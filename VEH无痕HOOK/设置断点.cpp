#include"设置断点.h"
#include <Zydis/Zydis.h>

extern ULONG64 下一条指令地址;

#ifdef __cplusplus
extern "C" {
#endif

    ZyanStatus ZydisDecoderInit(ZydisDecoder* decoder, ZydisMachineMode machine_mode,
        ZydisStackWidth stack_width);

    ZyanStatus ZydisDecoderDecodeFull(const ZydisDecoder* decoder,
        const void* buffer, ZyanUSize length, ZydisDecodedInstruction* instruction,
        ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT]);

    ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style);

    ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count, char* buffer, ZyanUSize length, ZyanU64 runtime_address,
        void* user_data);

    ZyanStatus ZydisEncoderDecodedInstructionToEncoderRequest(
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count_visible, ZydisEncoderRequest* request);
    ZyanStatus ZydisEncoderEncodeInstruction(const ZydisEncoderRequest* request,
        void* buffer, ZyanUSize* length);

#ifdef __cplusplus
}
#endif

BOOLEAN 内存地址是否可读(ULONG64 内存地址, SIZE_T 探测长度) {
    MEMORY_BASIC_INFORMATION mbi;
    ULONG64 结束地址 = 内存地址 + 探测长度;

    while (内存地址 < 结束地址) {
        if (VirtualQuery((LPCVOID)内存地址, &mbi, sizeof(mbi)) == 0) {
            return FALSE; // 如果 VirtualQuery 失败，返回 FALSE
        }

        // 检查内存页面的保护属性是否允许读操作
        if (!((mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_READONLY) || (mbi.Protect & PAGE_EXECUTE_READ) || (mbi.Protect & PAGE_EXECUTE_READWRITE))) {
            return FALSE; // 如果内存不可读，返回 FALSE
        }

        // 前进到下一页
        内存地址 = (ULONG64)mbi.BaseAddress + mbi.RegionSize;
    }

    return TRUE; // 如果整个区域内存可读，返回 TRUE
}

USHORT 读短整数(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(USHORT))) {
        *是否成功 = TRUE;
        return *(USHORT*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

ULONG 读整数(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(ULONG))) {
        *是否成功 = TRUE;
        return *(ULONG*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

ULONG64 读长整数(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(ULONG64))) {
        *是否成功 = TRUE;
        return *(ULONG64*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}








BOOLEAN 设置硬件断点(HANDLE 线程句柄, ULONG64 HOOK函数地址, DWORD 线程TID, ULONG 调试寄存器信息) {
    CONTEXT 线程上下文 = { 0 };
    线程上下文.ContextFlags = CONTEXT_DEBUG_REGISTERS; // 获取调试寄存器信息
    GetThreadContext(线程句柄, &线程上下文);  // 获取线程的上下文信息
    线程上下文.Dr7 |= 0x1;//这里为启用断点
    if (调试寄存器信息 == 1) {
        线程上下文.Dr0 = HOOK函数地址;
    }
    else if (调试寄存器信息 == 2) {
        线程上下文.Dr1 = HOOK函数地址;
    }
    else if (调试寄存器信息 == 3) {
        线程上下文.Dr2 = HOOK函数地址;
    }
    else if (调试寄存器信息 == 4) {
        线程上下文.Dr3 = HOOK函数地址;
    }
    SetThreadContext(线程句柄, &线程上下文);

    return TRUE;
}

BOOLEAN 获取异常线程上下文(_EXCEPTION_POINTERS* 异常线程的信息, P寄存器结构体 寄存器信息) {

    寄存器信息->RAX = 异常线程的信息->ContextRecord->Rax;
    寄存器信息->RBX = 异常线程的信息->ContextRecord->Rbx;
    寄存器信息->RCX = 异常线程的信息->ContextRecord->Rcx;
    寄存器信息->RDX = 异常线程的信息->ContextRecord->Rdx;
    寄存器信息->RSI = 异常线程的信息->ContextRecord->Rsi;
    寄存器信息->RDI = 异常线程的信息->ContextRecord->Rdi;
    寄存器信息->RBP = 异常线程的信息->ContextRecord->Rbp;
    寄存器信息->RSP = 异常线程的信息->ContextRecord->Rsp;
    寄存器信息->R8 = 异常线程的信息->ContextRecord->R8;
    寄存器信息->R9 = 异常线程的信息->ContextRecord->R9;
    寄存器信息->R10 = 异常线程的信息->ContextRecord->R10;
    寄存器信息->R11 = 异常线程的信息->ContextRecord->R11;
    寄存器信息->R12 = 异常线程的信息->ContextRecord->R12;
    寄存器信息->R13 = 异常线程的信息->ContextRecord->R13;
    寄存器信息->R14 = 异常线程的信息->ContextRecord->R14;
    寄存器信息->RIP = 异常线程的信息->ContextRecord->Rip;
    寄存器信息->XMM0 = 异常线程的信息->ContextRecord->Xmm0;
    寄存器信息->XMM1 = 异常线程的信息->ContextRecord->Xmm1;
    寄存器信息->XMM2 = 异常线程的信息->ContextRecord->Xmm2;
    寄存器信息->XMM3 = 异常线程的信息->ContextRecord->Xmm3;
    寄存器信息->XMM4 = 异常线程的信息->ContextRecord->Xmm4;
    寄存器信息->XMM5 = 异常线程的信息->ContextRecord->Xmm5;
    寄存器信息->XMM6 = 异常线程的信息->ContextRecord->Xmm6;
    寄存器信息->XMM7 = 异常线程的信息->ContextRecord->Xmm7;
    寄存器信息->XMM8 = 异常线程的信息->ContextRecord->Xmm8;
    寄存器信息->XMM9 = 异常线程的信息->ContextRecord->Xmm9;
    寄存器信息->XMM10 = 异常线程的信息->ContextRecord->Xmm10;
    寄存器信息->XMM11 = 异常线程的信息->ContextRecord->Xmm11;
    寄存器信息->XMM12 = 异常线程的信息->ContextRecord->Xmm12;
    寄存器信息->XMM13 = 异常线程的信息->ContextRecord->Xmm13;
    寄存器信息->XMM14 = 异常线程的信息->ContextRecord->Xmm14;
    寄存器信息->XMM15 = 异常线程的信息->ContextRecord->Xmm15;
    寄存器信息->DR0 = 异常线程的信息->ContextRecord->Dr0;
    寄存器信息->DR1 = 异常线程的信息->ContextRecord->Dr1;
    寄存器信息->DR2 = 异常线程的信息->ContextRecord->Dr2;
    寄存器信息->DR3 = 异常线程的信息->ContextRecord->Dr3;
    寄存器信息->DR6 = 异常线程的信息->ContextRecord->Dr6;
    寄存器信息->DR7 = 异常线程的信息->ContextRecord->Dr7;

    return TRUE;
}

BOOLEAN 设置断点(ULONG64 HOOK函数地址, ULONG 调试寄存器信息) {

    DWORD 进程ID = GetCurrentProcessId();
    HANDLE 线程快照 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 线程条目;
    线程条目.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(线程快照, &线程条目)) {
        do {
            if (线程条目.th32OwnerProcessID == 进程ID) {
                HANDLE 线程句柄 = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, 线程条目.th32ThreadID);
                if (线程句柄) {
                    设置硬件断点(线程句柄, HOOK函数地址, 线程条目.th32ThreadID, 调试寄存器信息);
                    CloseHandle(线程句柄);
                }
            }
        } while (Thread32Next(线程快照, &线程条目));
    }
    CloseHandle(线程快照);
    return TRUE;
}


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
        ULONG64 返回地址 = 读长整数(寄存器信息->RSP, &是否成功);

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
    下一条指令地址 = 断点1地址;
    if (断点2地址 != 0)
    {
        异常线程的信息->ContextRecord->Dr1 = 断点2地址; // 第二个断点地址
    }

    // 设置调试寄存器的标志位
    异常线程的信息->ContextRecord->Dr7 = 0b01010101;

    // 返回TRUE，表示成功设置断点
    return TRUE;
}

BOOLEAN 清空断点(_EXCEPTION_POINTERS* 异常线程的信息)
{
    异常线程的信息->ContextRecord->Dr0 = 0;
    异常线程的信息->ContextRecord->Dr1 = 0;
    异常线程的信息->ContextRecord->Dr2 = 0;
    异常线程的信息->ContextRecord->Dr3 = 0;
    return TRUE;
}