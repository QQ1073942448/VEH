#include"主窗口.h"

BOOLEAN 向主窗口报告堆栈调用(CListCtrl* 列表框, P寄存器结构体 寄存器信息) {
    // 获取返回地址
    ULONG64 返回地址 = 获取上级调用函数(寄存器信息);
    CStringW 地址字符串;
    地址字符串.Format(L"%p", 返回地址);

    // 获取函数参数
    DWORD 参数1 = 寄存器信息->RCX;
    DWORD 参数2 = 寄存器信息->RDX;
    DWORD 参数3 = 寄存器信息->R8;
    DWORD 参数4 = 寄存器信息->R9;

    // 将参数转换为字符串，如果参数无效则显示“无”
    CStringW 参数1字符串;
    if (参数1 != 0) {
        参数1字符串.Format(L"%p", 参数1);
    }
    else {
        参数1字符串 = L"无";
    }

    CStringW 参数2字符串;
    if (参数2 != 0) {
        参数2字符串.Format(L"%p", 参数2);
    }
    else {
        参数2字符串 = L"无";
    }

    CStringW 参数3字符串;
    if (参数3 != 0) {
        参数3字符串.Format(L"%p", 参数3);
    }
    else {
        参数3字符串 = L"无";
    }

    CStringW 参数4字符串;
    if (参数4 != 0) {
        参数4字符串.Format(L"%p", 参数4);
    }
    else {
        参数4字符串 = L"无";
    }

    // 获取帧指针
    ULONG64 帧指针 = 寄存器信息->RBP;

    // 将帧指针转换为字符串
    CStringW 帧指针字符串;
    帧指针字符串.Format(L"%p", 帧指针);

    // 插入新的行
    int 行号 = 列表框->GetItemCount();
    列表框->InsertItem(行号, 地址字符串); // 第一列是返回地址
    列表框->SetItemText(行号, 1, 参数1字符串); // 第二列是参数1
    列表框->SetItemText(行号, 2, 参数2字符串); // 第三列是参数2
    列表框->SetItemText(行号, 3, 参数3字符串); // 第四列是参数3
    列表框->SetItemText(行号, 4, 参数4字符串); // 第五列是参数4
    列表框->SetItemText(行号, 5, 帧指针字符串); // 第六列是帧指针

    return TRUE;
}
