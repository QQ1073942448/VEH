#include"������.h"

extern �༭��ָ�� �༭����Ϣ;


ULONG64 �ӱ༭���ȡ��ֵ(CEdit* �༭��) {
    CString �ı�;
    �༭��->GetWindowTextW(�ı�);
    std::wstringstream wss;
    wss << �ı�.GetString();
    ULONG64 ��ֵ = 0;
    wss >> std::hex >> ��ֵ;
    return ��ֵ;
}

BOOLEAN ��ȡ�쳣�߳�������(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ, P�Ĵ����ṹ�� �Ĵ�����Ϣ) {

	�Ĵ�����Ϣ->RAX = �쳣�̵߳���Ϣ->ContextRecord->Rax;
	�Ĵ�����Ϣ->RBX = �쳣�̵߳���Ϣ->ContextRecord->Rbx;
	�Ĵ�����Ϣ->RCX = �쳣�̵߳���Ϣ->ContextRecord->Rcx;
	�Ĵ�����Ϣ->RDX = �쳣�̵߳���Ϣ->ContextRecord->Rdx;
	�Ĵ�����Ϣ->RSI = �쳣�̵߳���Ϣ->ContextRecord->Rsi;
	�Ĵ�����Ϣ->RDI = �쳣�̵߳���Ϣ->ContextRecord->Rdi;
	�Ĵ�����Ϣ->RBP = �쳣�̵߳���Ϣ->ContextRecord->Rbp;
	�Ĵ�����Ϣ->RSP = �쳣�̵߳���Ϣ->ContextRecord->Rsp;
	�Ĵ�����Ϣ->R8 = �쳣�̵߳���Ϣ->ContextRecord->R8;
	�Ĵ�����Ϣ->R9 = �쳣�̵߳���Ϣ->ContextRecord->R9;
	�Ĵ�����Ϣ->R10 = �쳣�̵߳���Ϣ->ContextRecord->R10;
	�Ĵ�����Ϣ->R11 = �쳣�̵߳���Ϣ->ContextRecord->R11;
	�Ĵ�����Ϣ->R12 = �쳣�̵߳���Ϣ->ContextRecord->R12;
	�Ĵ�����Ϣ->R13 = �쳣�̵߳���Ϣ->ContextRecord->R13;
	�Ĵ�����Ϣ->R14 = �쳣�̵߳���Ϣ->ContextRecord->R14;
	�Ĵ�����Ϣ->RIP = �쳣�̵߳���Ϣ->ContextRecord->Rip;
	�Ĵ�����Ϣ->XMM0 = �쳣�̵߳���Ϣ->ContextRecord->Xmm0;
	�Ĵ�����Ϣ->XMM1 = �쳣�̵߳���Ϣ->ContextRecord->Xmm1;
	�Ĵ�����Ϣ->XMM2 = �쳣�̵߳���Ϣ->ContextRecord->Xmm2;
	�Ĵ�����Ϣ->XMM3 = �쳣�̵߳���Ϣ->ContextRecord->Xmm3;
	�Ĵ�����Ϣ->XMM4 = �쳣�̵߳���Ϣ->ContextRecord->Xmm4;
	�Ĵ�����Ϣ->XMM5 = �쳣�̵߳���Ϣ->ContextRecord->Xmm5;
	�Ĵ�����Ϣ->XMM6 = �쳣�̵߳���Ϣ->ContextRecord->Xmm6;
	�Ĵ�����Ϣ->XMM7 = �쳣�̵߳���Ϣ->ContextRecord->Xmm7;
	�Ĵ�����Ϣ->XMM8 = �쳣�̵߳���Ϣ->ContextRecord->Xmm8;
	�Ĵ�����Ϣ->XMM9 = �쳣�̵߳���Ϣ->ContextRecord->Xmm9;
	�Ĵ�����Ϣ->XMM10 = �쳣�̵߳���Ϣ->ContextRecord->Xmm10;
	�Ĵ�����Ϣ->XMM11 = �쳣�̵߳���Ϣ->ContextRecord->Xmm11;
	�Ĵ�����Ϣ->XMM12 = �쳣�̵߳���Ϣ->ContextRecord->Xmm12;
	�Ĵ�����Ϣ->XMM13 = �쳣�̵߳���Ϣ->ContextRecord->Xmm13;
	�Ĵ�����Ϣ->XMM14 = �쳣�̵߳���Ϣ->ContextRecord->Xmm14;
	�Ĵ�����Ϣ->XMM15 = �쳣�̵߳���Ϣ->ContextRecord->Xmm15;
	�Ĵ�����Ϣ->DR0 = �쳣�̵߳���Ϣ->ContextRecord->Dr0;
	�Ĵ�����Ϣ->DR1 = �쳣�̵߳���Ϣ->ContextRecord->Dr1;
	�Ĵ�����Ϣ->DR2 = �쳣�̵߳���Ϣ->ContextRecord->Dr2;
	�Ĵ�����Ϣ->DR3 = �쳣�̵߳���Ϣ->ContextRecord->Dr3;
	�Ĵ�����Ϣ->DR6 = �쳣�̵߳���Ϣ->ContextRecord->Dr6;
	�Ĵ�����Ϣ->DR7 = �쳣�̵߳���Ϣ->ContextRecord->Dr7;

	return TRUE;
}

BOOLEAN �������ڱ����쳣�߳�������(�༭��ָ�� �༭����Ϣ, P�Ĵ����ṹ�� �Ĵ�����Ϣ) {

    auto to_hex_string = [](ULONG64 value) -> std::wstring {
        std::wstringstream wss;
        wss << std::hex << std::showbase << value;
        return wss.str();
    };

    �༭����Ϣ.�༭��1->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RAX).c_str());
    �༭����Ϣ.�༭��2->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RBX).c_str());
    �༭����Ϣ.�༭��3->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RCX).c_str());
    �༭����Ϣ.�༭��4->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RDX).c_str());
    �༭����Ϣ.�༭��5->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RSI).c_str());
    �༭����Ϣ.�༭��6->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RDI).c_str());
    �༭����Ϣ.�༭��7->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RBP).c_str());
    �༭����Ϣ.�༭��8->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RSP).c_str());
    �༭����Ϣ.�༭��9->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R8).c_str());
    �༭����Ϣ.�༭��10->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R9).c_str());
    �༭����Ϣ.�༭��11->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R10).c_str());
    �༭����Ϣ.�༭��12->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R11).c_str());
    �༭����Ϣ.�༭��13->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R12).c_str());
    �༭����Ϣ.�༭��14->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R13).c_str());
    �༭����Ϣ.�༭��15->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R14).c_str());
    �༭����Ϣ.�༭��16->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->R15).c_str());
    �༭����Ϣ.�༭��17->SetWindowTextW(to_hex_string(�Ĵ�����Ϣ->RIP).c_str());

    return TRUE;
}

BOOLEAN ��ȡ�����ڸ����Ĵ�����Ϣд���쳣�߳�������(�༭��ָ�� �༭����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ) {
   
    �쳣�̵߳���Ϣ->ContextRecord->Rax = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��1);
    �쳣�̵߳���Ϣ->ContextRecord->Rbx = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��2);
    �쳣�̵߳���Ϣ->ContextRecord->Rcx = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��3);
    �쳣�̵߳���Ϣ->ContextRecord->Rdx = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��4);
    �쳣�̵߳���Ϣ->ContextRecord->Rsi = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��5);
    �쳣�̵߳���Ϣ->ContextRecord->Rdi = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��6);
    �쳣�̵߳���Ϣ->ContextRecord->Rbp = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��7);
    �쳣�̵߳���Ϣ->ContextRecord->Rsp = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��8);
    �쳣�̵߳���Ϣ->ContextRecord->R8 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��9);
    �쳣�̵߳���Ϣ->ContextRecord->R9 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��10);
    �쳣�̵߳���Ϣ->ContextRecord->R10 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��11);
    �쳣�̵߳���Ϣ->ContextRecord->R11 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��12);
    �쳣�̵߳���Ϣ->ContextRecord->R12 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��13);
    �쳣�̵߳���Ϣ->ContextRecord->R13 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��14);
    �쳣�̵߳���Ϣ->ContextRecord->R14 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��15);
    �쳣�̵߳���Ϣ->ContextRecord->R15 = �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��16);
    �쳣�̵߳���Ϣ->ContextRecord->Rip= �ӱ༭���ȡ��ֵ(�༭����Ϣ.�༭��17);
    return TRUE;
}


void ���¶ϵ���ʾ(CListCtrl* �б��, P�Ĵ����ṹ�� �Ĵ�����Ϣ)
{
    ULONG ����������� = �б��->GetItemCount();//��ȡ�������
    BOOLEAN �ҵ�ƥ���� = FALSE; // ��־�Ƿ��ҵ�ƥ����
    for (int i = 0; i < �����������; ++i)//��ʼ����
    {
        CString ��һ���ı� = �б��->GetItemText(i, 0); // ��ȡ��һ�е��ı�
        ULONG64 ��ֵַ = _tcstoull(��һ���ı�, NULL, 16); // ���ı�ת��ΪULONG64

        if (��ֵַ == �Ĵ�����Ϣ->RIP)
        {
            �ҵ�ƥ���� = TRUE; // �ҵ�ƥ������ñ�־Ϊ��
            �б��->SetItemText(i, 3, L"<--��"); // ���µ�����Ϊ���桱
        }
        else
        {
            �б��->SetItemText(i, 3, L"");   // ɾ�������в�ƥ�������
        }
    }

    if (!�ҵ�ƥ����)
    {
        int �к� = �б��->GetItemCount();
        �б��->SetItemText(�к�, 3, L"<--��");

        // ���·���������ӡ���б��
        ������ڴ�����(�б��, (UCHAR*)�Ĵ�����Ϣ->RIP, ������С);
    }
}

void ��ջ�����ϵ���ʾ(CListCtrl* �б��) {
    ULONG ����������� = �б��->GetItemCount(); // ��ȡ�������
    for (int i = 0; i < �����������; ++i) {
        �б��->SetItemText(i, 3, L"");
    }
}

