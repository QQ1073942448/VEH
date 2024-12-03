#include"主窗口.h"

BOOLEAN 设置硬件断点(HANDLE hThread, ULONG64 断点地址, DWORD 线程TID, ULONG 调试寄存器信息) {
    CONTEXT 线程上下文 = { 0 };
    线程上下文.ContextFlags = CONTEXT_DEBUG_REGISTERS; // 获取调试寄存器信息

  //  SuspendThread(hThread);//挂起线程

    // 获取线程的上下文信息
    if (!GetThreadContext(hThread, &线程上下文)) {
        std::stringstream ss;
        ss << "获取线程TID " << 线程TID << " 上下文信息失败";
        MessageBoxA(nullptr, ss.str().c_str(), "错误", MB_OK);
        ResumeThread(hThread);
        return FALSE;
    }

    线程上下文.Dr7 |= 0x1;//这里为启用断点
    if (调试寄存器信息 == 0) {
        线程上下文.Dr0 = 断点地址;
    }
    else if (调试寄存器信息 == 1) {
        线程上下文.Dr1 = 断点地址;
    }
    else if (调试寄存器信息 == 2) {
        线程上下文.Dr2 = 断点地址;
    }
    else if (调试寄存器信息 == 3) {
        线程上下文.Dr3 = 断点地址;
    }
 

    // 设置线程的上下文信息
    if (!SetThreadContext(hThread, &线程上下文)) {
        std::stringstream ss;
        ss << "设置线程TID " << 线程TID << " 断点失败";
        MessageBoxA(nullptr, ss.str().c_str(), "错误", MB_OK);
        ResumeThread(hThread);
        return FALSE;
    }

   // ResumeThread(hThread);    // 恢复线程
    return TRUE;
}


BOOLEAN 设置断点(CEdit* 编辑框 , ULONG 调试寄存器信息,ULONG64 下个断点地址) {

    DWORD 进程ID = GetCurrentProcessId(); // 获取当前进程ID
    HANDLE 线程快照 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
   
    THREADENTRY32 线程条目;
    线程条目.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(线程快照, &线程条目)) {
        do {
            if (线程条目.th32OwnerProcessID == 进程ID) {
                HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, 线程条目.th32ThreadID);
                if (hThread) {
                    ULONG64 断点地址;
                    if (编辑框==NULL) {
                        断点地址 = 下个断点地址;
                    }
                    断点地址 = 取编辑框数据到整数(编辑框);
                    设置硬件断点(hThread, 断点地址, 线程条目.th32ThreadID, 调试寄存器信息);
                    CloseHandle(hThread);
                }
            }
        } while (Thread32Next(线程快照, &线程条目));
    }
    else {
        //MessageBoxA(nullptr, "枚举线程失败", "错误", MB_OK);
    }

    CloseHandle(线程快照);
    return TRUE;
}





BOOLEAN 清空断点(_EXCEPTION_POINTERS* 异常线程的信息) 
{
       异常线程的信息->ContextRecord->Dr0 = 0;
       异常线程的信息->ContextRecord->Dr1 = 0;
       异常线程的信息->ContextRecord->Dr2 = 0;
       异常线程的信息->ContextRecord->Dr3 = 0;
        return TRUE;
}






