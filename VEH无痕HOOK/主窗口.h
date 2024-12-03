#pragma once


// 主窗口 对话框

#include"resource.h"
#include"VEH无痕HOOK.h"
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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
