#include"����2.h"
#include"resource.h"
#include <vector>
#include <sstream>
#include <unordered_set>

extern ����2_�ı�ָ�� �ı���Ϣ;


ɨ����ڴ� ɨ��Ľṹ��[2] = { 0 };

void ����UI() {
    MSG msg; // ��Ϣ�ṹ��
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { // ������Ϣ�����е���Ϣ
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


BOOLEAN ��2_ɨ���ڴ�(CEdit* ɨ��༭��, CEdit* ��ʼ��ַ�༭��, CEdit* ������ַ�༭��, CListCtrl* ��ʾ�б��, CComboBox* ����������, CButton* ʮ�����ư�ť, CProgressCtrl* ������) {
    �ı���Ϣ.����2_�ı�1->SetWindowText(L"����ɨ��");
    
    memset(ɨ��Ľṹ��[1].��ַ����, 0, sizeof(ɨ��Ľṹ��[1]));

    ɨ��Ľṹ��[1].��ַ���� = 0;
    ��ʾ�б��->DeleteAllItems();
    ������->SetPos(0);



    CString ���� = ȡ�������ı�(����������);
    BOOL ��ʮ������ = ʮ�����ư�ť->GetCheck();
    CString ɨ������;
    ɨ��༭��->GetWindowText(ɨ������);

    ULONG64 ��ʼ��ַ = ȡ�༭�����ݵ�����(��ʼ��ַ�༭��);
    ULONG64 ������ַ = ȡ�༭�����ݵ�����(������ַ�༭��);

    auto ��ȡ�༭������ = [&](CEdit* �༭��) -> ULONG64 {
        CString �ı�;
        �༭��->GetWindowText(�ı�);
        return ��ʮ������ ? _tcstoull(�ı�, nullptr, 16) : _tcstoull(�ı�, nullptr, 10);
    };

    auto ��ȡ���������� = [&](CEdit* �༭��) -> float {
        CString �ı�;
        �༭��->GetWindowText(�ı�);
        return _tstof(�ı�);
    };

  

    HANDLE ���̾�� = GetCurrentProcess();
    MEMORY_BASIC_INFORMATION �ڴ���Ϣ1;
    MEMORY_BASIC_INFORMATION �ڴ���Ϣ2;
    ULONG ɨ����� = 0; // ɨ���������
    ULONG �ڴ������ = 0;
    ULONG �ڴ����� = 0;

    // Ԥ�ȼ����ڴ������
    ULONG64 ��ʱ��ַ = ��ʼ��ַ;
    while (��ʱ��ַ < ������ַ) {
        if (VirtualQuery((LPCVOID)��ʱ��ַ, &�ڴ���Ϣ1, sizeof(�ڴ���Ϣ1)) == sizeof(�ڴ���Ϣ1)) {
            if (�ڴ���Ϣ1.State == MEM_COMMIT && (�ڴ���Ϣ1.Protect & PAGE_READONLY ||
                �ڴ���Ϣ1.Protect & PAGE_READWRITE ||
                �ڴ���Ϣ1.Protect & PAGE_WRITECOPY ||
                �ڴ���Ϣ1.Protect & PAGE_EXECUTE_READ ||
                �ڴ���Ϣ1.Protect & PAGE_EXECUTE_READWRITE ||
                �ڴ���Ϣ1.Protect & PAGE_EXECUTE_WRITECOPY)) {
                ++�ڴ������;
            }
           
        }
        ��ʱ��ַ += �ڴ���Ϣ1.RegionSize;
    }
    // ʵ��ɨ���ڴ�
    while (��ʼ��ַ < ������ַ) {
        if (VirtualQuery((LPCVOID)��ʼ��ַ, &�ڴ���Ϣ2, sizeof(�ڴ���Ϣ2)) == sizeof(�ڴ���Ϣ2)) {
            if (�ڴ���Ϣ2.State == MEM_COMMIT && (�ڴ���Ϣ2.Protect & PAGE_READONLY ||
                �ڴ���Ϣ2.Protect & PAGE_READWRITE ||
                �ڴ���Ϣ2.Protect & PAGE_WRITECOPY ||
                �ڴ���Ϣ2.Protect & PAGE_EXECUTE_READ ||
                �ڴ���Ϣ2.Protect & PAGE_EXECUTE_READWRITE ||
                �ڴ���Ϣ2.Protect & PAGE_EXECUTE_WRITECOPY)) {
                ++�ڴ�����;
                BYTE* ������ = new BYTE[�ڴ���Ϣ2.RegionSize];
                SIZE_T ��ȡ�ֽ���;
                if (ReadProcessMemory(���̾��, �ڴ���Ϣ2.BaseAddress, ������, �ڴ���Ϣ2.RegionSize, &��ȡ�ֽ���)) {
                    auto ɨ���ڴ� = [&](auto ɨ������, auto �ȽϺ���, SIZE_T ��λ��С) {
                        for (SIZE_T ƫ�� = 0; ƫ�� < ��ȡ�ֽ���; ƫ�� += ��λ��С) {
                            decltype(ɨ������) �ڴ�����;
                            �ڴ����� = *reinterpret_cast<decltype(ɨ������)*>(������ + ƫ��);
                            if (�ȽϺ���(�ڴ�����, ɨ������)) {
                                CString �����ַ���;
                                �����ַ���.Format(_T("%s"), std::to_wstring(�ڴ�����).c_str());
                                CString ��ַ�ַ���;
                                ��ַ�ַ���.Format(_T("%llX"), (ULONG64)(�ڴ���Ϣ2.BaseAddress) + ƫ��);
                                int �к� = ��ʾ�б��->GetItemCount(); // ��ȡ��ǰ�����������һ�е�����
                                ��ʾ�б��->InsertItem(�к�, ��ַ�ַ���); // ����ײ�������
                                ��ʾ�б��->SetItemText(�к�, 1, �����ַ���); // ���õڶ�������
                                ɨ��Ľṹ��[1].��ַ����[ɨ�����] = (ULONG64)(�ڴ���Ϣ2.BaseAddress) + ƫ��;
                                ɨ�����++;
                            }
                        }
                    };

                    // �������ͽ�������ɨ��
                    if (���� == _T("���ֽ�")) {
                        USHORT ɨ������ = static_cast<USHORT>(��ȡ�༭������(ɨ��༭��));
                        ɨ���ڴ�(ɨ������, [](USHORT a, USHORT b) { return a == b; }, sizeof(USHORT));
                    }
                    else if (���� == _T("���ֽ�")) {
                        ULONG ɨ������ = static_cast<ULONG>(��ȡ�༭������(ɨ��༭��));
                        ɨ���ڴ�(ɨ������, [](ULONG a, ULONG b) { return a == b; }, sizeof(ULONG));
                    }
                    else if (���� == _T("���ֽ�")) {
                        ULONG64 ɨ������ = ��ȡ�༭������(ɨ��༭��);
                        ɨ���ڴ�(ɨ������, [](ULONG64 a, ULONG64 b) { return a == b; }, sizeof(ULONG64));
                    }
                    else if (���� == _T("������")) {
                        float ɨ������ = ��ȡ����������(ɨ��༭��);
                        ɨ���ڴ�(ɨ������, [](float a, float b) { return fabs(a - b) < 0.00001; }, sizeof(float));
                    }
                    else if (���� == _T("˫����")) {
                        double ɨ������ = ��ȡ����������(ɨ��༭��);
                        ɨ���ڴ�(ɨ������, [](double a, double b) { return fabs(a - b) < 0.00001; }, sizeof(double));
                    }
                    else if (���� == _T("�ֽ�����")) {
                        UCHAR �ַ���[256] = { 0 };
                        CString �ı� = ɨ������;
                        SIZE_T ��С = 0;
                        ȡ�ı��ֽڼ�����(�ַ���, �ı�, &��С);
                        for (SIZE_T ƫ�� = 0; ƫ�� <= ��ȡ�ֽ��� - ��С; ƫ��++) {
                            bool ƥ�� = true;
                            for (SIZE_T i = 0; i < ��С; i++) {
                                if (������[ƫ�� + i] != �ַ���[i]) {
                                    ƥ�� = false;
                                    break;
                                }
                            }
                            if (ƥ��) {
                                CString �����ַ���;
                                �����ַ���.Format(_T("%s"), �ı�);
                                CString ��ַ�ַ���;
                                ��ַ�ַ���.Format(_T("%llx"), (ULONG64)(�ڴ���Ϣ2.BaseAddress) + ƫ��);
                                int �к� = ��ʾ�б��->InsertItem(0, ��ַ�ַ���);
                                ��ʾ�б��->SetItemText(�к�, 1, �����ַ���);
                            }
                        }
                    }
                }

                delete[] ������;
              
            }
        }

      
        int ��ǰ���� = static_cast<int>((�ڴ����� * 100) / �ڴ������);
        ������->SetPos(��ǰ����);
        ��ʼ��ַ += �ڴ���Ϣ2.RegionSize;
        ����UI();
    }
    ɨ��Ľṹ��[1].��ַ���� = ɨ�����;
    CString �����ı�;
    �����ı�.Format(_T("��ǰ�����%d"), ɨ�����);
    �ı���Ϣ.����2_�ı�1->SetWindowText(�����ı�);
    return TRUE;
}


BOOLEAN �ٴ�ɨ��(CEdit* ɨ��༭��, CComboBox* ����������, CListCtrl* ��ʾ�б��, CButton* ʮ�����ư�ť, CProgressCtrl* ������) {
    �ı���Ϣ.����2_�ı�1->SetWindowText(L"����ɨ��");
    ��ʾ�б��->DeleteAllItems();
    ������->SetPos(0);
    std::unordered_set<ULONG64> �Ѳ���ĵ�ַ����;
    �Ѳ���ĵ�ַ����.clear(); // ����Ѳ���ĵ�ַ����

    CString ɨ������;
    ɨ��༭��->GetWindowText(ɨ������);
    BOOL ��ʮ������ = ʮ�����ư�ť->GetCheck();
    ULONG ʣ���ַ���� = ɨ��Ľṹ��[1].��ַ����;
    ULONG ��ʼ��ַ���� = ʣ���ַ����;
    ULONG ɨ����� = 0; // ɨ���������

    CString ����;
    ����������->GetWindowText(����);

    auto ��ȡ�༭������ = [&](CEdit* �༭��) -> ULONG64 {
        CString �ı�;
        �༭��->GetWindowText(�ı�);
        return ��ʮ������ ? _tcstoull(�ı�, nullptr, 16) : _tcstoull(�ı�, nullptr, 10);
    };

    auto ��ȡ���������� = [&](CEdit* �༭��) -> float {
        CString �ı�;
        �༭��->GetWindowText(�ı�);
        return static_cast<float>(_tstof(�ı�));
    };

    auto ɨ���ڴ� = [&](auto ɨ������, auto �ȽϺ���, SIZE_T ��λ��С, BYTE* ������, SIZE_T ��ȡ�ֽ���, ULONG64 ��ַ) {
        if (�Ѳ���ĵ�ַ����.find(��ַ) != �Ѳ���ĵ�ַ����.end()) {
            ɨ��Ľṹ��[1].��ַ����[ɨ�����] = ��ַ;         
            return; // �����ַ�Ѵ��ڣ�����������
        }

        decltype(ɨ������) �ڴ����� = *reinterpret_cast<decltype(ɨ������)*>(������);
        if (�ȽϺ���(�ڴ�����, ɨ������)) {;
            �Ѳ���ĵ�ַ����.insert(��ַ); // ��¼����ĵ�ַ
            ɨ��Ľṹ��[1].��ַ����[ɨ�����] = ��ַ;
            CString �����ַ���;
            �����ַ���.Format(_T("%s"), std::to_wstring(�ڴ�����).c_str());
            CString ��ַ�ַ���;
            ��ַ�ַ���.Format(_T("%llx"), ��ַ);
            int �к� = ��ʾ�б��->GetItemCount();
            ��ʾ�б��->InsertItem(�к�, ��ַ�ַ���);
            ��ʾ�б��->SetItemText(�к�, 1, �����ַ���);
            ɨ�����++;
        }
    };

    ʣ���ַ����++;
    while (ʣ���ַ���� > 0) {
        ULONG64 ��ַ = ɨ��Ľṹ��[1].��ַ����[ʣ���ַ���� - 1];
        ɨ��Ľṹ��[1].��ַ����[ʣ���ַ���� - 1] = 0;
        MEMORY_BASIC_INFORMATION �ڴ���Ϣ;
        if (VirtualQuery(reinterpret_cast<LPCVOID>(��ַ), &�ڴ���Ϣ, sizeof(�ڴ���Ϣ)) == sizeof(�ڴ���Ϣ) &&
            �ڴ���Ϣ.State == MEM_COMMIT &&
            (�ڴ���Ϣ.Protect & PAGE_READONLY || �ڴ���Ϣ.Protect & PAGE_READWRITE ||
                �ڴ���Ϣ.Protect & PAGE_WRITECOPY || �ڴ���Ϣ.Protect & PAGE_EXECUTE_READ ||
                �ڴ���Ϣ.Protect & PAGE_EXECUTE_READWRITE || �ڴ���Ϣ.Protect & PAGE_EXECUTE_WRITECOPY)) {

            BYTE* ������ = reinterpret_cast<BYTE*>(��ַ);
            SIZE_T ��ȡ�ֽ��� = sizeof(ULONG64);  // �������Ǵ������ 8 �ֽ�����

            if (���� == _T("���ֽ�")) {
                USHORT ɨ������ = static_cast<USHORT>(��ȡ�༭������(ɨ��༭��));
                ɨ���ڴ�(ɨ������, [](USHORT a, USHORT b) { return a == b; }, sizeof(USHORT), ������, ��ȡ�ֽ���, ��ַ);
            }
            else if (���� == _T("���ֽ�")) {
                ULONG ɨ������ = static_cast<ULONG>(��ȡ�༭������(ɨ��༭��));
                ɨ���ڴ�(ɨ������, [](ULONG a, ULONG b) { return a == b; }, sizeof(ULONG), ������, ��ȡ�ֽ���, ��ַ);
            }
            else if (���� == _T("���ֽ�")) {
                ULONG64 ɨ������ = ��ȡ�༭������(ɨ��༭��);
                ɨ���ڴ�(ɨ������, [](ULONG64 a, ULONG64 b) { return a == b; }, sizeof(ULONG64), ������, ��ȡ�ֽ���, ��ַ);
            }
            else if (���� == _T("������")) {
                float ɨ������ = ��ȡ����������(ɨ��༭��);
                ɨ���ڴ�(ɨ������, [](float a, float b) { return fabs(a - b) < 0.00001; }, sizeof(float), ������, ��ȡ�ֽ���, ��ַ);
            }
            else if (���� == _T("˫����")) {
                double ɨ������ = static_cast<double>(��ȡ����������(ɨ��༭��));
                ɨ���ڴ�(ɨ������, [](double a, double b) { return fabs(a - b) < 0.00001; }, sizeof(double), ������, ��ȡ�ֽ���, ��ַ);
            }
            else if (���� == _T("�ֽ�����")) {
                UCHAR �ַ���[256] = { 0 };
                CString �ı� = ɨ������;
                SIZE_T ��С = 0;
                ȡ�ı��ֽڼ�����(�ַ���, �ı�, &��С);
                bool ƥ�� = true;
                for (SIZE_T i = 0; i < ��С; i++) {
                    if (������[i] != �ַ���[i]) {
                        ƥ�� = false;
                        break;
                    }
                }
                if (ƥ��) {
                    CString �����ַ���;
                    �����ַ���.Format(_T("%s"), �ı�);
                    CString ��ַ�ַ���;
                    ��ַ�ַ���.Format(_T("%llX"), ��ַ);
                    int �к� = ��ʾ�б��->InsertItem(0, ��ַ�ַ���);
                    ��ʾ�б��->SetItemText(�к�, 1, �����ַ���);
                    �Ѳ���ĵ�ַ����.insert(��ַ); // ��¼����ĵ�ַ
                }
            }
        }

        ʣ���ַ����--;
        int ��ǰ���� = static_cast<int>(((��ʼ��ַ���� - ʣ���ַ����) * 100) / ��ʼ��ַ����);
        ������->SetPos(��ǰ����);
        ����UI();
    }
    ������->SetPos(100);
    ɨ��Ľṹ��[1].��ַ���� = ɨ�����;
    CString �����ı�;
    �����ı�.Format(_T("��ǰ�����%d"), ɨ�����);
    �ı���Ϣ.����2_�ı�1->SetWindowText(�����ı�);
    return TRUE;
}