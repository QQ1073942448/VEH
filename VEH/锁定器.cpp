#include"窗口2.h"

extern 窗口2_列表框指针 列表框信息 ;

UINT 开启锁定器(LPVOID 参数) {
    while (TRUE) {
        ULONG 最大行 = 列表框信息.窗口2_列表框2->GetItemCount();
        for (ULONG i = 0; i < 最大行; i++) {
            CString 文本真假;
            文本真假 = 列表框信息.窗口2_列表框2->GetItemText(i, 0);
            if (文本真假 == _T("是")) {
                CString 文本地址;
                CString 文本数值;
                CString 文本类型;
                文本地址 = 列表框信息.窗口2_列表框2->GetItemText(i, 2);
                文本类型 = 列表框信息.窗口2_列表框2->GetItemText(i, 3);
                文本数值 = 列表框信息.窗口2_列表框2->GetItemText(i, 4);
                ULONG 类型 = 取类型(文本类型);
                写入数据(文本地址, 文本数值, 类型);
            }
           
        }
    }
    return 0;
}


void 锁定器() {


	AfxBeginThread(开启锁定器, nullptr);

}



BOOLEAN 内部_修改数据(CListCtrl* 列表框, CString 地址, ULONG 类型, ULONG 行)
{
    ULONG64 转换的地址 = 文本转整数(地址);
    CString 格式化字符串;
    BOOLEAN 是否成功 = FALSE;
    if (类型 == 二字节类型) {
        USHORT 短整数 = 读短整数(转换的地址, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            格式化字符串.Format(_T("%hu"), 短整数);
        }
    }
    else if (类型 == 四字节类型) {
        ULONG 整数 = 读整数(转换的地址, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            格式化字符串.Format(_T("%lu"), 整数);
        }
    }
    else if (类型 == 八字节类型) {
        ULONG64 长整数 = 读长整数(转换的地址, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            格式化字符串.Format(_T("%llu"), 长整数);
        }

    }
    else if (类型 == 小数类型) {
        float 小数型 = 读浮点数(转换的地址, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            格式化字符串.Format(_T("%f"), 小数型);
        }

    }
    else if (类型 == 双浮点小数类型) {
        double 双精度小数型 = 读双浮点(转换的地址, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            格式化字符串.Format(_T("%lf"), 双精度小数型);
        }
    }
    else if (类型 == 字节数组类型) {
        UCHAR 缓冲区[10] = { 0 };
        读字节集(缓冲区, 转换的地址, 10, &是否成功);
        if (!是否成功) {
            格式化字符串 = _T("????");
        }
        else {
            // 将字节数组转换为字符串表示
            for (int i = 0; i < 10; ++i) {
                CString 字节字符串;
                字节字符串.Format(_T("%02X "), 缓冲区[i]);
                格式化字符串 += 字节字符串;
            }
            格式化字符串.TrimRight(); // 去除最后一个多余的空格
        }
    }
    else {
        return FALSE; // 未知类型，返回FALSE
    }

    // 获取当前列表框项的文本
    CString 当前文本 = 列表框->GetItemText(行, 4);

    // 检查新生成的文本是否与当前文本相同，如果相同则不更新
    if (当前文本 != 格式化字符串) {
        列表框->SetItemText(行, 4, 格式化字符串);
    }

    return TRUE;
}



UINT 开启监控器(LPVOID 参数) {
    CString 格式化字符串;
    while (TRUE) {
        ULONG 最大行 = 列表框信息.窗口2_列表框2->GetItemCount();
        for (ULONG i = 0; i < 最大行; i++) {
            CString 文本地址;
            CString 文本类型;
            文本地址 = 列表框信息.窗口2_列表框2->GetItemText(i, 2);
            文本类型 = 列表框信息.窗口2_列表框2->GetItemText(i, 3);
            ULONG 类型=取类型(文本类型);
            内部_修改数据(列表框信息.窗口2_列表框2, 文本地址, 类型, i);
             
        }
        Sleep(1);
    }
    return 0;
}


void 监控器() {

    AfxBeginThread(开启监控器, nullptr);


}


