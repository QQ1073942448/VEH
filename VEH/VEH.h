#pragma once
#include"framework.h"
#include "resource.h"		// 主符号

// CVEHApp
// 有关此类实现的信息，请参阅 VEH.cpp
//

class CVEHApp : public CWinApp
{
public:
	CVEHApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
