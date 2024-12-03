#include"主窗口.h"


ULONG64 获取上级调用函数(P寄存器结构体 寄存器信息) {

    ULONG64 栈帧地址 = 寄存器信息->RSP;   // 获取当前栈帧地址
    ULONG64 返回地址 = *((ULONG64*)栈帧地址);   // 获取当前函数执行完的返回地址
    return 返回地址;
}

BOOLEAN 函_返回上级调用(P寄存器结构体 寄存器信息, _EXCEPTION_POINTERS* 异常线程的信息) {
   
    ULONG64 返回地址 = 获取上级调用函数(寄存器信息);
    if (返回地址==0) {
        return FALSE; // 无效返回地址，表示已经到达最顶层   

    }
    异常线程的信息->ContextRecord->Dr0 = 返回地址;
    异常线程的信息->ContextRecord->Dr7 = 0b01010101;
    return TRUE;
}


