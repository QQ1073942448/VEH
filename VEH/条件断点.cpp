#include"������.h"


BOOLEAN �Ա�����(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ, �Ĵ����ṹ�� �����ϵ�)
{
	//�ж��Ƿ����������ϵ�
	if (�쳣�̵߳���Ϣ->ContextRecord->Rax== �����ϵ�.RAX) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rbx == �����ϵ�.RBX) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rcx == �����ϵ�.RCX) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rdx == �����ϵ�.RDX) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rdi == �����ϵ�.RDI) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rsi == �����ϵ�.RSI) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rbp == �����ϵ�.RBP) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->Rsp == �����ϵ�.RSP) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R8 == �����ϵ�.R8) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R9 == �����ϵ�.R9) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R10 == �����ϵ�.R10) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R11 == �����ϵ�.R11) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R12 == �����ϵ�.R12) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R13 == �����ϵ�.R13) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R14 == �����ϵ�.R14) {
		return TRUE;
	}
	else if (�쳣�̵߳���Ϣ->ContextRecord->R15 == �����ϵ�.R15) {
		return TRUE;
	}
	
	return FALSE;

}