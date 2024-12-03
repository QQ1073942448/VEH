#include"������.h"
#include"Zyidi.h"

#define ������ 0x500


BOOLEAN ������ڴ�����(CListCtrl* �б��, UCHAR* ָ�ʼ��ַ, SIZE_T ��С) {
  
  

    // ��ʼ�� Zydis ����
    ZydisDecoder ������;
    ZydisDecoderInit(&������, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // ��ʼ�� Zydis ��ʽ��
    ZydisFormatter ��ʽ��;
    ZydisFormatterInit(&��ʽ��, ZYDIS_FORMATTER_STYLE_INTEL); // ʹ�� Intel ��ʽ

    // ׼���洢�������Ľṹ�������
    ZydisDecodedInstruction ������;
    ZydisDecodedOperand ������[ZYDIS_MAX_OPERAND_COUNT];

    // ��ʼ��ƫ����
    UCHAR* ��ǰ��ַ = ָ�ʼ��ַ;
    UCHAR* ������ַ = ָ�ʼ��ַ +��С;
    char buffer[256];

    // ����б��
    �б��->DeleteAllItems();

    while (��ǰ��ַ < ������ַ) {
        // ���뵱ǰ��ַ����ָ��
        if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&������, ��ǰ��ַ, ZYDIS_MAX_INSTRUCTION_LENGTH, &������, ������))) {
            // ��ʽ��������Ϊ����ɶ���ʽ
            ZydisFormatterFormatInstruction(&��ʽ��, &������, ������, ������.operand_count_visible,
                buffer, sizeof(buffer), reinterpret_cast<ZyanU64>(��ǰ��ַ), nullptr);

            // ����ǰ��ַת��Ϊ���ַ��ַ���
            CStringW ��ַ�ַ���;
            ��ַ�ַ���.Format(L"%p", ��ǰ��ַ);
            int �к� = �б��->GetItemCount();
            �б��->InsertItem(�к�, ��ַ�ַ���); // ��һ���ǵ�ַ

            // ����ǰָ����ֽ�ת��Ϊʮ�������ַ�������ӵ��ڶ���
            CString �ֽ��ַ���;
            for (SIZE_T i = 0; i < ������.length; ++i) {
                CString ���ֽ�;
                ���ֽ�.Format(L"%02X ", ��ǰ��ַ[i]);
                �ֽ��ַ��� += ���ֽ�;
            }
            �б��->SetItemText(�к�, 1, �ֽ��ַ���); // �ڶ������ֽ�

            // �� ANSI ��ʽ�� buffer ת��Ϊ���ַ�����ӵ�������
            CStringA ������ANSI(buffer);
            CStringW ���ַ�������(������ANSI); // ʹ�ù��캯���� ANSI ת��Ϊ Unicode
            �б��->SetItemText(�к�, 2, ���ַ�������); // �������ǻ����

            // ���µ�ǰ��ַ
            ��ǰ��ַ += ������.length;
        }
        else {
            // �������ʧ�ܣ��˳�ѭ��
            break;
        }
    }

    return TRUE;
}

