#pragma once
#include"������.h"




typedef struct �Ĵ����ṹ�� {
    ULONG64 RAX;
    ULONG64 RBX;
    ULONG64 RCX;
    ULONG64 RDX;
    ULONG64 RSI;
    ULONG64 RDI;
    ULONG64 RBP;
    ULONG64 RSP;
    ULONG64 R8;
    ULONG64 R9;
    ULONG64 R10;
    ULONG64 R11;
    ULONG64 R12;
    ULONG64 R13;
    ULONG64 R14;
    ULONG64 R15;
    ULONG64 RIP;
    M128A XMM0;
    M128A XMM1;
    M128A XMM2;
    M128A XMM3;
    M128A XMM4;
    M128A XMM5;
    M128A XMM6;
    M128A XMM7;
    M128A XMM8;
    M128A XMM9;
    M128A XMM10;
    M128A XMM11;
    M128A XMM12;
    M128A XMM13;
    M128A XMM14;
    M128A XMM15;
    ULONG64 DR0;
    ULONG64 DR1;
    ULONG64 DR2;
    ULONG64 DR3;
    ULONG64 DR6;
    ULONG64 DR7;

} �Ĵ����ṹ��, * P�Ĵ����ṹ��;


BOOLEAN ���öϵ�(ULONG64 HOOK������ַ, ULONG ���ԼĴ�����Ϣ);
BOOLEAN ��ȡ�쳣�߳�������(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ, P�Ĵ����ṹ�� �Ĵ�����Ϣ);
BOOLEAN ��_����ִ��(P�Ĵ����ṹ�� �Ĵ�����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ);
BOOLEAN ��նϵ�(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ);