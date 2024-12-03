#include"主窗口.h"


BOOLEAN 对比条件(_EXCEPTION_POINTERS* 异常线程的信息, 寄存器结构体 条件断点)
{
	//判断是否满足条件断点
	if (异常线程的信息->ContextRecord->Rax== 条件断点.RAX) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rbx == 条件断点.RBX) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rcx == 条件断点.RCX) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rdx == 条件断点.RDX) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rdi == 条件断点.RDI) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rsi == 条件断点.RSI) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rbp == 条件断点.RBP) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->Rsp == 条件断点.RSP) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R8 == 条件断点.R8) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R9 == 条件断点.R9) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R10 == 条件断点.R10) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R11 == 条件断点.R11) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R12 == 条件断点.R12) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R13 == 条件断点.R13) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R14 == 条件断点.R14) {
		return TRUE;
	}
	else if (异常线程的信息->ContextRecord->R15 == 条件断点.R15) {
		return TRUE;
	}
	
	return FALSE;

}