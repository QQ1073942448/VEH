#pragma once

#include "resource.h"		// 主符号
#include"framework.h"

// CVEH无痕HOOKApp
// 有关此类实现的信息，请参阅 VEH无痕HOOK.cpp
//

class CVEH无痕HOOKApp : public CWinApp
{
public:
	CVEH无痕HOOKApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
