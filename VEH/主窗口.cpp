#include "VEH.h"
#include "主窗口.h"
#include "afxdialogex.h"




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
	主窗口::初始化组件();
}




BEGIN_MESSAGE_MAP(主窗口, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &主窗口::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &主窗口::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &主窗口::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &主窗口::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &主窗口::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &主窗口::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &主窗口::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &主窗口::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &主窗口::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &主窗口::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &主窗口::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &主窗口::OnBnClickedButton12)//按钮少13  编辑框少24
	ON_BN_CLICKED(IDC_BUTTON14, &主窗口::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &主窗口::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &主窗口::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &主窗口::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &主窗口::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &主窗口::OnBnClickedButton19)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &主窗口::列表框4_双击列表项)
	ON_EN_KILLFOCUS(IDC_EDIT4, &主窗口::列表框4_失去焦点编辑框)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &主窗口::列表框3_双击列表项)
	ON_EN_KILLFOCUS(IDC_EDIT3, &主窗口::列表框3_失去焦点编辑框)

END_MESSAGE_MAP()


// 主窗口 消息处理程序











void 主窗口::OnBnClickedButton18()
{
	ShowWindow(SW_MINIMIZE);
}








PVOID VEH句柄 = 0;
编辑框指针 编辑框信息 = { 0 };
列表框指针 列表框信息 = { 0 };
下拉框指针 下拉框信息 = { 0 };
寄存器结构体 寄存器信息 = { 0 };
调试寄存器信息 寄存器标识符 = { 0, 1, 2, 3, 4, 5, 6, 7 };
BOOLEAN 单步步过 = FALSE;
BOOLEAN 单步步入 = FALSE;
BOOLEAN 单步执行 = FALSE;
BOOLEAN 返回上级调用 = FALSE;
BOOLEAN 运行 = FALSE;
BOOLEAN 是否清空断点 = FALSE;
ULONG 列表框4_写入类型 = 0;
BOOLEAN 允许执行 = FALSE;
CString 文本数值;
CString 文本地址;
ULONG64 编辑框激活 = 0;
ULONG 当前数据类型 = 0;
寄存器结构体 条件断点 = { 0 };
BOOLEAN 是否开启条件断点 = FALSE;

LONG VEH回调函数(_EXCEPTION_POINTERS* 异常线程的信息)
{
	if (异常线程的信息->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT ||//INT 3引起的中断异常     //只处理特定异常
		异常线程的信息->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)//硬件断点引起的中断异常
	{
		if (!允许执行) {

			return EXCEPTION_CONTINUE_SEARCH;//不运行执行直接调试不处理
		}
		if (是否开启条件断点) {//对比条件断点是否开启
			if (!对比条件(异常线程的信息, 条件断点)) {//对比条件是否达成
				清空断点(异常线程的信息);//不达成情况断点
				return EXCEPTION_CONTINUE_EXECUTION;//返回通知系统继续执行
			}
		}

		获取异常线程上下文(异常线程的信息, &寄存器信息);//获取该线程上下文
		向主窗口报告堆栈调用(列表框信息.列表框2, &寄存器信息);//向主窗口报告堆栈回溯
		向主窗口报告异常线程上下文(编辑框信息, &寄存器信息);//向主页面打印各个寄存器信息
		while (TRUE) {//进入循环等待逻辑，等待用户界面操作
			更新断点显示(列表框信息.列表框1, &寄存器信息);//向主窗口报告并更新断点的显示信息
			获取异常线程上下文(异常线程的信息, &寄存器信息);//重新获取一遍
			if (单步执行 == TRUE) {//单步执行
				单步执行 = FALSE;//等待主窗口再次设置单步为TRUE
				if (清空断点(异常线程的信息)) {//清空造成异常的断点为程序下一次正常运行做好准备，
					函_单步执行(&寄存器信息, 异常线程的信息);//获取异常线程RIP寄存器+当前指令长度计算出写入下一个断点位置，并反汇编当前指令得到立即数或者寄存器算出下一个跳转地址，并写入新的2个断点已完成单步执行逻辑
					清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
					获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文
					return EXCEPTION_CONTINUE_EXECUTION;//通知系统进行下一个单步执行逻辑  
				}
			}
			if (单步步过 == TRUE) {//单步步过
				单步步过 = FALSE;//等待主窗口再次设置单步为TRUE
				if (清空断点(异常线程的信息)) {//清空造成异常的断点为程序下一次正常运行做好准备，
					函_单步步过(&寄存器信息, 异常线程的信息);//获取异常线程RIP寄存器+当前指令长度算出下一个断点位置，写入下一个断点寄存器已完成单步步过逻辑
					清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
					获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文
					return EXCEPTION_CONTINUE_EXECUTION;//通知系统进行下一个单步步过逻辑 
				}
			}
			if (单步步入 == TRUE) {//单步步入
				单步步入 = FALSE;//等待主窗口再次设置单步为TRUE
				if (清空断点(异常线程的信息)) {//清空造成异常的断点为程序下一次正常运行做好准备，
					函_单步步入(&寄存器信息, 异常线程的信息);//反汇编当前指令是否为CALL指令，如果是则计算跳转的指令，更新新断点，完成单步步入逻辑
					清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
					获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文
					return EXCEPTION_CONTINUE_EXECUTION;//通知系统进行下一个单步步入逻辑 
				}
			}
			if (返回上级调用 == TRUE) {//返回上级调用
				返回上级调用 = FALSE;//等待主窗口再次设置单步为TRUE
				if (清空断点(异常线程的信息)) {//清空造成异常的断点为程序下一次正常运行做好准备，
					函_返回上级调用(&寄存器信息, 异常线程的信息);//获取当前线程的返回地址设置为下一个断点信息更新断点，完成返回调用逻辑
					清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
					获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文
					return EXCEPTION_CONTINUE_EXECUTION;//通知系统进行下一个方式上级调用逻辑 
				}
			}
			if (是否清空断点) {//是否清空断点
				是否清空断点 = FALSE; //等待主窗口再次设置单步为TRUE
				清空断点(异常线程的信息);//清空造成异常的断点为程序下一次正常运行做好准备，
				清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
				获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文

			}
			if (运行) {//是否允许运行
				运行 = FALSE;//等待主窗口再次设置单步为TRUE
				清空汇编区断点显示(列表框信息.列表框1);//清空用户界面的汇编断点显示区域
				获取主窗口各个寄存器信息写回异常线程上下文(编辑框信息, 异常线程的信息);//获取用户界面备好的各个寄存器并写回异常线程上下文
		      return EXCEPTION_CONTINUE_EXECUTION;//通知系统运行起来
			}
			Sleep(5);//延迟5毫秒
		};
	}
	return EXCEPTION_CONTINUE_SEARCH;//不处理直接跳过
}



BOOLEAN 初始化列表框格式1(CListCtrl* 列表框) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(列表框->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(列表框->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 列表框->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	列表框->SetExtendedStyle(dstyle);
	列表框->InsertColumn(0, L"命中断点", 0, 150);
	列表框->InsertColumn(0, L"汇编码", 0, 250);
	列表框->InsertColumn(0, L"字节", 0, 250);
	列表框->InsertColumn(0, L"地址", 0, 150);
	列表框->SetItemState(0, 0, LVIS_SELECTED); 

	return TRUE;
}


BOOLEAN 初始化列表框格式2(CListCtrl* 列表框) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(列表框->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(列表框->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 列表框->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	列表框->SetExtendedStyle(dstyle);
	列表框->InsertColumn(0, L"RBP", 0, 100);
	列表框->InsertColumn(0, L"参数4", 0, 100);
	列表框->InsertColumn(0, L"参数3", 0, 100);
	列表框->InsertColumn(0, L"参数2", 0, 100);
	列表框->InsertColumn(0, L"参数1", 0, 100);
	列表框->InsertColumn(0, L"返回地址", 0, 100);
	列表框->SetItemState(0, 0, LVIS_SELECTED);

	return TRUE;
}

BOOLEAN 初始化列表框格式3(CListCtrl* 列表框) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(列表框->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(列表框->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 列表框->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	列表框->SetExtendedStyle(dstyle);
	列表框->InsertColumn(0, L"16", 0, 40);
	列表框->InsertColumn(0, L"15", 0, 40);
	列表框->InsertColumn(0, L"14", 0, 40);
	列表框->InsertColumn(0, L"13", 0, 40);
	列表框->InsertColumn(0, L"12", 0, 40);
	列表框->InsertColumn(0, L"11", 0, 40);
	列表框->InsertColumn(0, L"10", 0, 40);
	列表框->InsertColumn(0, L"09", 0, 40);
	列表框->InsertColumn(0, L"08", 0, 40);
	列表框->InsertColumn(0, L"07", 0, 40);
	列表框->InsertColumn(0, L"06", 0, 40);
	列表框->InsertColumn(0, L"05", 0, 40);
	列表框->InsertColumn(0, L"04", 0, 40);
	列表框->InsertColumn(0, L"03", 0, 40);
	列表框->InsertColumn(0, L"02", 0, 40);
	列表框->InsertColumn(0, L"01", 0, 40);
	列表框->InsertColumn(0, L"地址", 0, 100);
	列表框->SetItemState(0, 0, LVIS_SELECTED);
	return TRUE;
}

BOOLEAN 初始化列表框格式4(CListCtrl* 列表框) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(列表框->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(列表框->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 列表框->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	列表框->SetExtendedStyle(dstyle);
	
	列表框->InsertColumn(0, L"数据", 0, 130);
	列表框->InsertColumn(0, L"地址", 0, 130);
	列表框->InsertColumn(0, L"偏移", 0, 50);
	列表框->SetItemState(0, 0, LVIS_SELECTED);
	return TRUE;
}


BOOLEAN 初始化下拉框格式1(CComboBox* 下拉框) {

	下拉框->AddString(_T("二字节"));
	下拉框->AddString(_T("四字节"));
	下拉框->AddString(_T("八字节"));
	下拉框->AddString(_T("单浮点"));
	下拉框->AddString(_T("双浮点"));
	CRect 矩形区域;
	下拉框->GetWindowRect(&矩形区域);
	int nNewHeight = 矩形区域.Height() + 6 * 下拉框->GetItemHeight(0); // 6 是要显示的行数
	下拉框->SetWindowPos(NULL, 0, 0, 矩形区域.Width(), nNewHeight, SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}


BOOLEAN 初始化下拉框格式2(CComboBox* 下拉框) {

	下拉框->AddString(_T("字节"));
	下拉框->AddString(_T("二字节"));
	下拉框->AddString(_T("四字节"));
	下拉框->AddString(_T("单浮点"));
	下拉框->AddString(_T("八字节"));
	下拉框->AddString(_T("双浮点"));
	CRect 矩形区域;
	下拉框->GetWindowRect(&矩形区域);
	int nNewHeight = 矩形区域.Height() + 7 * 下拉框->GetItemHeight(0); // 7 是要显示的行数
	下拉框->SetWindowPos(NULL, 0, 0, 矩形区域.Width(), nNewHeight, SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}

BOOLEAN 初始化下拉框格式3(CComboBox* 下拉框) {

	下拉框->AddString(_T("十进制"));
	下拉框->AddString(_T("十六进制"));
	CRect 矩形区域;
	下拉框->GetWindowRect(&矩形区域);
	int nNewHeight = 矩形区域.Height() + 6 * 下拉框->GetItemHeight(0); // 6 是要显示的行数
	下拉框->SetWindowPos(NULL, 0, 0, 矩形区域.Width(), nNewHeight, SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}

BOOLEAN 初始化下拉框格式4(CComboBox* 下拉框) {

	下拉框->AddString(_T("RAX"));
	下拉框->AddString(_T("RBX"));
	下拉框->AddString(_T("RCX"));
	下拉框->AddString(_T("RDX"));
	下拉框->AddString(_T("RSI"));
	下拉框->AddString(_T("RDI"));
	下拉框->AddString(_T("RBP"));
	下拉框->AddString(_T("RSP"));
	下拉框->AddString(_T("R8"));
	下拉框->AddString(_T("R9"));
	下拉框->AddString(_T("R10"));
	下拉框->AddString(_T("R11"));
	下拉框->AddString(_T("R12"));
	下拉框->AddString(_T("R13"));
	下拉框->AddString(_T("R14"));
	下拉框->AddString(_T("R15"));


	CRect 矩形区域;
	下拉框->GetWindowRect(&矩形区域);
	int nNewHeight = 矩形区域.Height() + 17 * 下拉框->GetItemHeight(0); // 6 是要显示的行数
	下拉框->SetWindowPos(NULL, 0, 0, 矩形区域.Width(), nNewHeight, SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}

 BOOLEAN 主窗口::初始化组件() {
	
	编辑框信息.编辑框1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	编辑框信息.编辑框2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	编辑框信息.编辑框3 = (CEdit*)GetDlgItem(IDC_EDIT3);
	编辑框信息.编辑框4 = (CEdit*)GetDlgItem(IDC_EDIT4);
	编辑框信息.编辑框5 = (CEdit*)GetDlgItem(IDC_EDIT5);
	编辑框信息.编辑框6 = (CEdit*)GetDlgItem(IDC_EDIT6);
	编辑框信息.编辑框7 = (CEdit*)GetDlgItem(IDC_EDIT7);
	编辑框信息.编辑框8 = (CEdit*)GetDlgItem(IDC_EDIT8);
	编辑框信息.编辑框9 = (CEdit*)GetDlgItem(IDC_EDIT9);
	编辑框信息.编辑框10 = (CEdit*)GetDlgItem(IDC_EDIT10);
	编辑框信息.编辑框11 = (CEdit*)GetDlgItem(IDC_EDIT11);
	编辑框信息.编辑框12 = (CEdit*)GetDlgItem(IDC_EDIT12);
	编辑框信息.编辑框13 = (CEdit*)GetDlgItem(IDC_EDIT13);
	编辑框信息.编辑框14 = (CEdit*)GetDlgItem(IDC_EDIT14);
	编辑框信息.编辑框15 = (CEdit*)GetDlgItem(IDC_EDIT15);
	编辑框信息.编辑框16 = (CEdit*)GetDlgItem(IDC_EDIT16);
	编辑框信息.编辑框17 = (CEdit*)GetDlgItem(IDC_EDIT17);
	编辑框信息.编辑框18 = (CEdit*)GetDlgItem(IDC_EDIT18);
	编辑框信息.编辑框19 = (CEdit*)GetDlgItem(IDC_EDIT19);
	编辑框信息.编辑框20 = (CEdit*)GetDlgItem(IDC_EDIT20);
	编辑框信息.编辑框21 = (CEdit*)GetDlgItem(IDC_EDIT21);
	编辑框信息.编辑框22 = (CEdit*)GetDlgItem(IDC_EDIT22);
	编辑框信息.编辑框23 = (CEdit*)GetDlgItem(IDC_EDIT23);
	编辑框信息.编辑框24 = (CEdit*)GetDlgItem(IDC_EDIT24);
	编辑框信息.编辑框25 = (CEdit*)GetDlgItem(IDC_EDIT25);
	列表框信息.列表框1= (CListCtrl*)GetDlgItem(IDC_LIST1);
	列表框信息.列表框2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	列表框信息.列表框3 = (CListCtrl*)GetDlgItem(IDC_LIST3);
	列表框信息.列表框4 = (CListCtrl*)GetDlgItem(IDC_LIST4);
	下拉框信息.下拉框1= (CComboBox*)GetDlgItem(IDC_COMBO1);
	下拉框信息.下拉框2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	下拉框信息.下拉框3 = (CComboBox*)GetDlgItem(IDC_COMBO3);
	下拉框信息.下拉框4 = (CComboBox*)GetDlgItem(IDC_COMBO4);
	初始化列表框格式1(列表框信息.列表框1);
	初始化列表框格式2(列表框信息.列表框2);
	初始化列表框格式3(列表框信息.列表框3);
	初始化列表框格式4(列表框信息.列表框4);
	初始化下拉框格式1(下拉框信息.下拉框1);
	初始化下拉框格式2(下拉框信息.下拉框2);
	初始化下拉框格式3(下拉框信息.下拉框3);
	初始化下拉框格式4(下拉框信息.下拉框4);
	 return TRUE;
}





void 主窗口::OnBnClickedButton1()
{
	// 获取当前系统时间
	SYSTEMTIME 当前时间;
	GetLocalTime(&当前时间);

	// 检查是否超过预定时间
	if (当前时间.wYear > 2024 || (当前时间.wYear == 2024 && 当前时间.wMonth > 10) || (当前时间.wYear == 2024 && 当前时间.wMonth == 10 && 当前时间.wDay > 25))
	{
		允许执行 = FALSE;
		return;
	}

	// 添加VEH处理程序
	VEH句柄 = AddVectoredExceptionHandler(1, VEH回调函数);
	if (VEH句柄 != NULL) {
		MessageBoxA(nullptr, "注意，本调试器仅供学习参考使用，禁止用于一切非法用途，否则后果自负！！！", "免责声明", MB_OK);
		 允许执行 = TRUE;
	}
	return;
}


void 主窗口::OnBnClickedButton2() {

	if (设置断点(编辑框信息.编辑框19, 0,NULL)) {
		MessageBoxA(nullptr, "断点设置成功", "成功",MB_OK);
	}
	else{
		MessageBoxA(nullptr, "断点设置失败", "失败",MB_OK);
	}
}


void 主窗口::OnBnClickedButton3()
{
	if (设置断点(编辑框信息.编辑框20, 寄存器标识符.DR1,NULL)) {
		MessageBoxA(nullptr, "断点设置成功", "成功", MB_OK);
	}
	else {
		MessageBoxA(nullptr, "断点设置失败", "失败", MB_OK);
	}
}


void 主窗口::OnBnClickedButton4()
{
	if (设置断点(编辑框信息.编辑框21, 寄存器标识符.DR2, NULL)) {
		MessageBoxA(nullptr, "断点设置成功", "成功", MB_OK);
	}
	else {
		MessageBoxA(nullptr, "断点设置失败", "失败", MB_OK);
	}
}


void 主窗口::OnBnClickedButton5()
{
	if (设置断点(编辑框信息.编辑框22, 寄存器标识符.DR3, NULL)) {
		MessageBoxA(nullptr, "断点设置成功", "成功", MB_OK);
	}
	else {
		MessageBoxA(nullptr, "断点设置失败", "失败", MB_OK);
	}
}

void 主窗口::OnBnClickedButton6()
{
	ULONG64 地址 = 取编辑框数据到整数(编辑框信息.编辑框18);
	读取内存(列表框信息.列表框3,下拉框信息.下拉框2, 地址, 4096*10);
}

void 主窗口::OnBnClickedButton7()
{
	单步步过 = TRUE;
}


void 主窗口::OnBnClickedButton8()
{
	运行 = TRUE;
}


void 主窗口::OnBnClickedButton9()
{
	ULONG64 地址 = 取编辑框数据到整数(编辑框信息.编辑框23);
	反汇编内存区域(列表框信息.列表框1, (UCHAR*)地址, 反汇编大小);
}



void 主窗口::OnBnClickedButton10()
{
	单步步入 = TRUE;
}


void 主窗口::OnBnClickedButton11()
{
	单步执行 = TRUE;
}


void 主窗口::OnBnClickedButton12()
{
	是否清空断点 = TRUE;
}


void 主窗口::OnBnClickedButton14()
{
	返回上级调用 = TRUE;
}





void 主窗口::OnBnClickedButton15()
{
	ULONG64 地址 = 取编辑框数据到整数(编辑框信息.编辑框25);
	函_类型读取(列表框信息.列表框4, 下拉框信息.下拉框1, 地址);
	
}


void 主窗口::列表框4_双击列表项(NMHDR* 消息, LRESULT* 结果)
{
	LPNMITEMACTIVATE 激活项消息 = reinterpret_cast<LPNMITEMACTIVATE>(消息);
	行 = 激活项消息->iItem;
	列 = 激活项消息->iSubItem;

	CRect 单元格矩形区域;
	列表框信息.列表框4->GetSubItemRect(行, 列, LVIR_BOUNDS, 单元格矩形区域);

	POINT 鼠标位置;
	GetCursorPos(&鼠标位置);
	ScreenToClient(&鼠标位置);
	int 编辑框宽度 = 单元格矩形区域.Width();
	int 编辑框高度 = 单元格矩形区域.Height();
	int 编辑框X = 鼠标位置.x + 5; // 调整X坐标，使其在鼠标右下角
	int 编辑框Y = 鼠标位置.y + 5; // 调整Y坐标，使其在鼠标右下角

	CRect 客户区矩形;
	GetClientRect(&客户区矩形);
	if (编辑框X + 编辑框宽度 > 客户区矩形.Width())
	{
		编辑框X = 客户区矩形.Width() - 编辑框宽度;
	}
	if (编辑框Y + 编辑框高度 > 客户区矩形.Height())
	{
		编辑框Y = 客户区矩形.Height() - 编辑框高度;
	}

	
	CRect 编辑框矩形(编辑框X, 编辑框Y, 编辑框X + 编辑框宽度, 编辑框Y + 编辑框高度);
	类_编辑框控件.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 编辑框矩形, this, IDC_EDIT1);
	类_编辑框控件.SetFocus();
	文本数值 = 列表框信息.列表框4->GetItemText(行, 列);
    文本地址 = 列表框信息.列表框4->GetItemText(行, 1);
	*结果 = 0;
	编辑框激活 = 4;
}

void 主窗口::列表框4_失去焦点编辑框()
{
	CString 编辑框获取的数值;
	类_编辑框控件.GetWindowText(编辑框获取的数值);
	写入数据(文本地址, 编辑框获取的数值, 列表框4_写入类型);
	列表框信息.列表框4->SetItemText(行, 列, 编辑框获取的数值);
	类_编辑框控件.DestroyWindow();
}




void 主窗口::列表框3_双击列表项(NMHDR* 消息, LRESULT* 结果) {
	LPNMITEMACTIVATE 激活项消息 = reinterpret_cast<LPNMITEMACTIVATE>(消息);
	行 = 激活项消息->iItem;
	列 = 激活项消息->iSubItem;

	CRect 单元格矩形区域;
	列表框信息.列表框3->GetSubItemRect(行, 列, LVIR_BOUNDS, 单元格矩形区域);

	POINT 鼠标位置;
	GetCursorPos(&鼠标位置);
	ScreenToClient(&鼠标位置);
	int 编辑框宽度 = 单元格矩形区域.Width();
	int 编辑框高度 = 单元格矩形区域.Height();
	int 编辑框X = 鼠标位置.x + 5; // 调整X坐标，使其在鼠标右下角
	int 编辑框Y = 鼠标位置.y + 5; // 调整Y坐标，使其在鼠标右下角

	CRect 客户区矩形;
	GetClientRect(&客户区矩形);
	if (编辑框X + 编辑框宽度 > 客户区矩形.Width())
	{
		编辑框X = 客户区矩形.Width() - 编辑框宽度;
	}
	if (编辑框Y + 编辑框高度 > 客户区矩形.Height())
	{
		编辑框Y = 客户区矩形.Height() - 编辑框高度;
	}

	CRect 编辑框矩形(编辑框X, 编辑框Y, 编辑框X + 编辑框宽度, 编辑框Y + 编辑框高度);
	类_编辑框控件.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 编辑框矩形, this, IDC_EDIT1);
	类_编辑框控件.SetFocus();
	文本数值 = 列表框信息.列表框3->GetItemText(行, 列);
	文本地址 = 列表框信息.列表框3->GetItemText(行, 0);
	*结果 = 0;
	编辑框激活 = 3;
}


ULONG64 主窗口::计算正确地址(ULONG64 基地址, ULONG 列, ULONG 数据类型) {
	ULONG64 正确地址 = 基地址;
	switch (数据类型) {
	case 字节数组类型:
		正确地址 += 列 - 1;
		break;
	case 二字节类型:
		正确地址 += (列 - 1) * 2;
		break;
	case 四字节类型:
	case 小数类型:
		正确地址 += (列 - 1) * 4;
		break;
	case 八字节类型:
	case 双浮点小数类型:
		正确地址 += (列 - 1) * 8;
		break;
	default:
		break;
	}
	return 正确地址;
}
void 主窗口::列表框3_失去焦点编辑框() {

	CString 编辑框获取的数值;
	类_编辑框控件.GetWindowText(编辑框获取的数值);
	ULONG64 基地址 = _tcstoull(文本地址, NULL, 16);
	ULONG64 正确地址 = 计算正确地址(基地址, 列, 当前数据类型);
	CString 正确的文本地址;
	正确的文本地址.Format(_T("%016llX"), 正确地址);
	写入数据(正确的文本地址, 编辑框获取的数值, 当前数据类型);
	类_编辑框控件.DestroyWindow();

}



void 主窗口::OnOK()
{
	if (编辑框激活 == 4) {
		CString 编辑框获取的数值;
		类_编辑框控件.GetWindowText(编辑框获取的数值);
		写入数据(文本地址, 编辑框获取的数值, 列表框4_写入类型);
		列表框信息.列表框4->SetItemText(行, 列, 编辑框获取的数值);
		类_编辑框控件.DestroyWindow();
		编辑框激活 = 0;
	}
	else if (编辑框激活 == 3) {
		CString 编辑框获取的数值;
		类_编辑框控件.GetWindowText(编辑框获取的数值);
		ULONG64 基地址 = _tcstoull(文本地址, NULL, 16);
		ULONG64 正确地址 = 计算正确地址(基地址, 列, 当前数据类型);
		CString 正确的文本地址;
		正确的文本地址.Format(_T("%016llX"), 正确地址);
		写入数据(正确的文本地址, 编辑框获取的数值, 当前数据类型);
		类_编辑框控件.DestroyWindow();
		ULONG64 地址 = 取编辑框数据到整数(编辑框信息.编辑框18);
		读取内存(列表框信息.列表框3,下拉框信息.下拉框2, 地址, 4096*10);
		编辑框激活 = 0;
	}
	


}


UINT __cdecl 窗口2线程(LPVOID pParam)
{
	
	AfxInitRichEdit2();

	窗口2 窗口;
	窗口.DoModal();

	return 0;
}

void 主窗口::OnBnClickedButton16()
{
	AfxBeginThread(窗口2线程, nullptr);
}




UINT 开启条件断点(LPVOID 参数) {

	while (是否开启条件断点) {
		CString 寄存器信息;
		CString 文本数值;
		ULONG64 数值;
		下拉框信息.下拉框4->GetWindowTextW(寄存器信息);
		编辑框信息.编辑框24->GetWindowTextW(文本数值);
		数值 = 文本转整数(文本数值);
		if (寄存器信息 == _T("RAX")) {
			条件断点.RAX = 数值;
		}
		else if (寄存器信息 == _T("RBX")) {
			条件断点.RBX = 数值;
		}
		else if (寄存器信息 == _T("RCX")) {
			条件断点.RCX = 数值;
		}
		else if (寄存器信息 == _T("RDX")) {
			条件断点.RDX = 数值;
		}
		else if (寄存器信息 == _T("RSI")) {
			条件断点.RSI = 数值;
		}
		else if (寄存器信息 == _T("RDI")) {
			条件断点.RDI = 数值;
		}
		else if (寄存器信息 == _T("RBP")) {
			条件断点.RBP = 数值;
		}
		else if (寄存器信息 == _T("RSP")) {
			条件断点.RSP = 数值;
		}
		else if (寄存器信息 == _T("R8")) {
			条件断点.R8 = 数值;
		}
		else if (寄存器信息 == _T("R9")) {
			条件断点.R9 = 数值;
		}
		else if (寄存器信息 == _T("R10")) {
			条件断点.R10 = 数值;
		}
		else if (寄存器信息 == _T("R11")) {
			条件断点.R11 = 数值;
		}
		else if (寄存器信息 == _T("R12")) {
			条件断点.R12 = 数值;
		}
		else if (寄存器信息 == _T("R13")) {
			条件断点.R13 = 数值;
		}
		else if (寄存器信息 == _T("R14")) {
			条件断点.R14 = 数值;
		}
		else if (寄存器信息 == _T("R15")) {
			条件断点.R15 = 数值;
		}
		设置断点(编辑框信息.编辑框20, 寄存器标识符.DR1, NULL);
	}
	return 0;
}


void 主窗口::OnBnClickedButton17()
{
	是否开启条件断点 = TRUE;
	AfxBeginThread(开启条件断点, nullptr);
	MessageBoxW(L"条件断点已开启", L"提示", MB_OK);

}

void 主窗口::OnBnClickedButton19()
{
	是否开启条件断点 = FALSE;
	条件断点 = { 0 };
	MessageBoxW(L"条件断点已关闭", L"提示", MB_OK);
}
