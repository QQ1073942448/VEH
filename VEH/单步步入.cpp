#include"������.h"




BOOLEAN ��_��������(P�Ĵ����ṹ�� �Ĵ�����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ) {
    ZydisDecoder ������;
    ZydisDecoderInit(&������, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    ZydisDecodedInstruction ������;
    ZydisDecodedOperand ������[ZYDIS_MAX_OPERAND_COUNT];
    ZydisDecoderDecodeFull(&������, (UCHAR*)�Ĵ�����Ϣ->RIP, ZYDIS_MAX_INSTRUCTION_LENGTH, &������, ������);

    if (������.mnemonic == ZYDIS_MNEMONIC_CALL) {
        UINT64 �����õ�ַ = 0;
        for (unsigned int i = 0; i < ������.operand_count_visible; i++) {
            if (������[i].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
                �����õ�ַ = �Ĵ�����Ϣ->RIP + ������.length + ������[i].imm.value.s;
                CString �ı���ַ = ����תʮ�������ı�(�����õ�ַ);
                break;
            }
            else if (������[i].type == ZYDIS_OPERAND_TYPE_REGISTER) {
                if (������[i].reg.value == ZYDIS_REGISTER_RAX) {
                    �����õ�ַ = �Ĵ�����Ϣ->RAX;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_RBX) {
                    �����õ�ַ = �Ĵ�����Ϣ->RBX;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_RCX) {
                    �����õ�ַ = �Ĵ�����Ϣ->RCX;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_RSI) {
                    �����õ�ַ = �Ĵ�����Ϣ->RDX;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_RBP) {
                    �����õ�ַ = �Ĵ�����Ϣ->RBP;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_RSP) {
                    �����õ�ַ = �Ĵ�����Ϣ->RSP;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R8) {
                    �����õ�ַ = �Ĵ�����Ϣ->R8;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R9) {
                    �����õ�ַ = �Ĵ�����Ϣ->R9;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R10) {
                    �����õ�ַ = �Ĵ�����Ϣ->R10;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R11) {
                    �����õ�ַ = �Ĵ�����Ϣ->R11;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R12) {
                    �����õ�ַ = �Ĵ�����Ϣ->R12;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R13) {
                    �����õ�ַ = �Ĵ�����Ϣ->R13;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R14) {
                    �����õ�ַ = �Ĵ�����Ϣ->R14;
                    break;
                }
                else if (������[i].reg.value == ZYDIS_REGISTER_R15) {
                    �����õ�ַ = �Ĵ�����Ϣ->R15;
                    break;
                }

            }
        }
        �쳣�̵߳���Ϣ->ContextRecord->Dr0 = �����õ�ַ;
        �쳣�̵߳���Ϣ->ContextRecord->Dr7 = 0b01010101;
    }
    else {
        SIZE_T ָ��� = ��ȡָ���((UCHAR*)�Ĵ�����Ϣ->RIP);
        �쳣�̵߳���Ϣ->ContextRecord->Dr0 = �Ĵ�����Ϣ->RIP + ָ���;
        �쳣�̵߳���Ϣ->ContextRecord->Dr7 = 0b01010101;
    }

    return TRUE;
}