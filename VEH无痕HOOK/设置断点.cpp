#include"���öϵ�.h"
#include <Zydis/Zydis.h>

extern ULONG64 ��һ��ָ���ַ;

#ifdef __cplusplus
extern "C" {
#endif

    ZyanStatus ZydisDecoderInit(ZydisDecoder* decoder, ZydisMachineMode machine_mode,
        ZydisStackWidth stack_width);

    ZyanStatus ZydisDecoderDecodeFull(const ZydisDecoder* decoder,
        const void* buffer, ZyanUSize length, ZydisDecodedInstruction* instruction,
        ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT]);

    ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style);

    ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count, char* buffer, ZyanUSize length, ZyanU64 runtime_address,
        void* user_data);

    ZyanStatus ZydisEncoderDecodedInstructionToEncoderRequest(
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count_visible, ZydisEncoderRequest* request);
    ZyanStatus ZydisEncoderEncodeInstruction(const ZydisEncoderRequest* request,
        void* buffer, ZyanUSize* length);

#ifdef __cplusplus
}
#endif

BOOLEAN �ڴ��ַ�Ƿ�ɶ�(ULONG64 �ڴ��ַ, SIZE_T ̽�ⳤ��) {
    MEMORY_BASIC_INFORMATION mbi;
    ULONG64 ������ַ = �ڴ��ַ + ̽�ⳤ��;

    while (�ڴ��ַ < ������ַ) {
        if (VirtualQuery((LPCVOID)�ڴ��ַ, &mbi, sizeof(mbi)) == 0) {
            return FALSE; // ��� VirtualQuery ʧ�ܣ����� FALSE
        }

        // ����ڴ�ҳ��ı��������Ƿ����������
        if (!((mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_READONLY) || (mbi.Protect & PAGE_EXECUTE_READ) || (mbi.Protect & PAGE_EXECUTE_READWRITE))) {
            return FALSE; // ����ڴ治�ɶ������� FALSE
        }

        // ǰ������һҳ
        �ڴ��ַ = (ULONG64)mbi.BaseAddress + mbi.RegionSize;
    }

    return TRUE; // ������������ڴ�ɶ������� TRUE
}

USHORT ��������(ULONG64 �ڴ��ַ, BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, sizeof(USHORT))) {
        *�Ƿ�ɹ� = TRUE;
        return *(USHORT*)�ڴ��ַ;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return 0;
    }
    return 0;
}

ULONG ������(ULONG64 �ڴ��ַ, BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, sizeof(ULONG))) {
        *�Ƿ�ɹ� = TRUE;
        return *(ULONG*)�ڴ��ַ;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return 0;
    }
    return 0;
}

ULONG64 ��������(ULONG64 �ڴ��ַ, BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, sizeof(ULONG64))) {
        *�Ƿ�ɹ� = TRUE;
        return *(ULONG64*)�ڴ��ַ;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return 0;
    }
    return 0;
}








BOOLEAN ����Ӳ���ϵ�(HANDLE �߳̾��, ULONG64 HOOK������ַ, DWORD �߳�TID, ULONG ���ԼĴ�����Ϣ) {
    CONTEXT �߳������� = { 0 };
    �߳�������.ContextFlags = CONTEXT_DEBUG_REGISTERS; // ��ȡ���ԼĴ�����Ϣ
    GetThreadContext(�߳̾��, &�߳�������);  // ��ȡ�̵߳���������Ϣ
    �߳�������.Dr7 |= 0x1;//����Ϊ���öϵ�
    if (���ԼĴ�����Ϣ == 1) {
        �߳�������.Dr0 = HOOK������ַ;
    }
    else if (���ԼĴ�����Ϣ == 2) {
        �߳�������.Dr1 = HOOK������ַ;
    }
    else if (���ԼĴ�����Ϣ == 3) {
        �߳�������.Dr2 = HOOK������ַ;
    }
    else if (���ԼĴ�����Ϣ == 4) {
        �߳�������.Dr3 = HOOK������ַ;
    }
    SetThreadContext(�߳̾��, &�߳�������);

    return TRUE;
}

BOOLEAN ��ȡ�쳣�߳�������(_EXCEPTION_POINTERS* �쳣�̵߳���Ϣ, P�Ĵ����ṹ�� �Ĵ�����Ϣ) {

    �Ĵ�����Ϣ->RAX = �쳣�̵߳���Ϣ->ContextRecord->Rax;
    �Ĵ�����Ϣ->RBX = �쳣�̵߳���Ϣ->ContextRecord->Rbx;
    �Ĵ�����Ϣ->RCX = �쳣�̵߳���Ϣ->ContextRecord->Rcx;
    �Ĵ�����Ϣ->RDX = �쳣�̵߳���Ϣ->ContextRecord->Rdx;
    �Ĵ�����Ϣ->RSI = �쳣�̵߳���Ϣ->ContextRecord->Rsi;
    �Ĵ�����Ϣ->RDI = �쳣�̵߳���Ϣ->ContextRecord->Rdi;
    �Ĵ�����Ϣ->RBP = �쳣�̵߳���Ϣ->ContextRecord->Rbp;
    �Ĵ�����Ϣ->RSP = �쳣�̵߳���Ϣ->ContextRecord->Rsp;
    �Ĵ�����Ϣ->R8 = �쳣�̵߳���Ϣ->ContextRecord->R8;
    �Ĵ�����Ϣ->R9 = �쳣�̵߳���Ϣ->ContextRecord->R9;
    �Ĵ�����Ϣ->R10 = �쳣�̵߳���Ϣ->ContextRecord->R10;
    �Ĵ�����Ϣ->R11 = �쳣�̵߳���Ϣ->ContextRecord->R11;
    �Ĵ�����Ϣ->R12 = �쳣�̵߳���Ϣ->ContextRecord->R12;
    �Ĵ�����Ϣ->R13 = �쳣�̵߳���Ϣ->ContextRecord->R13;
    �Ĵ�����Ϣ->R14 = �쳣�̵߳���Ϣ->ContextRecord->R14;
    �Ĵ�����Ϣ->RIP = �쳣�̵߳���Ϣ->ContextRecord->Rip;
    �Ĵ�����Ϣ->XMM0 = �쳣�̵߳���Ϣ->ContextRecord->Xmm0;
    �Ĵ�����Ϣ->XMM1 = �쳣�̵߳���Ϣ->ContextRecord->Xmm1;
    �Ĵ�����Ϣ->XMM2 = �쳣�̵߳���Ϣ->ContextRecord->Xmm2;
    �Ĵ�����Ϣ->XMM3 = �쳣�̵߳���Ϣ->ContextRecord->Xmm3;
    �Ĵ�����Ϣ->XMM4 = �쳣�̵߳���Ϣ->ContextRecord->Xmm4;
    �Ĵ�����Ϣ->XMM5 = �쳣�̵߳���Ϣ->ContextRecord->Xmm5;
    �Ĵ�����Ϣ->XMM6 = �쳣�̵߳���Ϣ->ContextRecord->Xmm6;
    �Ĵ�����Ϣ->XMM7 = �쳣�̵߳���Ϣ->ContextRecord->Xmm7;
    �Ĵ�����Ϣ->XMM8 = �쳣�̵߳���Ϣ->ContextRecord->Xmm8;
    �Ĵ�����Ϣ->XMM9 = �쳣�̵߳���Ϣ->ContextRecord->Xmm9;
    �Ĵ�����Ϣ->XMM10 = �쳣�̵߳���Ϣ->ContextRecord->Xmm10;
    �Ĵ�����Ϣ->XMM11 = �쳣�̵߳���Ϣ->ContextRecord->Xmm11;
    �Ĵ�����Ϣ->XMM12 = �쳣�̵߳���Ϣ->ContextRecord->Xmm12;
    �Ĵ�����Ϣ->XMM13 = �쳣�̵߳���Ϣ->ContextRecord->Xmm13;
    �Ĵ�����Ϣ->XMM14 = �쳣�̵߳���Ϣ->ContextRecord->Xmm14;
    �Ĵ�����Ϣ->XMM15 = �쳣�̵߳���Ϣ->ContextRecord->Xmm15;
    �Ĵ�����Ϣ->DR0 = �쳣�̵߳���Ϣ->ContextRecord->Dr0;
    �Ĵ�����Ϣ->DR1 = �쳣�̵߳���Ϣ->ContextRecord->Dr1;
    �Ĵ�����Ϣ->DR2 = �쳣�̵߳���Ϣ->ContextRecord->Dr2;
    �Ĵ�����Ϣ->DR3 = �쳣�̵߳���Ϣ->ContextRecord->Dr3;
    �Ĵ�����Ϣ->DR6 = �쳣�̵߳���Ϣ->ContextRecord->Dr6;
    �Ĵ�����Ϣ->DR7 = �쳣�̵߳���Ϣ->ContextRecord->Dr7;

    return TRUE;
}

BOOLEAN ���öϵ�(ULONG64 HOOK������ַ, ULONG ���ԼĴ�����Ϣ) {

    DWORD ����ID = GetCurrentProcessId();
    HANDLE �߳̿��� = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 �߳���Ŀ;
    �߳���Ŀ.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(�߳̿���, &�߳���Ŀ)) {
        do {
            if (�߳���Ŀ.th32OwnerProcessID == ����ID) {
                HANDLE �߳̾�� = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, �߳���Ŀ.th32ThreadID);
                if (�߳̾��) {
                    ����Ӳ���ϵ�(�߳̾��, HOOK������ַ, �߳���Ŀ.th32ThreadID, ���ԼĴ�����Ϣ);
                    CloseHandle(�߳̾��);
                }
            }
        } while (Thread32Next(�߳̿���, &�߳���Ŀ));
    }
    CloseHandle(�߳̿���);
    return TRUE;
}


BOOLEAN ��_����ִ��(P�Ĵ����ṹ�� �Ĵ�����Ϣ, _EXCEPTION_POINTERS* �쳣�̵߳���Ϣ)
{
    // ��ʼ��Zydis������
    ZydisDecoder ������;
    ZydisDecoderInit(&������, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    // ���뵱ǰָ��
    ZydisDecodedInstruction ������;
    ZydisDecodedOperand ������[ZYDIS_MAX_OPERAND_COUNT];
    ZydisDecoderDecodeFull(&������, (UCHAR*)�Ĵ�����Ϣ->RIP, ZYDIS_MAX_INSTRUCTION_LENGTH, &������, ������);

    // ��ȡ��ǰָ���
    SIZE_T ָ��� = ������.length;

    // ������һ��ָ���ַ
    UINT64 ��һ��ָ���ַ = �Ĵ�����Ϣ->RIP + ָ���;

    // ��ʼ�������ϵ��ַ
    UINT64 �ϵ�1��ַ = ��һ��ָ���ַ;
    UINT64 �ϵ�2��ַ = 0;
    BOOLEAN �Ƿ�ɹ� = FALSE;
    // ����Ƿ�ΪRETָ��
    if (������.mnemonic == ZYDIS_MNEMONIC_RET)
    {
        // ��ȡջ�ϵķ��ص�ַ
        // �������ջ��64λ��
        ULONG64 ���ص�ַ = ��������(�Ĵ�����Ϣ->RSP, &�Ƿ�ɹ�);

        // ���÷��ص�ַΪ�ϵ�
        �ϵ�1��ַ = ���ص�ַ;
        �ϵ�2��ַ = 0; // RETָ��ͨ������Ҫ�ڶ����ϵ�

        // ����ջָ��
        �Ĵ�����Ϣ->RSP += sizeof(UINT64);
    }
    else
    {
        // ������������������������Ĵ���
        for (ULONG i = 0; i < ������.operand_count_visible; i++)
        {
            if (������[i].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
            {
                �ϵ�2��ַ = �Ĵ�����Ϣ->RIP + ָ��� + ������[i].imm.value.s;
                break;
            }
            else if (������[i].type == ZYDIS_OPERAND_TYPE_REGISTER)
            {
                // ����Ĵ�����ת
                switch (������[i].reg.value)
                {
                case ZYDIS_REGISTER_RAX: �ϵ�2��ַ = �Ĵ�����Ϣ->RAX; break;
                case ZYDIS_REGISTER_RBX: �ϵ�2��ַ = �Ĵ�����Ϣ->RBX; break;
                case ZYDIS_REGISTER_RCX: �ϵ�2��ַ = �Ĵ�����Ϣ->RCX; break;
                case ZYDIS_REGISTER_RDX: �ϵ�2��ַ = �Ĵ�����Ϣ->RDX; break;
                case ZYDIS_REGISTER_RBP: �ϵ�2��ַ = �Ĵ�����Ϣ->RBP; break;
                case ZYDIS_REGISTER_RSP: �ϵ�2��ַ = �Ĵ�����Ϣ->RSP; break;
                case ZYDIS_REGISTER_R8: �ϵ�2��ַ = �Ĵ�����Ϣ->R8; break;
                case ZYDIS_REGISTER_R9: �ϵ�2��ַ = �Ĵ�����Ϣ->R9; break;
                case ZYDIS_REGISTER_R10: �ϵ�2��ַ = �Ĵ�����Ϣ->R10; break;
                case ZYDIS_REGISTER_R11: �ϵ�2��ַ = �Ĵ�����Ϣ->R11; break;
                case ZYDIS_REGISTER_R12: �ϵ�2��ַ = �Ĵ�����Ϣ->R12; break;
                case ZYDIS_REGISTER_R13: �ϵ�2��ַ = �Ĵ�����Ϣ->R13; break;
                case ZYDIS_REGISTER_R14: �ϵ�2��ַ = �Ĵ�����Ϣ->R14; break;
                case ZYDIS_REGISTER_R15: �ϵ�2��ַ = �Ĵ�����Ϣ->R15; break;
                }
                break; // ����ҵ�һ���Ĵ�����ת���˳�ѭ��
            }
        }
    }

    // ���õ��ԼĴ���
    �쳣�̵߳���Ϣ->ContextRecord->Dr0 = �ϵ�1��ַ; // ��һ���ϵ��ַ
    ��һ��ָ���ַ = �ϵ�1��ַ;
    if (�ϵ�2��ַ != 0)
    {
        �쳣�̵߳���Ϣ->ContextRecord->Dr1 = �ϵ�2��ַ; // �ڶ����ϵ��ַ
    }

    // ���õ��ԼĴ����ı�־λ
    �쳣�̵߳���Ϣ->ContextRecord->Dr7 = 0b01010101;

    // ����TRUE����ʾ�ɹ����öϵ�
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