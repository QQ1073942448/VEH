#include"������.h"

BOOLEAN ����Ӳ���ϵ�(HANDLE hThread, ULONG64 �ϵ��ַ, DWORD �߳�TID, ULONG ���ԼĴ�����Ϣ) {
    CONTEXT �߳������� = { 0 };
    �߳�������.ContextFlags = CONTEXT_DEBUG_REGISTERS; // ��ȡ���ԼĴ�����Ϣ

  //  SuspendThread(hThread);//�����߳�

    // ��ȡ�̵߳���������Ϣ
    if (!GetThreadContext(hThread, &�߳�������)) {
        std::stringstream ss;
        ss << "��ȡ�߳�TID " << �߳�TID << " ��������Ϣʧ��";
        MessageBoxA(nullptr, ss.str().c_str(), "����", MB_OK);
        ResumeThread(hThread);
        return FALSE;
    }

    �߳�������.Dr7 |= 0x1;//����Ϊ���öϵ�
    if (���ԼĴ�����Ϣ == 0) {
        �߳�������.Dr0 = �ϵ��ַ;
    }
    else if (���ԼĴ�����Ϣ == 1) {
        �߳�������.Dr1 = �ϵ��ַ;
    }
    else if (���ԼĴ�����Ϣ == 2) {
        �߳�������.Dr2 = �ϵ��ַ;
    }
    else if (���ԼĴ�����Ϣ == 3) {
        �߳�������.Dr3 = �ϵ��ַ;
    }
 

    // �����̵߳���������Ϣ
    if (!SetThreadContext(hThread, &�߳�������)) {
        std::stringstream ss;
        ss << "�����߳�TID " << �߳�TID << " �ϵ�ʧ��";
        MessageBoxA(nullptr, ss.str().c_str(), "����", MB_OK);
        ResumeThread(hThread);
        return FALSE;
    }

   // ResumeThread(hThread);    // �ָ��߳�
    return TRUE;
}


BOOLEAN ���öϵ�(CEdit* �༭�� , ULONG ���ԼĴ�����Ϣ,ULONG64 �¸��ϵ��ַ) {

    DWORD ����ID = GetCurrentProcessId(); // ��ȡ��ǰ����ID
    HANDLE �߳̿��� = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
   
    THREADENTRY32 �߳���Ŀ;
    �߳���Ŀ.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(�߳̿���, &�߳���Ŀ)) {
        do {
            if (�߳���Ŀ.th32OwnerProcessID == ����ID) {
                HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, �߳���Ŀ.th32ThreadID);
                if (hThread) {
                    ULONG64 �ϵ��ַ;
                    if (�༭��==NULL) {
                        �ϵ��ַ = �¸��ϵ��ַ;
                    }
                    �ϵ��ַ = ȡ�༭�����ݵ�����(�༭��);
                    ����Ӳ���ϵ�(hThread, �ϵ��ַ, �߳���Ŀ.th32ThreadID, ���ԼĴ�����Ϣ);
                    CloseHandle(hThread);
                }
            }
        } while (Thread32Next(�߳̿���, &�߳���Ŀ));
    }
    else {
        //MessageBoxA(nullptr, "ö���߳�ʧ��", "����", MB_OK);
    }

    CloseHandle(�߳̿���);
    return TRUE;
}





BOOLEAN ��նϵ�(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ) 
{
       �쳣�̵߳���Ϣ->ContextRecord->Dr0 = 0;
       �쳣�̵߳���Ϣ->ContextRecord->Dr1 = 0;
       �쳣�̵߳���Ϣ->ContextRecord->Dr2 = 0;
       �쳣�̵߳���Ϣ->ContextRecord->Dr3 = 0;
        return TRUE;
}






