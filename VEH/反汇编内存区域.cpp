#include"主窗口.h"
#include"Zyidi.h"

#define 缓存数 0x500


BOOLEAN 反汇编内存区域(CListCtrl* 列表框, UCHAR* 指令开始地址, SIZE_T 大小) {
  
  

    // 初始化 Zydis 引擎
    ZydisDecoder 编码器;
    ZydisDecoderInit(&编码器, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // 初始化 Zydis 格式器
    ZydisFormatter 格式器;
    ZydisFormatterInit(&格式器, ZYDIS_FORMATTER_STYLE_INTEL); // 使用 Intel 格式

    // 准备存储解码结果的结构体和数组
    ZydisDecodedInstruction 解码结果;
    ZydisDecodedOperand 操作数[ZYDIS_MAX_OPERAND_COUNT];

    // 初始化偏移量
    UCHAR* 当前地址 = 指令开始地址;
    UCHAR* 结束地址 = 指令开始地址 +大小;
    char buffer[256];

    // 清空列表框
    列表框->DeleteAllItems();

    while (当前地址 < 结束地址) {
        // 解码当前地址处的指令
        if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&编码器, 当前地址, ZYDIS_MAX_INSTRUCTION_LENGTH, &解码结果, 操作数))) {
            // 格式化解码结果为人类可读格式
            ZydisFormatterFormatInstruction(&格式器, &解码结果, 操作数, 解码结果.operand_count_visible,
                buffer, sizeof(buffer), reinterpret_cast<ZyanU64>(当前地址), nullptr);

            // 将当前地址转换为宽字符字符串
            CStringW 地址字符串;
            地址字符串.Format(L"%p", 当前地址);
            int 行号 = 列表框->GetItemCount();
            列表框->InsertItem(行号, 地址字符串); // 第一列是地址

            // 将当前指令的字节转换为十六进制字符串并添加到第二列
            CString 字节字符串;
            for (SIZE_T i = 0; i < 解码结果.length; ++i) {
                CString 单字节;
                单字节.Format(L"%02X ", 当前地址[i]);
                字节字符串 += 单字节;
            }
            列表框->SetItemText(行号, 1, 字节字符串); // 第二列是字节

            // 将 ANSI 格式的 buffer 转换为宽字符并添加到第三列
            CStringA 缓冲区ANSI(buffer);
            CStringW 宽字符缓冲区(缓冲区ANSI); // 使用构造函数将 ANSI 转换为 Unicode
            列表框->SetItemText(行号, 2, 宽字符缓冲区); // 第三列是汇编码

            // 更新当前地址
            当前地址 += 解码结果.length;
        }
        else {
            // 如果解码失败，退出循环
            break;
        }
    }

    return TRUE;
}

