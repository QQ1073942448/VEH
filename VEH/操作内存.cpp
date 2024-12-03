#include"主窗口.h"
#include <vector>


 SIZE_T 读取长度 = 400;
 extern ULONG 列表框4_写入类型;
 extern ULONG 当前数据类型;

 BOOLEAN 初始化列表框格式(CListCtrl* 列表框, CString 选择文本) {
     // 清空所有列
     while (列表框->DeleteColumn(0));

     if (选择文本 == _T("字节")) {
         // 默认打印字节：17列
         列表框->InsertColumn(0, L"地址", 0, 100);
         for (int i = 1; i <= 16; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             列表框->InsertColumn(i, colName, 0, 40);
         }
     }
     else if (选择文本 == _T("二字节")) {
         // 短整数：9列
         列表框->InsertColumn(0, L"地址", 0, 100);
         for (int i = 1; i <= 8; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             列表框->InsertColumn(i, colName, 0, 80);
         }
     }
     else if (选择文本 == _T("四字节") || 选择文本 == _T("单浮点")) {
         // 四字节或单浮点：5列
         列表框->InsertColumn(0, L"地址", 0, 100);
         for (int i = 1; i <= 4; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             列表框->InsertColumn(i, colName, 0, 100);
         }
     }
     else if (选择文本 == _T("八字节") || 选择文本 == _T("双浮点")) {
         // 八字节或双浮点：3列
         列表框->InsertColumn(0, L"地址", 0, 100);
         for (int i = 1; i <= 2; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             列表框->InsertColumn(i, colName, 0, 200);
         }
     }
     else {
         return FALSE;
     }

     return TRUE;
 }


 extern 下拉框指针 下拉框信息;
 BOOLEAN 是否打印十六进制 = TRUE;
 BOOLEAN 读取内存(CListCtrl* 列表框, CComboBox* 下拉框, ULONG64 起始地址, SIZE_T 长度) {
   
     列表框->DeleteAllItems(); // 清除列表框中的所有内容
     
     // 获取下拉框内容
     CString 选择文本;
     下拉框->GetWindowText(选择文本);
     CString 进制文本;
     下拉框信息.下拉框3->GetWindowText(进制文本);
     if (进制文本 == _T("十六进制")) {


         是否打印十六进制 = TRUE;

     }
     else {
         是否打印十六进制 = FALSE;
     }
     // 初始化列表框格式
     if (!初始化列表框格式(列表框, 选择文本)) {
         return FALSE;
     }

     // 根据选择内容设置每行的字节数
     SIZE_T bytesPerLine = 16; // 默认是16字节
     if (选择文本 == _T("二字节")) {

         bytesPerLine = 16;
     }
     else if (选择文本 == _T("四字节") || 选择文本 == _T("单浮点")) {
         bytesPerLine = 16;
     }
     else if (选择文本 == _T("八字节") || 选择文本 == _T("双浮点")) {
         bytesPerLine = 16;
     }

     SIZE_T totalLines = (长度 + bytesPerLine - 1) / bytesPerLine;

     for (SIZE_T line = 0; line < totalLines; ++line) {
         ULONG64 当前地址 = 起始地址 + line * bytesPerLine;

         // 探测内存是否可读
         MEMORY_BASIC_INFORMATION mbi;
         if (VirtualQuery((LPCVOID)当前地址, &mbi, sizeof(mbi)) == 0 ||
             !(mbi.Protect & PAGE_READONLY) && !(mbi.Protect & PAGE_READWRITE) && !(mbi.Protect & PAGE_EXECUTE_READ) && !(mbi.Protect & PAGE_EXECUTE_READWRITE)) {

             CString strAddress;
             strAddress.Format(_T("0x%llX"), 当前地址);
             int rowIndex = 列表框->InsertItem(line, strAddress);
             for (int i = 1; i <= (选择文本 == _T("字节") ? 16 : (选择文本 == _T("二字节") ? 8 : (选择文本 == _T("四字节") || 选择文本 == _T("单浮点") ? 4 : 2))); ++i) {
                 列表框->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // 修改内存保护为可读可写可执行
         DWORD oldProtect;
         if (!VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
             CString strAddress;
             strAddress.Format(_T("0x%llX"), 当前地址);
             int rowIndex = 列表框->InsertItem(line, strAddress);
             for (int i = 1; i <= (选择文本 == _T("字节") ? 16 : (选择文本 == _T("二字节") ? 8 : (选择文本 == _T("四字节") || 选择文本 == _T("单浮点") ? 4 : 2))); ++i) {
                 列表框->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // 读取内存
         std::vector<BYTE> buffer(bytesPerLine, 0);
         SIZE_T bytesRead;
         if (!ReadProcessMemory(GetCurrentProcess(), (LPCVOID)当前地址, buffer.data(), bytesPerLine, &bytesRead)) {
             CString strAddress;
             strAddress.Format(_T("0x%llX"), 当前地址);
             int rowIndex = 列表框->InsertItem(line, strAddress);
             for (int i = 1; i <= (选择文本 == _T("字节") ? 16 : (选择文本 == _T("二字节") ? 8 : (选择文本 == _T("四字节") || 选择文本 == _T("单浮点") ? 4 : 2))); ++i) {
                 列表框->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // 打印对应字节和地址到控件中
         CString strAddress;
         strAddress.Format(_T("0x%llX"), 当前地址);
         int rowIndex = 列表框->InsertItem(line, strAddress);

         if (选择文本 == _T("字节")) {
             当前数据类型 = 字节数组类型;
             if (是否打印十六进制) {
                 for (SIZE_T i = 0; i < bytesRead; ++i) {
                     CString strByte;
                     strByte.Format(_T("%02X"), buffer[i]); // 十六进制打印
                     列表框->SetItemText(rowIndex, i + 1, strByte);
                 }
                 for (SIZE_T i = bytesRead; i < bytesPerLine; ++i) {
                     列表框->SetItemText(rowIndex, i + 1, _T("??"));
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead; ++i) {
                     CString strByte;
                     strByte.Format(_T("%d"), buffer[i]); // 十进制打印
                     列表框->SetItemText(rowIndex, i + 1, strByte);
                 }
             }
         }
         else if (选择文本 == _T("二字节")) {
             当前数据类型 = 二字节类型;
             if (是否打印十六进制) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(USHORT); ++i) {
                     USHORT value = *((USHORT*)(buffer.data() + i * sizeof(USHORT)));
                     CString strValue;
                     strValue.Format(_T("%04X"), value); // 十六进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(USHORT); ++i) {
                     USHORT value = *((USHORT*)(buffer.data() + i * sizeof(USHORT)));
                     CString strValue;
                     strValue.Format(_T("%u"), value); // 十进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (选择文本 == _T("四字节")) {
             当前数据类型 = 四字节类型;
             if (是否打印十六进制) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG); ++i) {
                     ULONG value = *((ULONG*)(buffer.data() + i * sizeof(ULONG)));
                     CString strValue;
                     strValue.Format(_T("%08X"), value); // 十六进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG); ++i) {
                     ULONG value = *((ULONG*)(buffer.data() + i * sizeof(ULONG)));
                     CString strValue;
                     strValue.Format(_T("%u"), value); // 十进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (选择文本 == _T("八字节")) {
             当前数据类型 = 八字节类型;
             if (是否打印十六进制) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG64); ++i) {
                     ULONG64 value = *((ULONG64*)(buffer.data() + i * sizeof(ULONG64)));
                     CString strValue;
                     strValue.Format(_T("%016llX"), value); // 十六进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG64); ++i) {
                     ULONG64 value = *((ULONG64*)(buffer.data() + i * sizeof(ULONG64)));
                     CString strValue;
                     strValue.Format(_T("%llu"), value); // 十进制打印
                     列表框->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (选择文本 == _T("单浮点")) {
             当前数据类型 = 小数类型;
             for (SIZE_T i = 0; i < bytesRead / sizeof(float); ++i) {
                 float value = *((float*)(buffer.data() + i * sizeof(float)));
                 CString strValue;
                 if (是否打印十六进制) {
                     strValue.Format(_T("%f"), value);
                 }
                 else {
                     strValue.Format(_T("%f"), value); // 十进制打印
                 }
                 列表框->SetItemText(rowIndex, i + 1, strValue);
             }
         }
         else if (选择文本 == _T("双浮点")) {
             当前数据类型 = 双浮点小数类型;
             for (SIZE_T i = 0; i < bytesRead / sizeof(double); ++i) {
                 double value = *((double*)(buffer.data() + i * sizeof(double)));
                 CString strValue;
                 if (是否打印十六进制) {
                     strValue.Format(_T("%lf"), value);
                 }
                 else {
                     strValue.Format(_T("%lf"), value); // 十进制打印
                 }
                 列表框->SetItemText(rowIndex, i + 1, strValue);
             }
         }
     }

     return TRUE;
 }





BOOLEAN 函_类型读取(CListCtrl* 列表框, CComboBox* 下拉框, ULONG64 地址 )
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((LPCVOID)地址, &mbi, sizeof(mbi)) == 0)
    {
        return FALSE;
    }

    if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD))
    {
        return FALSE;
    }

    if (mbi.RegionSize < 读取长度)
    {
        return FALSE;
    }

    CString 选择文本;
    下拉框->GetWindowText(选择文本);

    std::vector<CString> 地址数据;
    std::vector<CString> 数据;
    std::vector<CString> 偏移数据;
    地址数据.reserve(读取长度 / sizeof(ULONG64));
    数据.reserve(读取长度 / sizeof(ULONG64));
    偏移数据.reserve(读取长度 / sizeof(ULONG64));

    SIZE_T 偏移量 = 0;

    if (选择文本 == _T("二字节"))
    {
        for (SIZE_T i = 0; i < 读取长度 / sizeof(short); ++i)
        {
            列表框4_写入类型 = 二字节类型;
            short 值 = *((short*)(地址 + i * sizeof(short)));
            CString 地址项, 数据项, 偏移项;
            地址项.Format(_T("%016llX"), 地址 + i * sizeof(short));
            数据项.Format(_T("%d"), 值);
            偏移项.Format(_T("+%X"), 偏移量);
            偏移量 += sizeof(short);
            地址数据.push_back(地址项);
            数据.push_back(数据项);
            偏移数据.push_back(偏移项);
        }
    }
    else if (选择文本 == _T("四字节"))
    {
        for (SIZE_T i = 0; i < 读取长度 / sizeof(ULONG); ++i)
        {
            列表框4_写入类型 = 四字节类型;
            ULONG 值 = *((ULONG*)(地址 + i * sizeof(ULONG)));
            CString 地址项, 数据项, 偏移项;
            地址项.Format(_T("%016llX"), 地址 + i * sizeof(ULONG));
            数据项.Format(_T("%lu"), 值);
            偏移项.Format(_T("+%X"), 偏移量);
            偏移量 += sizeof(ULONG);
            地址数据.push_back(地址项);
            数据.push_back(数据项);
            偏移数据.push_back(偏移项);
        }
    }
    else if (选择文本 == _T("八字节"))
    {
        for (SIZE_T i = 0; i < 读取长度 / sizeof(ULONG64); ++i)
        {
            列表框4_写入类型 = 八字节类型;
            ULONG64 值 = *((ULONG64*)(地址 + i * sizeof(ULONG64)));
            CString 地址项, 数据项, 偏移项;
            地址项.Format(_T("%016llX"), 地址 + i * sizeof(ULONG64));
            数据项.Format(_T("%llu"), 值);
            偏移项.Format(_T("+%X"), 偏移量);
            偏移量 += sizeof(ULONG64);
            地址数据.push_back(地址项);
            数据.push_back(数据项);
            偏移数据.push_back(偏移项);
        }
    }
    else if (选择文本 == _T("单浮点"))
    {
        for (SIZE_T i = 0; i < 读取长度 / sizeof(float); ++i)
        {
            列表框4_写入类型 = 小数类型;
            float 值 = *((float*)(地址 + i * sizeof(float)));
            CString 地址项, 数据项, 偏移项;
            地址项.Format(_T("%016llX"), 地址 + i * sizeof(float));
            数据项.Format(_T("%f"), 值);
            偏移项.Format(_T("+%X"), 偏移量);
            偏移量 += sizeof(float);
            地址数据.push_back(地址项);
            数据.push_back(数据项);
            偏移数据.push_back(偏移项);
        }
    }
    else if (选择文本 == _T("双浮点"))
    {
        for (SIZE_T i = 0; i < 读取长度 / sizeof(double); ++i)
        {
            列表框4_写入类型 = 双浮点小数类型;
            double 值 = *((double*)(地址 + i * sizeof(double)));
            CString 地址项, 数据项, 偏移项;
            地址项.Format(_T("%016llX"), 地址 + i * sizeof(double));
            数据项.Format(_T("%lf"), 值);
            偏移项.Format(_T("+%X"), 偏移量);
            偏移量 += sizeof(double);
            地址数据.push_back(地址项);
            数据.push_back(数据项);
            偏移数据.push_back(偏移项);
        }
    }
    else
    {
       
        return FALSE;
    }

    // 清空列表框并添加数据
    列表框->DeleteAllItems();
    for (size_t i = 0; i < 地址数据.size(); ++i)
    {
        int nItem = 列表框->InsertItem(i, 偏移数据[i]); 
        列表框->SetItemText(nItem, 1, 地址数据[i]); 
        列表框->SetItemText(nItem, 2, 数据[i]);
    }

    return TRUE;
}



BOOLEAN 内存地址是否可读(ULONG64 内存地址, SIZE_T 探测长度) {
    MEMORY_BASIC_INFORMATION mbi;
    ULONG64 结束地址 = 内存地址 + 探测长度;

    while (内存地址 < 结束地址) {
        if (VirtualQuery((LPCVOID)内存地址, &mbi, sizeof(mbi)) == 0) {
            return FALSE; // 如果 VirtualQuery 失败，返回 FALSE
        }

        // 检查内存页面的保护属性是否允许读操作
        if (!((mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_READONLY) || (mbi.Protect & PAGE_EXECUTE_READ) || (mbi.Protect & PAGE_EXECUTE_READWRITE))) {
            return FALSE; // 如果内存不可读，返回 FALSE
        }

        // 前进到下一页
        内存地址 = (ULONG64)mbi.BaseAddress + mbi.RegionSize;
    }

    return TRUE; // 如果整个区域内存可读，返回 TRUE
}

USHORT 读短整数(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(USHORT))) {
        *是否成功 = TRUE;
        return *(USHORT*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

ULONG 读整数(ULONG64 内存地址, BOOLEAN *是否成功) {
    if (内存地址是否可读(内存地址, sizeof(ULONG))) {
        *是否成功 = TRUE;
        return *(ULONG*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

ULONG64 读长整数(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(ULONG64))) {
        *是否成功 = TRUE;
        return *(ULONG64*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

float 读浮点数(ULONG64 内存地址,BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(float))) {
        *是否成功 = TRUE;
        return *(float*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

double 读双浮点(ULONG64 内存地址, BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, sizeof(double))) {
        *是否成功 = TRUE;
        return *(double*)内存地址;
    }
    else {
        *是否成功 = FALSE;
        return 0;
    }
    return 0;
}

BOOLEAN 读字节集(UCHAR* 缓冲区, ULONG64 内存地址, SIZE_T 读取长度 , BOOLEAN* 是否成功) {
    if (内存地址是否可读(内存地址, 读取长度)) {
        memcpy(缓冲区, (void*)内存地址, 读取长度);////使用memcpy从源地址下复制数据到参数一的缓冲区中
        *是否成功 = TRUE;
        return TRUE;
    }
    else {
        *是否成功 = FALSE;
        return FALSE;
    }
    return FALSE;
}


//以下为写入函数
BOOLEAN 修改目标内存权限(ULONG64 内存地址, SIZE_T 修改长度, ULONG* 原本权限) {//修改目标内存属性页函数
    if (!VirtualProtect((LPVOID)内存地址, 修改长度, PAGE_EXECUTE_READWRITE, 原本权限)) {
        return FALSE;  ////如果执行到这说明该内存段可能有驱动保护
    }
    return TRUE;
}

BOOLEAN 恢复目标内存权限(ULONG64 内存地址, SIZE_T 修改长度, ULONG 原本权限) {//恢复原本属性页函数防止被游戏检测
    ULONG 权限缓冲区;
    if (!VirtualProtect((LPVOID)内存地址, 修改长度, 原本权限, &权限缓冲区)) {
        return FALSE;
    }
    return TRUE;
}

BOOLEAN 写短整数(ULONG64 内存地址, USHORT 写入数值) {
    ULONG  原本权限;
    if (!修改目标内存权限(内存地址, sizeof(USHORT), &原本权限)) {//不管内存页面是否可写，先修改目标内存权限为可读写可执行,在安全进行写入，否则该内存段如果不可写入会触发页面异常
        return FALSE;
    }
    *(USHORT*)内存地址 = 写入数值;
    if (!恢复目标内存权限(内存地址, sizeof(USHORT), 原本权限)) {//如果第一次成功修改了目标内存页面权限，第二次一般也不会有什么问题
        return FALSE;
    }
    return TRUE;
}

BOOLEAN 写整数(ULONG64 内存地址, ULONG 写入数值) {
    ULONG 原本权限;
    if (!修改目标内存权限(内存地址, sizeof(ULONG), &原本权限)) {
        return FALSE;
    }

    *(ULONG*)内存地址 = 写入数值;

    if (!恢复目标内存权限(内存地址, sizeof(ULONG), 原本权限)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN 写长整数(ULONG64 内存地址, ULONG64 写入数值) {
    ULONG 原本权限;
    if (!修改目标内存权限(内存地址, sizeof(ULONG64), &原本权限)) {
        return FALSE;
    }

    *(ULONG64*)内存地址 = 写入数值;

    if (!恢复目标内存权限(内存地址, sizeof(ULONG64), 原本权限)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN 写小数型(ULONG64 内存地址, float 写入数值) {
    ULONG 原本权限;
    if (!修改目标内存权限(内存地址, sizeof(float), &原本权限)) {
        return FALSE;
    }

    *(float*)内存地址 = 写入数值;

    if (!恢复目标内存权限(内存地址, sizeof(float), 原本权限)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN 写双浮点小数型(ULONG64 内存地址, double 写入数值) {
    ULONG 原本权限;
    if (!修改目标内存权限(内存地址, sizeof(double), &原本权限)) {
        return FALSE;
    }

    *(double*)内存地址 = 写入数值;

    if (!恢复目标内存权限(内存地址, sizeof(double), 原本权限)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN 写字节集(ULONG64 内存地址, UCHAR* 缓冲区, SIZE_T 长度) {
    ULONG 原本权限;
    if (!修改目标内存权限(内存地址, 长度, &原本权限)) {
        return FALSE;
    }
    memcpy((LPVOID)内存地址, 缓冲区, 长度);//这里一样，传递UCHAR*字节集的缓冲区使用memcpy函数复制进去

    if (!恢复目标内存权限(内存地址, 长度, 原本权限)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN 读取文本转宽字符串(const char* 文本地址, WCHAR* 宽字符串) {//采用宽字符处理，因为WINDOWS以及游戏很少用ANSI字符，基本都是宽字符的数据
    SIZE_T 宽字符串长度计算 = MultiByteToWideChar(CP_UTF8, 0, 文本地址, -1, NULL, 0);//这里使用MultiByteToWideChar函数自动计算该内存地址下的数据长度得到文本长度
    if (MultiByteToWideChar(CP_UTF8, 0, 文本地址, -1, 宽字符串, 宽字符串长度计算) == 0) {//将该内存地址下的文本数据复制到传递来的宽字符串缓冲区中，注意缓冲区大小自己定义就好
        return FALSE;
    }

    return TRUE;
}




BOOLEAN 写入数据(CString 文本地址, CString 编辑框获取的数值, ULONG 列表框4_写入类型) {
    // 将文本地址转换为数值地址
    ULONG64 地址 = _tcstoull(文本地址, NULL, 16);

    // 将编辑框获取的数值转换为合适的数据类型
    if (列表框4_写入类型 == 二字节类型) {
        USHORT 数值 = static_cast<USHORT>(_tstoi(编辑框获取的数值));
        if (写短整数(地址, 数值)) {
            return TRUE;
        }
    }
    else if (列表框4_写入类型 == 四字节类型) {
        ULONG 数值 = static_cast<ULONG>(_tstoi(编辑框获取的数值));
        if (写整数(地址, 数值)) {
            return TRUE;
        }
    }
    else if (列表框4_写入类型 == 八字节类型) {
        ULONG64 数值 = _tcstoull(编辑框获取的数值, NULL, 10);
        if (写长整数(地址, 数值)) {
            return TRUE;
        }
    }
    else if (列表框4_写入类型 == 小数类型) {
        float 数值 = static_cast<float>(_tstof(编辑框获取的数值));
        if (写小数型(地址, 数值)) {
            return TRUE;
        }
    }
    else if (列表框4_写入类型 == 双浮点小数类型) {
        double 数值 = static_cast<double>(_tstof(编辑框获取的数值));
        if (写双浮点小数型(地址, 数值)) {
            return TRUE;
        }
    }
    else if (列表框4_写入类型 == 字节数组类型) {
        std::vector<UCHAR> 数组;
        std::wistringstream stream(编辑框获取的数值.GetString());
        std::wstring token;
        while (stream >> token) {
            UCHAR byte = static_cast<UCHAR>(_tcstoul(token.c_str(), NULL, 16));
            数组.push_back(byte);
        }
        if (写字节集(地址, 数组.data(), 数组.size())) {
            return TRUE;
        }
    }

    return FALSE;
}




