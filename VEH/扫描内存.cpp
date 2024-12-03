#include"窗口2.h"
#include"resource.h"
#include <vector>
#include <sstream>
#include <unordered_set>

extern 窗口2_文本指针 文本信息;


扫描的内存 扫描的结构体[2] = { 0 };

void 更新UI() {
    MSG msg; // 消息结构体
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { // 处理消息队列中的消息
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


BOOLEAN 函2_扫描内存(CEdit* 扫描编辑框, CEdit* 开始地址编辑框, CEdit* 结束地址编辑框, CListCtrl* 显示列表框, CComboBox* 类型下拉框, CButton* 十六进制按钮, CProgressCtrl* 进度条) {
    文本信息.窗口2_文本1->SetWindowText(L"正在扫描");
    
    memset(扫描的结构体[1].地址数组, 0, sizeof(扫描的结构体[1]));

    扫描的结构体[1].地址数量 = 0;
    显示列表框->DeleteAllItems();
    进度条->SetPos(0);



    CString 类型 = 取下拉框到文本(类型下拉框);
    BOOL 是十六进制 = 十六进制按钮->GetCheck();
    CString 扫描内容;
    扫描编辑框->GetWindowText(扫描内容);

    ULONG64 开始地址 = 取编辑框数据到整数(开始地址编辑框);
    ULONG64 结束地址 = 取编辑框数据到整数(结束地址编辑框);

    auto 获取编辑框数据 = [&](CEdit* 编辑框) -> ULONG64 {
        CString 文本;
        编辑框->GetWindowText(文本);
        return 是十六进制 ? _tcstoull(文本, nullptr, 16) : _tcstoull(文本, nullptr, 10);
    };

    auto 获取浮点数数据 = [&](CEdit* 编辑框) -> float {
        CString 文本;
        编辑框->GetWindowText(文本);
        return _tstof(文本);
    };

  

    HANDLE 进程句柄 = GetCurrentProcess();
    MEMORY_BASIC_INFORMATION 内存信息1;
    MEMORY_BASIC_INFORMATION 内存信息2;
    ULONG 扫描计数 = 0; // 扫描计数变量
    ULONG 内存块总数 = 0;
    ULONG 内存块计数 = 0;

    // 预先计算内存块总数
    ULONG64 临时地址 = 开始地址;
    while (临时地址 < 结束地址) {
        if (VirtualQuery((LPCVOID)临时地址, &内存信息1, sizeof(内存信息1)) == sizeof(内存信息1)) {
            if (内存信息1.State == MEM_COMMIT && (内存信息1.Protect & PAGE_READONLY ||
                内存信息1.Protect & PAGE_READWRITE ||
                内存信息1.Protect & PAGE_WRITECOPY ||
                内存信息1.Protect & PAGE_EXECUTE_READ ||
                内存信息1.Protect & PAGE_EXECUTE_READWRITE ||
                内存信息1.Protect & PAGE_EXECUTE_WRITECOPY)) {
                ++内存块总数;
            }
           
        }
        临时地址 += 内存信息1.RegionSize;
    }
    // 实际扫描内存
    while (开始地址 < 结束地址) {
        if (VirtualQuery((LPCVOID)开始地址, &内存信息2, sizeof(内存信息2)) == sizeof(内存信息2)) {
            if (内存信息2.State == MEM_COMMIT && (内存信息2.Protect & PAGE_READONLY ||
                内存信息2.Protect & PAGE_READWRITE ||
                内存信息2.Protect & PAGE_WRITECOPY ||
                内存信息2.Protect & PAGE_EXECUTE_READ ||
                内存信息2.Protect & PAGE_EXECUTE_READWRITE ||
                内存信息2.Protect & PAGE_EXECUTE_WRITECOPY)) {
                ++内存块计数;
                BYTE* 缓冲区 = new BYTE[内存信息2.RegionSize];
                SIZE_T 读取字节数;
                if (ReadProcessMemory(进程句柄, 内存信息2.BaseAddress, 缓冲区, 内存信息2.RegionSize, &读取字节数)) {
                    auto 扫描内存 = [&](auto 扫描数据, auto 比较函数, SIZE_T 单位大小) {
                        for (SIZE_T 偏移 = 0; 偏移 < 读取字节数; 偏移 += 单位大小) {
                            decltype(扫描数据) 内存数据;
                            内存数据 = *reinterpret_cast<decltype(扫描数据)*>(缓冲区 + 偏移);
                            if (比较函数(内存数据, 扫描数据)) {
                                CString 数据字符串;
                                数据字符串.Format(_T("%s"), std::to_wstring(内存数据).c_str());
                                CString 地址字符串;
                                地址字符串.Format(_T("%llX"), (ULONG64)(内存信息2.BaseAddress) + 偏移);
                                int 行号 = 显示列表框->GetItemCount(); // 获取当前行数，即最后一行的索引
                                显示列表框->InsertItem(行号, 地址字符串); // 在最底部插入行
                                显示列表框->SetItemText(行号, 1, 数据字符串); // 设置第二列数据
                                扫描的结构体[1].地址数组[扫描计数] = (ULONG64)(内存信息2.BaseAddress) + 偏移;
                                扫描计数++;
                            }
                        }
                    };

                    // 根据类型进行数据扫描
                    if (类型 == _T("二字节")) {
                        USHORT 扫描数据 = static_cast<USHORT>(获取编辑框数据(扫描编辑框));
                        扫描内存(扫描数据, [](USHORT a, USHORT b) { return a == b; }, sizeof(USHORT));
                    }
                    else if (类型 == _T("四字节")) {
                        ULONG 扫描数据 = static_cast<ULONG>(获取编辑框数据(扫描编辑框));
                        扫描内存(扫描数据, [](ULONG a, ULONG b) { return a == b; }, sizeof(ULONG));
                    }
                    else if (类型 == _T("八字节")) {
                        ULONG64 扫描数据 = 获取编辑框数据(扫描编辑框);
                        扫描内存(扫描数据, [](ULONG64 a, ULONG64 b) { return a == b; }, sizeof(ULONG64));
                    }
                    else if (类型 == _T("单浮点")) {
                        float 扫描数据 = 获取浮点数数据(扫描编辑框);
                        扫描内存(扫描数据, [](float a, float b) { return fabs(a - b) < 0.00001; }, sizeof(float));
                    }
                    else if (类型 == _T("双浮点")) {
                        double 扫描数据 = 获取浮点数数据(扫描编辑框);
                        扫描内存(扫描数据, [](double a, double b) { return fabs(a - b) < 0.00001; }, sizeof(double));
                    }
                    else if (类型 == _T("字节数组")) {
                        UCHAR 字符集[256] = { 0 };
                        CString 文本 = 扫描内容;
                        SIZE_T 大小 = 0;
                        取文本字节集内容(字符集, 文本, &大小);
                        for (SIZE_T 偏移 = 0; 偏移 <= 读取字节数 - 大小; 偏移++) {
                            bool 匹配 = true;
                            for (SIZE_T i = 0; i < 大小; i++) {
                                if (缓冲区[偏移 + i] != 字符集[i]) {
                                    匹配 = false;
                                    break;
                                }
                            }
                            if (匹配) {
                                CString 数据字符串;
                                数据字符串.Format(_T("%s"), 文本);
                                CString 地址字符串;
                                地址字符串.Format(_T("%llx"), (ULONG64)(内存信息2.BaseAddress) + 偏移);
                                int 行号 = 显示列表框->InsertItem(0, 地址字符串);
                                显示列表框->SetItemText(行号, 1, 数据字符串);
                            }
                        }
                    }
                }

                delete[] 缓冲区;
              
            }
        }

      
        int 当前进度 = static_cast<int>((内存块计数 * 100) / 内存块总数);
        进度条->SetPos(当前进度);
        开始地址 += 内存信息2.RegionSize;
        更新UI();
    }
    扫描的结构体[1].地址数量 = 扫描计数;
    CString 计数文本;
    计数文本.Format(_T("当前结果：%d"), 扫描计数);
    文本信息.窗口2_文本1->SetWindowText(计数文本);
    return TRUE;
}


BOOLEAN 再次扫描(CEdit* 扫描编辑框, CComboBox* 类型下拉框, CListCtrl* 显示列表框, CButton* 十六进制按钮, CProgressCtrl* 进度条) {
    文本信息.窗口2_文本1->SetWindowText(L"正在扫描");
    显示列表框->DeleteAllItems();
    进度条->SetPos(0);
    std::unordered_set<ULONG64> 已插入的地址集合;
    已插入的地址集合.clear(); // 清空已插入的地址集合

    CString 扫描内容;
    扫描编辑框->GetWindowText(扫描内容);
    BOOL 是十六进制 = 十六进制按钮->GetCheck();
    ULONG 剩余地址数量 = 扫描的结构体[1].地址数量;
    ULONG 初始地址数量 = 剩余地址数量;
    ULONG 扫描计数 = 0; // 扫描计数变量

    CString 类型;
    类型下拉框->GetWindowText(类型);

    auto 获取编辑框数据 = [&](CEdit* 编辑框) -> ULONG64 {
        CString 文本;
        编辑框->GetWindowText(文本);
        return 是十六进制 ? _tcstoull(文本, nullptr, 16) : _tcstoull(文本, nullptr, 10);
    };

    auto 获取浮点数数据 = [&](CEdit* 编辑框) -> float {
        CString 文本;
        编辑框->GetWindowText(文本);
        return static_cast<float>(_tstof(文本));
    };

    auto 扫描内存 = [&](auto 扫描数据, auto 比较函数, SIZE_T 单位大小, BYTE* 缓冲区, SIZE_T 读取字节数, ULONG64 地址) {
        if (已插入的地址集合.find(地址) != 已插入的地址集合.end()) {
            扫描的结构体[1].地址数组[扫描计数] = 地址;         
            return; // 如果地址已存在，则跳过插入
        }

        decltype(扫描数据) 内存数据 = *reinterpret_cast<decltype(扫描数据)*>(缓冲区);
        if (比较函数(内存数据, 扫描数据)) {;
            已插入的地址集合.insert(地址); // 记录插入的地址
            扫描的结构体[1].地址数组[扫描计数] = 地址;
            CString 数据字符串;
            数据字符串.Format(_T("%s"), std::to_wstring(内存数据).c_str());
            CString 地址字符串;
            地址字符串.Format(_T("%llx"), 地址);
            int 行号 = 显示列表框->GetItemCount();
            显示列表框->InsertItem(行号, 地址字符串);
            显示列表框->SetItemText(行号, 1, 数据字符串);
            扫描计数++;
        }
    };

    剩余地址数量++;
    while (剩余地址数量 > 0) {
        ULONG64 地址 = 扫描的结构体[1].地址数组[剩余地址数量 - 1];
        扫描的结构体[1].地址数组[剩余地址数量 - 1] = 0;
        MEMORY_BASIC_INFORMATION 内存信息;
        if (VirtualQuery(reinterpret_cast<LPCVOID>(地址), &内存信息, sizeof(内存信息)) == sizeof(内存信息) &&
            内存信息.State == MEM_COMMIT &&
            (内存信息.Protect & PAGE_READONLY || 内存信息.Protect & PAGE_READWRITE ||
                内存信息.Protect & PAGE_WRITECOPY || 内存信息.Protect & PAGE_EXECUTE_READ ||
                内存信息.Protect & PAGE_EXECUTE_READWRITE || 内存信息.Protect & PAGE_EXECUTE_WRITECOPY)) {

            BYTE* 缓冲区 = reinterpret_cast<BYTE*>(地址);
            SIZE_T 读取字节数 = sizeof(ULONG64);  // 假设我们处理的是 8 字节数据

            if (类型 == _T("二字节")) {
                USHORT 扫描数据 = static_cast<USHORT>(获取编辑框数据(扫描编辑框));
                扫描内存(扫描数据, [](USHORT a, USHORT b) { return a == b; }, sizeof(USHORT), 缓冲区, 读取字节数, 地址);
            }
            else if (类型 == _T("四字节")) {
                ULONG 扫描数据 = static_cast<ULONG>(获取编辑框数据(扫描编辑框));
                扫描内存(扫描数据, [](ULONG a, ULONG b) { return a == b; }, sizeof(ULONG), 缓冲区, 读取字节数, 地址);
            }
            else if (类型 == _T("八字节")) {
                ULONG64 扫描数据 = 获取编辑框数据(扫描编辑框);
                扫描内存(扫描数据, [](ULONG64 a, ULONG64 b) { return a == b; }, sizeof(ULONG64), 缓冲区, 读取字节数, 地址);
            }
            else if (类型 == _T("单浮点")) {
                float 扫描数据 = 获取浮点数数据(扫描编辑框);
                扫描内存(扫描数据, [](float a, float b) { return fabs(a - b) < 0.00001; }, sizeof(float), 缓冲区, 读取字节数, 地址);
            }
            else if (类型 == _T("双浮点")) {
                double 扫描数据 = static_cast<double>(获取浮点数数据(扫描编辑框));
                扫描内存(扫描数据, [](double a, double b) { return fabs(a - b) < 0.00001; }, sizeof(double), 缓冲区, 读取字节数, 地址);
            }
            else if (类型 == _T("字节数组")) {
                UCHAR 字符集[256] = { 0 };
                CString 文本 = 扫描内容;
                SIZE_T 大小 = 0;
                取文本字节集内容(字符集, 文本, &大小);
                bool 匹配 = true;
                for (SIZE_T i = 0; i < 大小; i++) {
                    if (缓冲区[i] != 字符集[i]) {
                        匹配 = false;
                        break;
                    }
                }
                if (匹配) {
                    CString 数据字符串;
                    数据字符串.Format(_T("%s"), 文本);
                    CString 地址字符串;
                    地址字符串.Format(_T("%llX"), 地址);
                    int 行号 = 显示列表框->InsertItem(0, 地址字符串);
                    显示列表框->SetItemText(行号, 1, 数据字符串);
                    已插入的地址集合.insert(地址); // 记录插入的地址
                }
            }
        }

        剩余地址数量--;
        int 当前进度 = static_cast<int>(((初始地址数量 - 剩余地址数量) * 100) / 初始地址数量);
        进度条->SetPos(当前进度);
        更新UI();
    }
    进度条->SetPos(100);
    扫描的结构体[1].地址数量 = 扫描计数;
    CString 计数文本;
    计数文本.Format(_T("当前结果：%d"), 扫描计数);
    文本信息.窗口2_文本1->SetWindowText(计数文本);
    return TRUE;
}