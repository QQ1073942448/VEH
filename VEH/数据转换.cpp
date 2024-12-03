#include"主窗口.h"


ULONG64 取编辑框数据到整数(CEdit* 编辑框)
{  // 获取编辑框中的文本
    CString 文本;
    编辑框->GetWindowText(文本);

    // 将 CString 转换为标准字符串
    CT2CA 转换(文本);
    std::string 标准字符串(转换);

   
      ULONG64 地址 = std::stoull(标准字符串, nullptr, 16);
      return 地址;
 
}

CString 取下拉框到文本(CComboBox* 下拉框) {

    CString 文本;
    下拉框->GetWindowText(文本);
    return 文本;
}


CString 整数转十六进制文本(ULONG64 数值)
{
    // 将数值转换为宽字符文本
    CString 文本;
    文本.Format(L"%016llX", 数值);

    // 返回宽字符文本
    return 文本;
}


BOOLEAN  取文本字节集内容(UCHAR* 需要充填的字节集, CString 字符集 ,SIZE_T *实际充填大小) {
    std::vector<UCHAR> 数组;
    std::wstring 字符串 = static_cast<LPCTSTR>(字符集);
    std::wistringstream stream(字符串);
    std::wstring token;
    while (stream >> token) {
        UCHAR byte = static_cast<UCHAR>(_tcstoul(token.c_str(), NULL, 16));
        数组.push_back(byte);
    }

    // 计算解析后的字节序列的大小
    SIZE_T 字节序列大小 = 数组.size();

    // 将解析后的字节序列复制到需要充填的字节集中
    memcpy(需要充填的字节集, 数组.data(), 字节序列大小);

    // 更新实际充填大小
    *实际充填大小 = 字节序列大小;
    return TRUE;
}

CString 取编辑框文本(CEdit* 编辑框) {
    CString 文本;
    编辑框->GetWindowTextW(文本);
    return 文本;
}

double 取编辑框数据到浮点(CEdit* 编辑框) {
    CString 文本 = 取编辑框文本(编辑框);
    return _tstof(文本);
}

ULONG 取下拉框类型(CComboBox* 下拉框) {
    CString 类型文本;
   下拉框->GetWindowTextW(类型文本);
   if (类型文本 == _T("二字节")) {
       return 二字节类型;
   }
   else if (类型文本 == _T("四字节")) {
       return  四字节类型;
   }
   else if (类型文本 == _T("八字节")) {
       return  八字节类型;
   }
   else if (类型文本 == _T("单浮点")) {
       return  小数类型;
   }
   else if (类型文本 == _T("双浮点")) {
       return  双浮点小数类型;
   }
   else if (类型文本 == _T("字节数组")) {
       return  字节数组类型;
   }

   return 0;
}

ULONG 取类型(CString 类型文本) {


    if (类型文本 == _T("二字节")) {
        return 二字节类型;
    }
    else if (类型文本 == _T("四字节")) {
        return  四字节类型;
    }
    else if (类型文本 == _T("八字节")) {
        return  八字节类型;
    }
    else if (类型文本 == _T("单浮点")) {
        return  小数类型;
    }
    else if (类型文本 == _T("双浮点")) {
        return  双浮点小数类型;
    }
    else if (类型文本 == _T("字节数组")) {
        return  字节数组类型;
    }

    return 0;
}

ULONG64 文本转整数(CString 文本) {
    // 去除字符串中的前缀"0x"（如果存在）
    if (文本.Left(2) == _T("0x") || 文本.Left(2) == _T("0X")) {
        文本 = 文本.Mid(2);
    }

    // 使用 CString 的字符指针进行转换
    LPCTSTR 文本内容 = 文本.GetString();
    ULONG64 数值 = _tcstoull(文本内容, nullptr, 16);

    return 数值;
}

CString 整数转十进制文本(ULONG 数值) {

    CString 字符串1;
    字符串1.Format(_T("%lu"), 数值);
    return  字符串1;

}