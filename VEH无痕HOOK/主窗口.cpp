// 主窗口.cpp: 实现文件
//

#include "VEH无痕HOOK.h"
#include "主窗口.h"
#include "afxdialogex.h"
#include"设置断点.h"
// 主窗口 对话框

IMPLEMENT_DYNAMIC(主窗口, CDialogEx)

主窗口::主窗口(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

主窗口::~主窗口()
{
}

void 主窗口::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(主窗口, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &主窗口::OnBnClickedButton1)
END_MESSAGE_MAP()


// 主窗口 消息处理程序


#define 技能CALL 0x14480BB70 

PVOID VEH句柄 = 0;
寄存器结构体 寄存器信息 = { 0 };
ULONG64 下一条指令地址 = 0;
BOOLEAN 无痕钩子(_EXCEPTION_POINTERS* 异常线程的信息) {

	ULONG64 技能代码所在的地址 = 异常线程的信息->ContextRecord->Rcx+0x10;
	ULONG 读取的数据 = *(ULONG*)技能代码所在的地址;
	char 读取的字符串[256];
	*(ULONG*)技能代码所在的地址 = 30515;
	return TRUE;

}




LONG VEH回调函数(_EXCEPTION_POINTERS* 异常线程的信息) {

	if (异常线程的信息->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT ||//INT 3引起的中断异常     //只处理特定异常
		异常线程的信息->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)//硬件断点引起的中断异常
	{
	
		if (异常线程的信息->ContextRecord->Rip == 技能CALL) {
			无痕钩子(异常线程的信息);
			清空断点(异常线程的信息);
			获取异常线程上下文(异常线程的信息, &寄存器信息);//获取该线程上下文
			函_单步执行(&寄存器信息, 异常线程的信息);
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		if (异常线程的信息->ContextRecord->Rip == 下一条指令地址) {
			清空断点(异常线程的信息);
			异常线程的信息->ContextRecord->Dr0 = 技能CALL;
			异常线程的信息->ContextRecord->Dr7 = 0b01010101;

			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}


	return EXCEPTION_CONTINUE_SEARCH;//不处理直接跳过
}




void 主窗口::OnBnClickedButton1()
{
	VEH句柄 = AddVectoredExceptionHandler(1, VEH回调函数);
	设置断点(技能CALL, 1);
}




