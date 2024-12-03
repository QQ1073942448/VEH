#include"主窗口.h"



BOOLEAN 函_单步执行(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息)
{
    // 初始化Zydis解码器
    ZydisDecoder 编码器;
    ZydisDecoderInit(&编码器, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // 解码当前指令
    ZydisDecodedInstruction 解码结果;
    ZydisDecodedOperand 操作数[ZYDIS_MAX_OPERAND_COUNT];
    ZydisDecoderDecodeFull(&编码器, (UCHAR*)寄存器信息->RIP, ZYDIS_MAX_INSTRUCTION_LENGTH, &解码结果, 操作数);
  
    // 获取当前指令长度
    SIZE_T 指令长度 = 解码结果.length;

    // 计算下一条指令地址
    UINT64 下一个指令地址 = 寄存器信息->RIP + 指令长度;

    // 初始化两个断点地址
    UINT64 断点1地址 = 下一个指令地址;
    UINT64 断点2地址 = 0;
    BOOLEAN 是否成功 = FALSE;                                                     
    // 检查是否为RET指令                                                              
    if (解码结果.mnemonic == ZYDIS_MNEMONIC_RET)                                       
    {
        // 获取栈上的返回地址
        // 这里假设栈是64位的
        ULONG64 返回地址 = 读长整数(寄存器信息->RSP,&是否成功);

        // 设置返回地址为断点
        断点1地址 = 返回地址;
        断点2地址 = 0; // RET指令通常不需要第二个断点

        // 更新栈指针
        寄存器信息->RSP += sizeof(UINT64);
    }
    else
    {
        // 遍历操作数，查找立即数或寄存器
        for (ULONG i = 0; i < 解码结果.operand_count_visible; i++)
        {
            if (操作数[i].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
            {
                断点2地址 = 寄存器信息->RIP + 指令长度 + 操作数[i].imm.value.s;
                break;
            }
            else if (操作数[i].type == ZYDIS_OPERAND_TYPE_REGISTER)
            {
                // 处理寄存器跳转
                switch (操作数[i].reg.value)
                {
                case ZYDIS_REGISTER_RAX: 断点2地址 = 寄存器信息->RAX; break;
                case ZYDIS_REGISTER_RBX: 断点2地址 = 寄存器信息->RBX; break;
                case ZYDIS_REGISTER_RCX: 断点2地址 = 寄存器信息->RCX; break;
                case ZYDIS_REGISTER_RDX: 断点2地址 = 寄存器信息->RDX; break;
                case ZYDIS_REGISTER_RBP: 断点2地址 = 寄存器信息->RBP; break;
                case ZYDIS_REGISTER_RSP: 断点2地址 = 寄存器信息->RSP; break;
                case ZYDIS_REGISTER_R8: 断点2地址 = 寄存器信息->R8; break;
                case ZYDIS_REGISTER_R9: 断点2地址 = 寄存器信息->R9; break;
                case ZYDIS_REGISTER_R10: 断点2地址 = 寄存器信息->R10; break;
                case ZYDIS_REGISTER_R11: 断点2地址 = 寄存器信息->R11; break;
                case ZYDIS_REGISTER_R12: 断点2地址 = 寄存器信息->R12; break;
                case ZYDIS_REGISTER_R13: 断点2地址 = 寄存器信息->R13; break;
                case ZYDIS_REGISTER_R14: 断点2地址 = 寄存器信息->R14; break;
                case ZYDIS_REGISTER_R15: 断点2地址 = 寄存器信息->R15; break;
                }
                break; // 如果找到一个寄存器跳转就退出循环
            }
        }
    }

    // 设置调试寄存器
    异常线程的信息->ContextRecord->Dr0 = 断点1地址; // 第一个断点地址

    if (断点2地址 != 0)
    {
        异常线程的信息->ContextRecord->Dr1 = 断点2地址; // 第二个断点地址
    }

    // 设置调试寄存器的标志位
    异常线程的信息->ContextRecord->Dr7 = 0b01010101;

    // 返回TRUE，表示成功设置断点
    return TRUE;
}
