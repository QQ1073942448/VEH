#include"������.h"



size_t ��ȡָ���(UCHAR* ָ���ַ)
{
    // ��ʼ�� Zydis ����
    ZydisDecoder ������;
    ZydisDecoderInit(&������, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // ׼���洢�������Ľṹ�������
    ZydisDecodedInstruction ������;
    ZydisDecodedOperand ������[ZYDIS_MAX_OPERAND_COUNT];

    // ����ָ��
    ZydisDecoderDecodeFull(&������, ָ���ַ, ZYDIS_MAX_INSTRUCTION_LENGTH, &������, ������);


    char ��������[256];
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL); // ʹ�� Intel ��ʽ
    ZydisFormatterFormatInstruction(&formatter, &������, ������, ������.operand_count_visible,
        ��������, sizeof(��������), 0, NULL);

    // ���ؽ�������ָ���
    return ������.length;
}


BOOLEAN ��_��������(P�Ĵ����ṹ�� �Ĵ�����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ)
{
    SIZE_T ָ��� = ��ȡָ���((UCHAR*)�Ĵ�����Ϣ->RIP);
    �쳣�̵߳���Ϣ->ContextRecord->Dr0 = �Ĵ�����Ϣ->RIP + ָ���;
    �쳣�̵߳���Ϣ->ContextRecord->Dr7 = 0b01010101;
    return TRUE;
}

