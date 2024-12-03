#include"主窗口.h"



size_t 获取指令长度(UCHAR* 指令地址)
{
    // 初始化 Zydis 引擎
    ZydisDecoder 编码器;
    ZydisDecoderInit(&编码器, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // 准备存储解码结果的结构体和数组
    ZydisDecodedInstruction 解码结果;
    ZydisDecodedOperand 操作数[ZYDIS_MAX_OPERAND_COUNT];

    // 解码指令
    ZydisDecoderDecodeFull(&编码器, 指令地址, ZYDIS_MAX_INSTRUCTION_LENGTH, &解码结果, 操作数);


    char 解码数据[256];
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL); // 使用 Intel 格式
    ZydisFormatterFormatInstruction(&formatter, &解码结果, 操作数, 解码结果.operand_count_visible,
        解码数据, sizeof(解码数据), 0, NULL);

    // 返回解析出的指令长度
    return 解码结果.length;
}


BOOLEAN 函_单步步过(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息)
{
    SIZE_T 指令长度 = 获取指令长度((UCHAR*)寄存器信息->RIP);
    异常线程的信息->ContextRecord->Dr0 = 寄存器信息->RIP + 指令长度;
    异常线程的信息->ContextRecord->Dr7 = 0b01010101;
    return TRUE;
}

