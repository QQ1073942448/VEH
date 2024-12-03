#include"主窗口.h"




BOOLEAN 函_单步步入(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息) {
    ZydisDecoder 编码器;
    ZydisDecoderInit(&编码器, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    ZydisDecodedInstruction 解码结果;
    ZydisDecodedOperand 操作数[ZYDIS_MAX_OPERAND_COUNT];
    ZydisDecoderDecodeFull(&编码器, (UCHAR*)寄存器信息->RIP, ZYDIS_MAX_INSTRUCTION_LENGTH, &解码结果, 操作数);

    if (解码结果.mnemonic == ZYDIS_MNEMONIC_CALL) {
        UINT64 被调用地址 = 0;
        for (unsigned int i = 0; i < 解码结果.operand_count_visible; i++) {
            if (操作数[i].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
                被调用地址 = 寄存器信息->RIP + 解码结果.length + 操作数[i].imm.value.s;
                CString 文本地址 = 整数转十六进制文本(被调用地址);
                break;
            }
            else if (操作数[i].type == ZYDIS_OPERAND_TYPE_REGISTER) {
                if (操作数[i].reg.value == ZYDIS_REGISTER_RAX) {
                    被调用地址 = 寄存器信息->RAX;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_RBX) {
                    被调用地址 = 寄存器信息->RBX;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_RCX) {
                    被调用地址 = 寄存器信息->RCX;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_RSI) {
                    被调用地址 = 寄存器信息->RDX;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_RBP) {
                    被调用地址 = 寄存器信息->RBP;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_RSP) {
                    被调用地址 = 寄存器信息->RSP;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R8) {
                    被调用地址 = 寄存器信息->R8;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R9) {
                    被调用地址 = 寄存器信息->R9;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R10) {
                    被调用地址 = 寄存器信息->R10;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R11) {
                    被调用地址 = 寄存器信息->R11;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R12) {
                    被调用地址 = 寄存器信息->R12;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R13) {
                    被调用地址 = 寄存器信息->R13;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R14) {
                    被调用地址 = 寄存器信息->R14;
                    break;
                }
                else if (操作数[i].reg.value == ZYDIS_REGISTER_R15) {
                    被调用地址 = 寄存器信息->R15;
                    break;
                }

            }
        }
        异常线程的信息->ContextRecord->Dr0 = 被调用地址;
        异常线程的信息->ContextRecord->Dr7 = 0b01010101;
    }
    else {
        SIZE_T 指令长度 = 获取指令长度((UCHAR*)寄存器信息->RIP);
        异常线程的信息->ContextRecord->Dr0 = 寄存器信息->RIP + 指令长度;
        异常线程的信息->ContextRecord->Dr7 = 0b01010101;
    }

    return TRUE;
}