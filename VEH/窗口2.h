#pragma once
#include"主窗口.h"

// 窗口2 对话框

class 窗口2 : public CDialogEx
{
	DECLARE_DYNAMIC(窗口2)

public:
	窗口2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~窗口2();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();//回车键的回调函数
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOLEAN 初始化组件();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
private:
	CEdit 类_编辑框控件; // 使用自定义的编辑框类
	int 行;
	int 列;
	CString 文本地址;
	CString 文本类型;
	CString 描述文本;
	CString 是否锁定;

public:
	afx_msg void 列表框1_双击列表项(NMHDR* 消息, LRESULT* 结果);
	afx_msg void 列表框1_失去焦点编辑框();
	afx_msg void 列表框2_双击列表项(NMHDR* 消息, LRESULT* 结果);
	afx_msg void 列表框2_失去焦点编辑框();
	afx_msg void OnBnClickedButton8();
};





typedef struct 窗口2_编辑框指针 {

  CEdit* 窗口2_编辑框1;
  CEdit* 窗口2_编辑框2;
  CEdit* 窗口2_编辑框3;
  CEdit* 窗口2_编辑框4;
  CEdit* 窗口2_编辑框5;
  CEdit* 窗口2_编辑框6;
  CEdit* 窗口2_编辑框7;
  CEdit* 窗口2_编辑框8;
  CEdit* 窗口2_编辑框9;
  CEdit* 窗口2_编辑框10;
  CEdit* 窗口2_编辑框11;
}窗口2_编辑框指针, * P窗口2_编辑框指针;



typedef struct 窗口2_下拉框指针 {
    CComboBox* 窗口2_下拉框1;
	CComboBox* 窗口2_下拉框2;
	CComboBox* 窗口2_下拉框3;
	CComboBox* 窗口2_下拉框4;
	CComboBox* 窗口2_下拉框5;
	CComboBox* 窗口2_下拉框6;
	CComboBox* 窗口2_下拉框7;
}窗口2_下拉框指针, * P窗口2_下拉框指针;

typedef struct 窗口2_选择框指针 {
	CButton* 窗口2_选择框1;
	CButton* 窗口2_选择框2;
	CButton* 窗口2_选择框3;
	CButton* 窗口2_选择框4;
	CButton* 窗口2_选择框5;
	CButton* 窗口2_选择框6;
	CButton* 窗口2_选择框7;
}窗口2_选择框指针, * P窗口2_选择框指针;


typedef struct 窗口2_文本指针 {
	CStatic* 窗口2_文本1;
	CStatic* 窗口2_文本2;
	CStatic* 窗口2_文本3;
	CStatic* 窗口2_文本4;
	CStatic* 窗口2_文本5;
	CStatic* 窗口2_文本6;
	CStatic* 窗口2_文本7;
}窗口2_文本指针, * P窗口2_文本指针;



typedef struct 窗口2_进度条指针 {
	CProgressCtrl* 窗口2_进度条1;
	CProgressCtrl* 窗口2_进度条2;
	CProgressCtrl* 窗口2_进度条3;
	CProgressCtrl* 窗口2_进度条4;
	CProgressCtrl* 窗口2_进度条5;
	CProgressCtrl* 窗口2_进度条6;
	CProgressCtrl* 窗口2_进度条7;
}窗口2_进度条指针, * P窗口2_进度条指针;


typedef struct 窗口2_列表框指针 {
	CListCtrl* 窗口2_列表框1;
	CListCtrl* 窗口2_列表框2;
	CListCtrl* 窗口2_列表框3;
	CListCtrl* 窗口2_列表框4;
	CListCtrl* 窗口2_列表框5;
	CListCtrl* 窗口2_列表框6;
	CListCtrl* 窗口2_列表框7;
	CListCtrl* 窗口2_列表框8;
	CListCtrl* 窗口2_列表框9;
	CListCtrl* 窗口2_列表框10;
	CListCtrl* 窗口2_列表框11;
	CListCtrl* 窗口2_列表框12;
	CListCtrl* 窗口2_列表框13;
	CListCtrl* 窗口2_列表框14;
	CListCtrl* 窗口2_列表框15;
	CListCtrl* 窗口2_列表框16;
	CListCtrl* 窗口2_列表框17;
	CListCtrl* 窗口2_列表框18;
	CListCtrl* 窗口2_列表框19;
	CListCtrl* 窗口2_列表框20;
	CListCtrl* 窗口2_列表框21;
	CListCtrl* 窗口2_列表框22;
	CListCtrl* 窗口2_列表框23;
	CListCtrl* 窗口2_列表框24;

} 窗口2_列表框指针, * P窗口2_列表框指针;


typedef struct 扫描的内存 {
	ULONG64 地址数组[20000000]; 
	ULONG 地址数量; 
} 扫描的内存, * P扫描的内存;

extern BOOLEAN 函2_扫描内存(CEdit* 扫描编辑框, CEdit* 开始地址编辑框, CEdit* 结束地址编辑框, CListCtrl* 显示列表框, CComboBox* 类型下拉框, CButton* 十六进制按钮, CProgressCtrl* 进度条);
extern BOOLEAN 再次扫描(CEdit* 扫描编辑框, CComboBox* 类型下拉框, CListCtrl* 显示列表框, CButton* 十六进制按钮, CProgressCtrl* 进度条);
extern BOOLEAN 插入数据(CListCtrl* 列表框, CString 地址, CString 数值);
extern void 锁定器();
extern void 监控器();
extern BOOLEAN 修改数据(CListCtrl* 列表框, CString 地址, ULONG 类型, ULONG 行);