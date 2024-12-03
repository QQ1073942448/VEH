#pragma once
#include"framework.h"
#include"Zyidi.h"
#include "窗口2.h"


#define 二字节类型 1
#define 四字节类型 2
#define 八字节类型 3
#define 小数类型 4
#define 双浮点小数类型 5
#define 字节数组类型 6
#define 反汇编大小 500


class 主窗口 : public CDialogEx
{
	DECLARE_DYNAMIC(主窗口)

public:
	主窗口(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~主窗口();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();//回车键的回调函数
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOLEAN 初始化组件();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
private:                                    
	CEdit 类_编辑框控件;
	int 行;
	int 列;

public:
	afx_msg void 列表框4_双击列表项(NMHDR* 消息, LRESULT* 结果);
	afx_msg void 列表框4_失去焦点编辑框();
	afx_msg void 列表框3_双击列表项(NMHDR* 消息, LRESULT* 结果);
	afx_msg void 列表框3_失去焦点编辑框();
	afx_msg ULONG64 计算正确地址(ULONG64 基地址, ULONG 列, ULONG 数据类型);

};




typedef struct 编辑框指针 {
	CEdit* 编辑框1;
	CEdit* 编辑框2;
	CEdit* 编辑框3;
	CEdit* 编辑框4;
	CEdit* 编辑框5;
	CEdit* 编辑框6;
	CEdit* 编辑框7;
	CEdit* 编辑框8;
	CEdit* 编辑框9;
	CEdit* 编辑框10;
	CEdit* 编辑框11;
	CEdit* 编辑框12;
	CEdit* 编辑框13;
	CEdit* 编辑框14;
	CEdit* 编辑框15;
	CEdit* 编辑框16;
	CEdit* 编辑框17;
	CEdit* 编辑框18;
	CEdit* 编辑框19;
	CEdit* 编辑框20;
	CEdit* 编辑框21;
	CEdit* 编辑框22;
	CEdit* 编辑框23;
	CEdit* 编辑框24;
	CEdit* 编辑框25;
	CEdit* 编辑框26;
} 编辑框指针, * P编辑框指针;



typedef struct 列表框指针 {
	CListCtrl* 列表框1;
	CListCtrl* 列表框2;
	CListCtrl* 列表框3;
	CListCtrl* 列表框4;
	CListCtrl* 列表框5;
	CListCtrl* 列表框6;
	CListCtrl* 列表框7;
	CListCtrl* 列表框8;
	CListCtrl* 列表框9;
	CListCtrl* 列表框10;
	CListCtrl* 列表框11;
	CListCtrl* 列表框12;
	CListCtrl* 列表框13;
	CListCtrl* 列表框14;
	CListCtrl* 列表框15;
	CListCtrl* 列表框16;
	CListCtrl* 列表框17;
	CListCtrl* 列表框18;
	CListCtrl* 列表框19;
	CListCtrl* 列表框20;
	CListCtrl* 列表框21;
	CListCtrl* 列表框22;
	CListCtrl* 列表框23;
	CListCtrl* 列表框24;

} 列表框指针, * P列表框指针;



typedef struct 下拉框指针 {
	CComboBox* 下拉框1;
	CComboBox* 下拉框2;
	CComboBox* 下拉框3;
	CComboBox* 下拉框4;
	CComboBox* 下拉框5;
	CComboBox* 下拉框6;
	CComboBox* 下拉框7;
}下拉框指针, * P下拉框指针;


typedef struct 寄存器结构体 {
	ULONG64 RAX;
	ULONG64 RBX;
	ULONG64 RCX;
	ULONG64 RDX;
	ULONG64 RSI;
	ULONG64 RDI;
	ULONG64 RBP;
	ULONG64 RSP;
	ULONG64 R8;
	ULONG64 R9;
	ULONG64 R10;
	ULONG64 R11;
	ULONG64 R12;
	ULONG64 R13;
	ULONG64 R14;
	ULONG64 R15;
	ULONG64 RIP;
	M128A XMM0;
	M128A XMM1;
	M128A XMM2;
	M128A XMM3;
	M128A XMM4;
	M128A XMM5;
	M128A XMM6;
	M128A XMM7;
	M128A XMM8;
	M128A XMM9;
	M128A XMM10;
	M128A XMM11;
	M128A XMM12;
	M128A XMM13;
	M128A XMM14;
	M128A XMM15;
	ULONG64 DR0;
	ULONG64 DR1;
	ULONG64 DR2;
	ULONG64 DR3;
	ULONG64 DR6;
	ULONG64 DR7;

} 寄存器结构体, * P寄存器结构体;


typedef struct 调试寄存器信息
{
	ULONG DR0;
	ULONG DR1;
	ULONG DR2;
	ULONG DR3;
	ULONG DR4;
	ULONG DR5;
	ULONG DR6;
	ULONG DR7;

}调试寄存器信息, * P调试寄存器信息;


extern  BOOLEAN 获取异常线程上下文(_EXCEPTION_POINTERS* 异常线程的信息, P寄存器结构体 寄存器信息);
extern  BOOLEAN 向主窗口报告异常线程上下文(编辑框指针 编辑框信息, P寄存器结构体 寄存器信息);
extern  BOOLEAN 设置断点(CEdit* 编辑框, ULONG 调试寄存器信息, ULONG64 下个断点地址);
extern  BOOLEAN 清空断点(_EXCEPTION_POINTERS* 异常线程的信息);
extern BOOLEAN 函_单步执行(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息);
extern  BOOLEAN 函_单步步过(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息);
extern BOOLEAN 函_单步步入(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息);
extern BOOLEAN 对比条件(_EXCEPTION_POINTERS* 异常线程的信息, 寄存器结构体 条件断点);
extern  size_t 获取指令长度(UCHAR* 指令地址);
extern  BOOLEAN 反汇编内存区域(CListCtrl* 列表框, UCHAR* 指令开始地址, SIZE_T 大小);
extern  ULONG64 取编辑框数据到整数(CEdit* 编辑框);
extern  CString 整数转十六进制文本(ULONG64 数值);
extern void 更新断点显示(CListCtrl* pListCtrl, P寄存器结构体 寄存器信息);
extern void 清空汇编区断点显示(CListCtrl* 列表框);
extern BOOLEAN 函_返回上级调用(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息);
extern BOOLEAN 向主窗口报告堆栈调用(CListCtrl* 列表框, P寄存器结构体 寄存器信息);
extern ULONG64 获取上级调用函数(P寄存器结构体 寄存器信息);
extern BOOLEAN 读取内存(CListCtrl* 列表框, CComboBox* 下拉框, ULONG64 起始地址, SIZE_T 长度);
extern BOOLEAN 函_类型读取(CListCtrl* 列表框, CComboBox* 下拉框, ULONG64 地址);
extern BOOLEAN 获取主窗口各个寄存器信息写回异常线程上下文(编辑框指针 编辑框信息, _EXCEPTION_POINTERS* 异常线程的信息);
extern CString 取下拉框到文本(CComboBox* 下拉框);
extern BOOLEAN 写入数据(CString 文本地址, CString 编辑框获取的数值, ULONG 写入类型);
extern BOOLEAN 取文本字节集内容(UCHAR* 需要充填的字节集, CString 字符集, SIZE_T* 实际充填大小);
extern CString 取编辑框文本(CEdit* 编辑框);
extern double 取编辑框数据到浮点(CEdit* 编辑框);
extern ULONG 取下拉框类型(CComboBox* 下拉框);
extern ULONG 取类型(CString 类型文本);
extern ULONG64 文本转整数(CString 文本);
extern USHORT 读短整数(ULONG64 内存地址,BOOLEAN* 是否成功);
extern ULONG 读整数(ULONG64 内存地址, BOOLEAN *是否成功);
extern ULONG64 读长整数(ULONG64 内存地址, BOOLEAN* 是否成功);
extern float 读浮点数(ULONG64 内存地址, BOOLEAN* 是否成功);
extern double 读双浮点(ULONG64 内存地址, BOOLEAN* 是否成功);
extern BOOLEAN 读字节集(UCHAR* 缓冲区, ULONG64 内存地址, SIZE_T 读取长度, BOOLEAN* 是否成功);
extern CString 整数转十进制文本(ULONG 数值);
