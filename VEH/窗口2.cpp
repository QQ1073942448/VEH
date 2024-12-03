// 窗口2.cpp: 实现文件
//

#include "VEH.h"
#include "窗口2.h"
#include "afxdialogex.h"


// 窗口2 对话框

IMPLEMENT_DYNAMIC(窗口2, CDialogEx)

窗口2::窗口2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

窗口2::~窗口2()
{
}

void 窗口2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	窗口2::初始化组件();
}




BEGIN_MESSAGE_MAP(窗口2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &窗口2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK2, &窗口2::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON2, &窗口2::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &窗口2::列表框1_双击列表项)
	ON_EN_KILLFOCUS(IDC_EDIT1, &窗口2::列表框1_失去焦点编辑框)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &窗口2::列表框2_双击列表项)
	ON_EN_KILLFOCUS(IDC_EDIT2, &窗口2::列表框2_失去焦点编辑框)
	ON_BN_CLICKED(IDC_BUTTON3, &窗口2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &窗口2::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &窗口2::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &窗口2::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &窗口2::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &窗口2::OnBnClickedButton8)
END_MESSAGE_MAP()


// 窗口2 消息处理程序


窗口2_编辑框指针 编辑框信息 = { 0 };
窗口2_下拉框指针 下拉框信息 = { 0 };
窗口2_列表框指针 列表框信息 = { 0 };
窗口2_选择框指针 选择框信息 = { 0 };
窗口2_文本指针 文本信息 = { 0 };
窗口2_进度条指针 进度条信息 = { 0 };
BOOLEAN 是否添加地址 = FALSE;


BOOLEAN 初始化下拉框1(CComboBox* 窗口2_下拉框) {


	窗口2_下拉框->AddString(_T("二字节"));
	窗口2_下拉框->AddString(_T("四字节"));
	窗口2_下拉框->AddString(_T("八字节"));
	窗口2_下拉框->AddString(_T("单浮点"));
	窗口2_下拉框->AddString(_T("双浮点"));
	窗口2_下拉框->AddString(_T("字节数组"));


	// 将默认选择设置为 "四字节"
	int 默认选择 = 窗口2_下拉框->FindStringExact(-1, _T("四字节"));
	if (默认选择 != CB_ERR)
	{
		窗口2_下拉框->SetCurSel(默认选择);
	}

	CRect 矩形区域;
	窗口2_下拉框->GetWindowRect(&矩形区域);
	int 最大区域 = 矩形区域.Height() + 7 * 窗口2_下拉框->GetItemHeight(0); // 6 是要显示的行数
	窗口2_下拉框->SetWindowPos(NULL, 0, 0, 矩形区域.Width(), 最大区域, SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}


BOOLEAN 初始化列表框1(CListCtrl* 窗口2_列表框1) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(窗口2_列表框1->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(窗口2_列表框1->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 窗口2_列表框1->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	窗口2_列表框1->SetExtendedStyle(dstyle);
	窗口2_列表框1->InsertColumn(0, L"数值", 0, 150);
	窗口2_列表框1->InsertColumn(0, L"地址", 0, 150);
	窗口2_列表框1->SetItemState(0, 0, LVIS_SELECTED);
	return TRUE;

}


BOOLEAN 初始化列表框2(CListCtrl* 窗口2_列表框2) {

	LONG_PTR lStyle;
	lStyle = GetWindowLongPtr(窗口2_列表框2->m_hWnd, GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLongPtr(窗口2_列表框2->m_hWnd, GWL_STYLE, lStyle);
	DWORD dstyle = 窗口2_列表框2->GetExtendedStyle();
	dstyle |= LVS_EX_FULLROWSELECT;
	dstyle |= LVS_EX_GRIDLINES;
	窗口2_列表框2->SetExtendedStyle(dstyle);
	窗口2_列表框2->InsertColumn(0, L"数值", 0, 150);
	窗口2_列表框2->InsertColumn(0, L"类型", 0, 150);
	窗口2_列表框2->InsertColumn(0, L"地址", 0, 150);
	窗口2_列表框2->InsertColumn(0, L"描述", 0, 250);
	窗口2_列表框2->InsertColumn(0, L"是否锁定", 0, 100);
	窗口2_列表框2->SetItemState(0, 0, LVIS_SELECTED);
	
	return TRUE;
}



BOOLEAN 初始化编辑框2(CEdit* 窗口2_编辑框2) {

	窗口2_编辑框2->SetWindowTextW(L"0");//初始化编辑框最小地址0
	return TRUE;//返回成功
}


BOOLEAN 初始化编辑框3(CEdit* 窗口2_编辑框3) {

	窗口2_编辑框3->SetWindowTextW(L"7FFFFFFFFFFF");//初始化编辑框最大地址7FFFFFFFFFFF
	return TRUE;//返回成功
}

BOOLEAN 初始化进度条1(CProgressCtrl* 窗口2_编辑框3) {

	窗口2_编辑框3->SetBarColor(RGB(0, 255, 0)); // 绿色
	窗口2_编辑框3->SetPos(0);
	return TRUE;//返回成功
}


BOOLEAN 窗口2::初始化组件() {

	编辑框信息.窗口2_编辑框1= (CEdit*)GetDlgItem(IDC_EDIT1);//初始化编辑框1
	编辑框信息.窗口2_编辑框2 = (CEdit*)GetDlgItem(IDC_EDIT2);//初始化编辑框2
	编辑框信息.窗口2_编辑框3 = (CEdit*)GetDlgItem(IDC_EDIT3);//初始化编辑框3

	初始化编辑框2(编辑框信息.窗口2_编辑框2);//初始化编辑框2内容,定义最小地址范围
	初始化编辑框3(编辑框信息.窗口2_编辑框3);//初始化编辑框3内容，定义最大地址范围

	下拉框信息.窗口2_下拉框1= (CComboBox*)GetDlgItem(IDC_COMBO1);//初始化下拉框1
	下拉框信息.窗口2_下拉框2 = (CComboBox*)GetDlgItem(IDC_COMBO2);//初始化下拉框1
	初始化下拉框1(下拉框信息.窗口2_下拉框1);//初始下拉框1内容;
	初始化下拉框1(下拉框信息.窗口2_下拉框2);//初始下拉框1内容;
		
	列表框信息.窗口2_列表框1 = (CListCtrl*)GetDlgItem(IDC_LIST1);//初始化列表框1
	列表框信息.窗口2_列表框2 = (CListCtrl*)GetDlgItem(IDC_LIST2);//初始化列表框2
	初始化列表框1(列表框信息.窗口2_列表框1);//初始化列表框1内容
	初始化列表框2(列表框信息.窗口2_列表框2);//初始化列表框2内容




	选择框信息.窗口2_选择框2= (CButton*)GetDlgItem(IDC_CHECK2);//初始化选择框1


	文本信息.窗口2_文本1= (CStatic*)GetDlgItem(IDC_STATIC1);//初始化选择框1



	进度条信息.窗口2_进度条1= (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	初始化进度条1(进度条信息.窗口2_进度条1);
    监控器();
	锁定器();
	return TRUE;//返回成功
}



void 窗口2::OnBnClickedButton1()
{
	函2_扫描内存(编辑框信息.窗口2_编辑框1, 编辑框信息.窗口2_编辑框2, 编辑框信息.窗口2_编辑框3,列表框信息.窗口2_列表框1, 下拉框信息.窗口2_下拉框1, 选择框信息.窗口2_选择框2,进度条信息.窗口2_进度条1);

}




void 窗口2::OnBnClickedCheck2()
{
	BOOLEAN 是十六进制 = 选择框信息.窗口2_选择框2->GetCheck();
	CString 扫描内容;
	编辑框信息.窗口2_编辑框1->GetWindowText(扫描内容);

	if (是十六进制) {
		// 如果是十六进制，将十进制文本转换为十六进制文本
		ULONG64 十进制值 = _tcstoull(扫描内容, nullptr, 10);
		CString 十六进制字符串;
		十六进制字符串.Format(_T("%llX"), 十进制值);
		编辑框信息.窗口2_编辑框1->SetWindowText(十六进制字符串);
	}
	else {
		// 如果是十进制，将十六进制文本转换为十进制文本
		ULONG64 十六进制值 = _tcstoull(扫描内容, nullptr, 16);
		CString 十进制字符串;
		十进制字符串.Format(_T("%llu"), 十六进制值);
		编辑框信息.窗口2_编辑框1->SetWindowText(十进制字符串);
	}

}


void 窗口2::OnBnClickedButton2()
{
	再次扫描(编辑框信息.窗口2_编辑框1, 下拉框信息.窗口2_下拉框1, 列表框信息.窗口2_列表框1, 选择框信息.窗口2_选择框2, 进度条信息.窗口2_进度条1);
}



void 窗口2::OnOK()
{
	CString 编辑框获取的内容;
	类_编辑框控件.GetWindowText(编辑框获取的内容);
	if (列 == 1) {
		列表框信息.窗口2_列表框2->SetItemText(行, 1, 编辑框获取的内容); // 第二列是备注
	}
	else if (列 == 2) {
		列表框信息.窗口2_列表框2->SetItemText(行, 2, 编辑框获取的内容);//第三列是地址
		文本地址 = 列表框信息.窗口2_列表框2->GetItemText(行, 2);//重新获取文本地址
		ULONG 类型 = 取类型(文本类型);//获取文本类型
		修改数据(列表框信息.窗口2_列表框2, 文本地址, 类型, 行);
	}
	else if (列 == 4) {
		ULONG 类型 = 取类型(文本类型);
		写入数据(文本地址, 编辑框获取的内容, 类型);
		列表框信息.窗口2_列表框2->SetItemText(行, 列, 编辑框获取的内容);//第五列是数值
	}
	else if(是否添加地址) {
		ULONG64 地址 = 文本转整数(编辑框获取的内容);
		BOOLEAN 是否成功;
		ULONG 数值 = 读整数(地址, &是否成功);
		CString 文本数值;
		if (!是否成功) {
			文本数值 = _T("????");
		}
		else {
			文本数值 = 整数转十进制文本(数值);
		}

		插入数据(列表框信息.窗口2_列表框2, 编辑框获取的内容, 文本数值);
		是否添加地址 = FALSE;

	}

	类_编辑框控件.DestroyWindow();
	return;
}


void 窗口2::列表框1_双击列表项(NMHDR* 消息, LRESULT* 结果) {
	CString 文本数值;
	CString 文本地址;
	LPNMITEMACTIVATE 激活项消息 = reinterpret_cast<LPNMITEMACTIVATE>(消息);
	行 = 激活项消息->iItem;
	列 = 激活项消息->iSubItem;
	文本地址 = 列表框信息.窗口2_列表框1->GetItemText(行, 0);
	文本数值 = 列表框信息.窗口2_列表框1->GetItemText(行, 1);


	插入数据(列表框信息.窗口2_列表框2, 文本地址, 文本数值);
	*结果 = 0;
 }

void 窗口2::列表框1_失去焦点编辑框()
{

}


void 窗口2::列表框2_双击列表项(NMHDR* 消息, LRESULT* 结果) {
	LPNMITEMACTIVATE 激活项消息 = reinterpret_cast<LPNMITEMACTIVATE>(消息);
	行 = 激活项消息->iItem;
	列 = 激活项消息->iSubItem;

	if (列 == 0) {
		是否锁定 = 列表框信息.窗口2_列表框2->GetItemText(行, 0);
		if (是否锁定 == _T("否")) {
			列表框信息.窗口2_列表框2->SetItemText(行, 0, L"是"); // 第二列是备注
		}
		else {
			列表框信息.窗口2_列表框2->SetItemText(行, 0, L"否"); // 第二列是备注
		}
		return;
	}
	else if (列 == 3) {
		CString 下拉框文本;
		下拉框信息.窗口2_下拉框2->GetWindowTextW(下拉框文本);
		列表框信息.窗口2_列表框2->SetItemText(行, 3, 下拉框文本);
		return;
	}
	

	
	CRect 单元格矩形区域;
	列表框信息.窗口2_列表框2->GetSubItemRect(行, 列, LVIR_BOUNDS, 单元格矩形区域);

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
	文本地址 = 列表框信息.窗口2_列表框2->GetItemText(行, 2);//取第三行地址数据
	文本类型= 列表框信息.窗口2_列表框2->GetItemText(行, 3);
	

	*结果 = 0;
}

void 窗口2::列表框2_失去焦点编辑框()
{
	CString 编辑框获取的内容;
	类_编辑框控件.GetWindowText(编辑框获取的内容);
	if (列 == 1) {
		列表框信息.窗口2_列表框2->SetItemText(行, 1, 编辑框获取的内容); // 第二列是备注
	}
	else if (列 == 2) {
		列表框信息.窗口2_列表框2->SetItemText(行, 2, 编辑框获取的内容);//第三列是地址
		文本地址 = 列表框信息.窗口2_列表框2->GetItemText(行, 2);//重新获取文本地址
		ULONG 类型 = 取类型(文本类型);//获取文本类型
		修改数据(列表框信息.窗口2_列表框2, 文本地址, 类型, 行);
	}
	else if (列 == 4) {
		ULONG 类型 = 取类型(文本类型);
		写入数据(文本地址, 编辑框获取的内容, 类型);
		列表框信息.窗口2_列表框2->SetItemText(行, 列, 编辑框获取的内容);//第五列是数值
	}
	类_编辑框控件.DestroyWindow();
	return;
}




void 窗口2::OnBnClickedButton3()
{
	列表框信息.窗口2_列表框2->DeleteAllItems();
}


void 窗口2::OnBnClickedButton5()
{

	// 获取所有选中的项
	POSITION 第一个选中项 = 列表框信息.窗口2_列表框2->GetFirstSelectedItemPosition();
	CArray<int, int> 所有选中项; // 使用 int 类型

	while (第一个选中项)
	{
		int 行索引 = 列表框信息.窗口2_列表框2->GetNextSelectedItem(第一个选中项);
		所有选中项.Add(行索引);
	}

	// 从最后一个选中的项开始删除
	for (int i = 所有选中项.GetSize() - 1; i >= 0; --i)
	{
		列表框信息.窗口2_列表框2->DeleteItem(所有选中项[i]);
	}
}



void 窗口2::OnBnClickedButton4()
{
	// 获取当前鼠标位置
	POINT 鼠标位置;
	GetCursorPos(&鼠标位置);
	ScreenToClient(&鼠标位置);

	// 确定编辑框的位置和大小
	int 编辑框宽度 = 200; // 根据需要设置编辑框的宽度
	int 编辑框高度 = 20;  // 根据需要设置编辑框的高度
	int 编辑框X = 鼠标位置.x + 10; // 调整X坐标，使其在鼠标右下角
	int 编辑框Y = 鼠标位置.y + 10; // 调整Y坐标，使其在鼠标右下角

	// 确保编辑框不会超出窗口的边界
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

	// 创建并显示编辑框
	CRect 编辑框矩形(编辑框X, 编辑框Y, 编辑框X + 编辑框宽度, 编辑框Y + 编辑框高度);
	类_编辑框控件.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 编辑框矩形, this, IDC_EDIT1);
	类_编辑框控件.SetFocus();
	是否添加地址 = TRUE;
}


void 窗口2::OnBnClickedButton6()
{
	ShowWindow(SW_MINIMIZE);
}


void 窗口2::OnBnClickedButton7()
{
	// 获取选中项的位置
	POSITION 标记位置 = 列表框信息.窗口2_列表框1->GetFirstSelectedItemPosition();

	while (标记位置 != NULL)
	{
		// 获取选中行的索引
		int 行索引起始 = 列表框信息.窗口2_列表框1->GetNextSelectedItem(标记位置);

		// 获取选中行第一列（列索引为0）的内容
		CString 地址内容 = 列表框信息.窗口2_列表框1->GetItemText(行索引起始, 0);

		// 将获取的内容插入到 窗口2_列表框2 的第三列（列索引为2）
		int 行索引 = 列表框信息.窗口2_列表框2->InsertItem(行索引起始, _T("")); // 插入新行
		CString 下拉框选中的文本;
		下拉框信息.窗口2_下拉框1->GetWindowTextW(下拉框选中的文本);
		列表框信息.窗口2_列表框2->SetItemText(行索引, 0, L"否");
		列表框信息.窗口2_列表框2->SetItemText(行索引, 1, L"无描述");
		列表框信息.窗口2_列表框2->SetItemText(行索引, 2, 地址内容);
		列表框信息.窗口2_列表框2->SetItemText(行索引, 3, 下拉框选中的文本);
	}

	if (列表框信息.窗口2_列表框1->GetSelectedCount() == 0)
	{
		// 没有选中任何项
		MessageBoxA(nullptr, "没有选中任何内容", "提示", MB_OK);
	}

}



UINT __cdecl 窗口3线程(LPVOID pParam)
{

	AfxInitRichEdit2();

	窗口2 窗口;
	窗口.DoModal();

	return 0;
}


void 窗口2::OnBnClickedButton8()
{
   
	AfxBeginThread(窗口3线程, nullptr);
}
