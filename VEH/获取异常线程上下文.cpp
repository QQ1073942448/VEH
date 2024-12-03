#include"主窗口.h"

extern 编辑框指针 编辑框信息;


ULONG64 从编辑框获取数值(CEdit* 编辑框) {
    CString 文本;
    编辑框->GetWindowTextW(文本);
    std::wstringstream wss;
    wss << 文本.GetString();
    ULONG64 数值 = 0;
    wss >> std::hex >> 数值;
    return 数值;
}

BOOLEAN 获取异常线程上下文(_EXCEPTION_POINTERS* 异常线程的信息, P寄存器结构体 寄存器信息) {

	寄存器信息->RAX = 异常线程的信息->ContextRecord->Rax;
	寄存器信息->RBX = 异常线程的信息->ContextRecord->Rbx;
	寄存器信息->RCX = 异常线程的信息->ContextRecord->Rcx;
	寄存器信息->RDX = 异常线程的信息->ContextRecord->Rdx;
	寄存器信息->RSI = 异常线程的信息->ContextRecord->Rsi;
	寄存器信息->RDI = 异常线程的信息->ContextRecord->Rdi;
	寄存器信息->RBP = 异常线程的信息->ContextRecord->Rbp;
	寄存器信息->RSP = 异常线程的信息->ContextRecord->Rsp;
	寄存器信息->R8 = 异常线程的信息->ContextRecord->R8;
	寄存器信息->R9 = 异常线程的信息->ContextRecord->R9;
	寄存器信息->R10 = 异常线程的信息->ContextRecord->R10;
	寄存器信息->R11 = 异常线程的信息->ContextRecord->R11;
	寄存器信息->R12 = 异常线程的信息->ContextRecord->R12;
	寄存器信息->R13 = 异常线程的信息->ContextRecord->R13;
	寄存器信息->R14 = 异常线程的信息->ContextRecord->R14;
	寄存器信息->RIP = 异常线程的信息->ContextRecord->Rip;
	寄存器信息->XMM0 = 异常线程的信息->ContextRecord->Xmm0;
	寄存器信息->XMM1 = 异常线程的信息->ContextRecord->Xmm1;
	寄存器信息->XMM2 = 异常线程的信息->ContextRecord->Xmm2;
	寄存器信息->XMM3 = 异常线程的信息->ContextRecord->Xmm3;
	寄存器信息->XMM4 = 异常线程的信息->ContextRecord->Xmm4;
	寄存器信息->XMM5 = 异常线程的信息->ContextRecord->Xmm5;
	寄存器信息->XMM6 = 异常线程的信息->ContextRecord->Xmm6;
	寄存器信息->XMM7 = 异常线程的信息->ContextRecord->Xmm7;
	寄存器信息->XMM8 = 异常线程的信息->ContextRecord->Xmm8;
	寄存器信息->XMM9 = 异常线程的信息->ContextRecord->Xmm9;
	寄存器信息->XMM10 = 异常线程的信息->ContextRecord->Xmm10;
	寄存器信息->XMM11 = 异常线程的信息->ContextRecord->Xmm11;
	寄存器信息->XMM12 = 异常线程的信息->ContextRecord->Xmm12;
	寄存器信息->XMM13 = 异常线程的信息->ContextRecord->Xmm13;
	寄存器信息->XMM14 = 异常线程的信息->ContextRecord->Xmm14;
	寄存器信息->XMM15 = 异常线程的信息->ContextRecord->Xmm15;
	寄存器信息->DR0 = 异常线程的信息->ContextRecord->Dr0;
	寄存器信息->DR1 = 异常线程的信息->ContextRecord->Dr1;
	寄存器信息->DR2 = 异常线程的信息->ContextRecord->Dr2;
	寄存器信息->DR3 = 异常线程的信息->ContextRecord->Dr3;
	寄存器信息->DR6 = 异常线程的信息->ContextRecord->Dr6;
	寄存器信息->DR7 = 异常线程的信息->ContextRecord->Dr7;

	return TRUE;
}

BOOLEAN 向主窗口报告异常线程上下文(编辑框指针 编辑框信息, P寄存器结构体 寄存器信息) {

    auto to_hex_string = [](ULONG64 value) -> std::wstring {
        std::wstringstream wss;
        wss << std::hex << std::showbase << value;
        return wss.str();
    };

    编辑框信息.编辑框1->SetWindowTextW(to_hex_string(寄存器信息->RAX).c_str());
    编辑框信息.编辑框2->SetWindowTextW(to_hex_string(寄存器信息->RBX).c_str());
    编辑框信息.编辑框3->SetWindowTextW(to_hex_string(寄存器信息->RCX).c_str());
    编辑框信息.编辑框4->SetWindowTextW(to_hex_string(寄存器信息->RDX).c_str());
    编辑框信息.编辑框5->SetWindowTextW(to_hex_string(寄存器信息->RSI).c_str());
    编辑框信息.编辑框6->SetWindowTextW(to_hex_string(寄存器信息->RDI).c_str());
    编辑框信息.编辑框7->SetWindowTextW(to_hex_string(寄存器信息->RBP).c_str());
    编辑框信息.编辑框8->SetWindowTextW(to_hex_string(寄存器信息->RSP).c_str());
    编辑框信息.编辑框9->SetWindowTextW(to_hex_string(寄存器信息->R8).c_str());
    编辑框信息.编辑框10->SetWindowTextW(to_hex_string(寄存器信息->R9).c_str());
    编辑框信息.编辑框11->SetWindowTextW(to_hex_string(寄存器信息->R10).c_str());
    编辑框信息.编辑框12->SetWindowTextW(to_hex_string(寄存器信息->R11).c_str());
    编辑框信息.编辑框13->SetWindowTextW(to_hex_string(寄存器信息->R12).c_str());
    编辑框信息.编辑框14->SetWindowTextW(to_hex_string(寄存器信息->R13).c_str());
    编辑框信息.编辑框15->SetWindowTextW(to_hex_string(寄存器信息->R14).c_str());
    编辑框信息.编辑框16->SetWindowTextW(to_hex_string(寄存器信息->R15).c_str());
    编辑框信息.编辑框17->SetWindowTextW(to_hex_string(寄存器信息->RIP).c_str());

    return TRUE;
}

BOOLEAN 获取主窗口各个寄存器信息写回异常线程上下文(编辑框指针 编辑框信息, _EXCEPTION_POINTERS* 异常线程的信息) {
   
    异常线程的信息->ContextRecord->Rax = 从编辑框获取数值(编辑框信息.编辑框1);
    异常线程的信息->ContextRecord->Rbx = 从编辑框获取数值(编辑框信息.编辑框2);
    异常线程的信息->ContextRecord->Rcx = 从编辑框获取数值(编辑框信息.编辑框3);
    异常线程的信息->ContextRecord->Rdx = 从编辑框获取数值(编辑框信息.编辑框4);
    异常线程的信息->ContextRecord->Rsi = 从编辑框获取数值(编辑框信息.编辑框5);
    异常线程的信息->ContextRecord->Rdi = 从编辑框获取数值(编辑框信息.编辑框6);
    异常线程的信息->ContextRecord->Rbp = 从编辑框获取数值(编辑框信息.编辑框7);
    异常线程的信息->ContextRecord->Rsp = 从编辑框获取数值(编辑框信息.编辑框8);
    异常线程的信息->ContextRecord->R8 = 从编辑框获取数值(编辑框信息.编辑框9);
    异常线程的信息->ContextRecord->R9 = 从编辑框获取数值(编辑框信息.编辑框10);
    异常线程的信息->ContextRecord->R10 = 从编辑框获取数值(编辑框信息.编辑框11);
    异常线程的信息->ContextRecord->R11 = 从编辑框获取数值(编辑框信息.编辑框12);
    异常线程的信息->ContextRecord->R12 = 从编辑框获取数值(编辑框信息.编辑框13);
    异常线程的信息->ContextRecord->R13 = 从编辑框获取数值(编辑框信息.编辑框14);
    异常线程的信息->ContextRecord->R14 = 从编辑框获取数值(编辑框信息.编辑框15);
    异常线程的信息->ContextRecord->R15 = 从编辑框获取数值(编辑框信息.编辑框16);
    异常线程的信息->ContextRecord->Rip= 从编辑框获取数值(编辑框信息.编辑框17);
    return TRUE;
}


void 更新断点显示(CListCtrl* 列表框, P寄存器结构体 寄存器信息)
{
    ULONG 最大索引数量 = 列表框->GetItemCount();//获取最大索引
    BOOLEAN 找到匹配项 = FALSE; // 标志是否找到匹配项
    for (int i = 0; i < 最大索引数量; ++i)//开始遍历
    {
        CString 第一列文本 = 列表框->GetItemText(i, 0); // 获取第一列的文本
        ULONG64 地址值 = _tcstoull(第一列文本, NULL, 16); // 将文本转换为ULONG64

        if (地址值 == 寄存器信息->RIP)
        {
            找到匹配项 = TRUE; // 找到匹配项，设置标志为真
            列表框->SetItemText(i, 3, L"<--真"); // 更新第四列为“真”
        }
        else
        {
            列表框->SetItemText(i, 3, L"");   // 删除第四列不匹配的内容
        }
    }

    if (!找到匹配项)
    {
        int 行号 = 列表框->GetItemCount();
        列表框->SetItemText(行号, 3, L"<--真");

        // 更新反汇编区域打印至列表框
        反汇编内存区域(列表框, (UCHAR*)寄存器信息->RIP, 反汇编大小);
    }
}

void 清空汇编区断点显示(CListCtrl* 列表框) {
    ULONG 最大索引数量 = 列表框->GetItemCount(); // 获取最大索引
    for (int i = 0; i < 最大索引数量; ++i) {
        列表框->SetItemText(i, 3, L"");
    }
}

