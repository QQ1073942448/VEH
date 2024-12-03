#include"窗口2.h"


extern 窗口2_下拉框指针 下拉框信息;
BOOLEAN 插入数据(CListCtrl* 列表框,CString 地址,CString 数值)
{
      ULONG 行号 = 列表框->GetItemCount();
      列表框->InsertItem(行号, L"否"); // 第一列是锁定
      列表框->SetItemText(行号, 1, L"无描述"); // 第二列是备注
      列表框->SetItemText(行号, 2, 地址); // 第三列是地址
      CString 类型文本;
      下拉框信息.窗口2_下拉框1->GetWindowTextW(类型文本);
      列表框->SetItemText(行号, 3, 类型文本); // 第四列是类型
      列表框->SetItemText(行号, 4, 数值);//第五列是类型数值
      return TRUE;

}

BOOLEAN 修改数据(CListCtrl* 列表框, CString 地址, ULONG 类型, ULONG 行)
{
    ULONG64 转换的地址 = 文本转整数(地址);
    CString 格式化字符串;
    BOOLEAN 是否成功 = FALSE;
    if (类型 == 二字节类型) {
        USHORT 短整数 = 读短整数(转换的地址, &是否成功);
        格式化字符串.Format(_T("%hu"), 短整数);
    }
    else if (类型 == 四字节类型) {
        ULONG 整数 = 读整数(转换的地址, &是否成功);
        格式化字符串.Format(_T("%lu"), 整数);
    }
    else if (类型 == 八字节类型) {
        ULONG64 长整数 = 读长整数(转换的地址, &是否成功);
        格式化字符串.Format(_T("%llu"), 长整数);
    }
    else if (类型 == 小数类型) {
        float 小数型 = 读浮点数(转换的地址, &是否成功);
        格式化字符串.Format(_T("%f"), 小数型);
    }
    else if (类型 == 双浮点小数类型) {
        double 双精度小数型 = 读双浮点(转换的地址, &是否成功);
        格式化字符串.Format(_T("%lf"), 双精度小数型);
    }
    else if (类型 == 字节数组类型) {
        UCHAR 缓冲区[10] = { 0 };
        读字节集(缓冲区, 转换的地址, 10, &是否成功);

        // 将字节数组转换为字符串表示
        for (int i = 0; i < 10; ++i) {
            CString 字节字符串;
            字节字符串.Format(_T("%02X "), 缓冲区[i]);
            格式化字符串 += 字节字符串;
        }
        格式化字符串.TrimRight(); // 去除最后一个多余的空格
    }
    else {
        return FALSE; // 未知类型，返回FALSE
    }

    列表框->SetItemText(行, 4, 格式化字符串);
    return TRUE;
}
