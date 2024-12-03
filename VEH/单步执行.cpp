#include"������.h"



BOOLEAN ��_����ִ��(P�Ĵ����ṹ�� �Ĵ�����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ)
{
    // ��ʼ��Zydis������
    ZydisDecoder ������;
    ZydisDecoderInit(&������, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // ���뵱ǰָ��
    ZydisDecodedInstruction ������;
    ZydisDecodedOperand ������[ZYDIS_MAX_OPERAND_COUNT];
    ZydisDecoderDecodeFull(&������, (UCHAR*)�Ĵ�����Ϣ->RIP, ZYDIS_MAX_INSTRUCTION_LENGTH, &������, ������);
  
    // ��ȡ��ǰָ���
    SIZE_T ָ��� = ������.length;

    // ������һ��ָ���ַ
    UINT64 ��һ��ָ���ַ = �Ĵ�����Ϣ->RIP + ָ���;

    // ��ʼ�������ϵ��ַ
    UINT64 �ϵ�1��ַ = ��һ��ָ���ַ;
    UINT64 �ϵ�2��ַ = 0;
    BOOLEAN �Ƿ�ɹ� = FALSE;                                                     
    // ����Ƿ�ΪRETָ��                                                              
    if (������.mnemonic == ZYDIS_MNEMONIC_RET)                                       
    {
        // ��ȡջ�ϵķ��ص�ַ
        // �������ջ��64λ��
        ULONG64 ���ص�ַ = ��������(�Ĵ�����Ϣ->RSP,&�Ƿ�ɹ�);

        // ���÷��ص�ַΪ�ϵ�
        �ϵ�1��ַ = ���ص�ַ;
        �ϵ�2��ַ = 0; // RETָ��ͨ������Ҫ�ڶ����ϵ�

        // ����ջָ��
        �Ĵ�����Ϣ->RSP += sizeof(UINT64);
    }
    else
    {
        // ������������������������Ĵ���
        for (ULONG i = 0; i < ������.operand_count_visible; i++)
        {
            if (������[i].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
            {
                �ϵ�2��ַ = �Ĵ�����Ϣ->RIP + ָ��� + ������[i].imm.value.s;
                break;
            }
            else if (������[i].type == ZYDIS_OPERAND_TYPE_REGISTER)
            {
                // ����Ĵ�����ת
                switch (������[i].reg.value)
                {
                case ZYDIS_REGISTER_RAX: �ϵ�2��ַ = �Ĵ�����Ϣ->RAX; break;
                case ZYDIS_REGISTER_RBX: �ϵ�2��ַ = �Ĵ�����Ϣ->RBX; break;
                case ZYDIS_REGISTER_RCX: �ϵ�2��ַ = �Ĵ�����Ϣ->RCX; break;
                case ZYDIS_REGISTER_RDX: �ϵ�2��ַ = �Ĵ�����Ϣ->RDX; break;
                case ZYDIS_REGISTER_RBP: �ϵ�2��ַ = �Ĵ�����Ϣ->RBP; break;
                case ZYDIS_REGISTER_RSP: �ϵ�2��ַ = �Ĵ�����Ϣ->RSP; break;
                case ZYDIS_REGISTER_R8: �ϵ�2��ַ = �Ĵ�����Ϣ->R8; break;
                case ZYDIS_REGISTER_R9: �ϵ�2��ַ = �Ĵ�����Ϣ->R9; break;
                case ZYDIS_REGISTER_R10: �ϵ�2��ַ = �Ĵ�����Ϣ->R10; break;
                case ZYDIS_REGISTER_R11: �ϵ�2��ַ = �Ĵ�����Ϣ->R11; break;
                case ZYDIS_REGISTER_R12: �ϵ�2��ַ = �Ĵ�����Ϣ->R12; break;
                case ZYDIS_REGISTER_R13: �ϵ�2��ַ = �Ĵ�����Ϣ->R13; break;
                case ZYDIS_REGISTER_R14: �ϵ�2��ַ = �Ĵ�����Ϣ->R14; break;
                case ZYDIS_REGISTER_R15: �ϵ�2��ַ = �Ĵ�����Ϣ->R15; break;
                }
                break; // ����ҵ�һ���Ĵ�����ת���˳�ѭ��
            }
        }
    }

    // ���õ��ԼĴ���
    �쳣�̵߳���Ϣ->ContextRecord->Dr0 = �ϵ�1��ַ; // ��һ���ϵ��ַ

    if (�ϵ�2��ַ != 0)
    {
        �쳣�̵߳���Ϣ->ContextRecord->Dr1 = �ϵ�2��ַ; // �ڶ����ϵ��ַ
    }

    // ���õ��ԼĴ����ı�־λ
    �쳣�̵߳���Ϣ->ContextRecord->Dr7 = 0b01010101;

    // ����TRUE����ʾ�ɹ����öϵ�
    return TRUE;
}
