#include"������.h"
#include <vector>


 SIZE_T ��ȡ���� = 400;
 extern ULONG �б��4_д������;
 extern ULONG ��ǰ��������;

 BOOLEAN ��ʼ���б���ʽ(CListCtrl* �б��, CString ѡ���ı�) {
     // ���������
     while (�б��->DeleteColumn(0));

     if (ѡ���ı� == _T("�ֽ�")) {
         // Ĭ�ϴ�ӡ�ֽڣ�17��
         �б��->InsertColumn(0, L"��ַ", 0, 100);
         for (int i = 1; i <= 16; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             �б��->InsertColumn(i, colName, 0, 40);
         }
     }
     else if (ѡ���ı� == _T("���ֽ�")) {
         // ��������9��
         �б��->InsertColumn(0, L"��ַ", 0, 100);
         for (int i = 1; i <= 8; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             �б��->InsertColumn(i, colName, 0, 80);
         }
     }
     else if (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("������")) {
         // ���ֽڻ򵥸��㣺5��
         �б��->InsertColumn(0, L"��ַ", 0, 100);
         for (int i = 1; i <= 4; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             �б��->InsertColumn(i, colName, 0, 100);
         }
     }
     else if (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("˫����")) {
         // ���ֽڻ�˫���㣺3��
         �б��->InsertColumn(0, L"��ַ", 0, 100);
         for (int i = 1; i <= 2; ++i) {
             CString colName;
             colName.Format(L"%02d", i);
             �б��->InsertColumn(i, colName, 0, 200);
         }
     }
     else {
         return FALSE;
     }

     return TRUE;
 }


 extern ������ָ�� ��������Ϣ;
 BOOLEAN �Ƿ��ӡʮ������ = TRUE;
 BOOLEAN ��ȡ�ڴ�(CListCtrl* �б��, CComboBox* ������, ULONG64 ��ʼ��ַ, SIZE_T ����) {
   
     �б��->DeleteAllItems(); // ����б���е���������
     
     // ��ȡ����������
     CString ѡ���ı�;
     ������->GetWindowText(ѡ���ı�);
     CString �����ı�;
     ��������Ϣ.������3->GetWindowText(�����ı�);
     if (�����ı� == _T("ʮ������")) {


         �Ƿ��ӡʮ������ = TRUE;

     }
     else {
         �Ƿ��ӡʮ������ = FALSE;
     }
     // ��ʼ���б���ʽ
     if (!��ʼ���б���ʽ(�б��, ѡ���ı�)) {
         return FALSE;
     }

     // ����ѡ����������ÿ�е��ֽ���
     SIZE_T bytesPerLine = 16; // Ĭ����16�ֽ�
     if (ѡ���ı� == _T("���ֽ�")) {

         bytesPerLine = 16;
     }
     else if (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("������")) {
         bytesPerLine = 16;
     }
     else if (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("˫����")) {
         bytesPerLine = 16;
     }

     SIZE_T totalLines = (���� + bytesPerLine - 1) / bytesPerLine;

     for (SIZE_T line = 0; line < totalLines; ++line) {
         ULONG64 ��ǰ��ַ = ��ʼ��ַ + line * bytesPerLine;

         // ̽���ڴ��Ƿ�ɶ�
         MEMORY_BASIC_INFORMATION mbi;
         if (VirtualQuery((LPCVOID)��ǰ��ַ, &mbi, sizeof(mbi)) == 0 ||
             !(mbi.Protect & PAGE_READONLY) && !(mbi.Protect & PAGE_READWRITE) && !(mbi.Protect & PAGE_EXECUTE_READ) && !(mbi.Protect & PAGE_EXECUTE_READWRITE)) {

             CString strAddress;
             strAddress.Format(_T("0x%llX"), ��ǰ��ַ);
             int rowIndex = �б��->InsertItem(line, strAddress);
             for (int i = 1; i <= (ѡ���ı� == _T("�ֽ�") ? 16 : (ѡ���ı� == _T("���ֽ�") ? 8 : (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("������") ? 4 : 2))); ++i) {
                 �б��->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // �޸��ڴ汣��Ϊ�ɶ���д��ִ��
         DWORD oldProtect;
         if (!VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
             CString strAddress;
             strAddress.Format(_T("0x%llX"), ��ǰ��ַ);
             int rowIndex = �б��->InsertItem(line, strAddress);
             for (int i = 1; i <= (ѡ���ı� == _T("�ֽ�") ? 16 : (ѡ���ı� == _T("���ֽ�") ? 8 : (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("������") ? 4 : 2))); ++i) {
                 �б��->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // ��ȡ�ڴ�
         std::vector<BYTE> buffer(bytesPerLine, 0);
         SIZE_T bytesRead;
         if (!ReadProcessMemory(GetCurrentProcess(), (LPCVOID)��ǰ��ַ, buffer.data(), bytesPerLine, &bytesRead)) {
             CString strAddress;
             strAddress.Format(_T("0x%llX"), ��ǰ��ַ);
             int rowIndex = �б��->InsertItem(line, strAddress);
             for (int i = 1; i <= (ѡ���ı� == _T("�ֽ�") ? 16 : (ѡ���ı� == _T("���ֽ�") ? 8 : (ѡ���ı� == _T("���ֽ�") || ѡ���ı� == _T("������") ? 4 : 2))); ++i) {
                 �б��->SetItemText(rowIndex, i, _T("??"));
             }
             continue;
         }

         // ��ӡ��Ӧ�ֽں͵�ַ���ؼ���
         CString strAddress;
         strAddress.Format(_T("0x%llX"), ��ǰ��ַ);
         int rowIndex = �б��->InsertItem(line, strAddress);

         if (ѡ���ı� == _T("�ֽ�")) {
             ��ǰ�������� = �ֽ���������;
             if (�Ƿ��ӡʮ������) {
                 for (SIZE_T i = 0; i < bytesRead; ++i) {
                     CString strByte;
                     strByte.Format(_T("%02X"), buffer[i]); // ʮ�����ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strByte);
                 }
                 for (SIZE_T i = bytesRead; i < bytesPerLine; ++i) {
                     �б��->SetItemText(rowIndex, i + 1, _T("??"));
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead; ++i) {
                     CString strByte;
                     strByte.Format(_T("%d"), buffer[i]); // ʮ���ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strByte);
                 }
             }
         }
         else if (ѡ���ı� == _T("���ֽ�")) {
             ��ǰ�������� = ���ֽ�����;
             if (�Ƿ��ӡʮ������) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(USHORT); ++i) {
                     USHORT value = *((USHORT*)(buffer.data() + i * sizeof(USHORT)));
                     CString strValue;
                     strValue.Format(_T("%04X"), value); // ʮ�����ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(USHORT); ++i) {
                     USHORT value = *((USHORT*)(buffer.data() + i * sizeof(USHORT)));
                     CString strValue;
                     strValue.Format(_T("%u"), value); // ʮ���ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (ѡ���ı� == _T("���ֽ�")) {
             ��ǰ�������� = ���ֽ�����;
             if (�Ƿ��ӡʮ������) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG); ++i) {
                     ULONG value = *((ULONG*)(buffer.data() + i * sizeof(ULONG)));
                     CString strValue;
                     strValue.Format(_T("%08X"), value); // ʮ�����ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG); ++i) {
                     ULONG value = *((ULONG*)(buffer.data() + i * sizeof(ULONG)));
                     CString strValue;
                     strValue.Format(_T("%u"), value); // ʮ���ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (ѡ���ı� == _T("���ֽ�")) {
             ��ǰ�������� = ���ֽ�����;
             if (�Ƿ��ӡʮ������) {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG64); ++i) {
                     ULONG64 value = *((ULONG64*)(buffer.data() + i * sizeof(ULONG64)));
                     CString strValue;
                     strValue.Format(_T("%016llX"), value); // ʮ�����ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
             else {
                 for (SIZE_T i = 0; i < bytesRead / sizeof(ULONG64); ++i) {
                     ULONG64 value = *((ULONG64*)(buffer.data() + i * sizeof(ULONG64)));
                     CString strValue;
                     strValue.Format(_T("%llu"), value); // ʮ���ƴ�ӡ
                     �б��->SetItemText(rowIndex, i + 1, strValue);
                 }
             }
         }
         else if (ѡ���ı� == _T("������")) {
             ��ǰ�������� = С������;
             for (SIZE_T i = 0; i < bytesRead / sizeof(float); ++i) {
                 float value = *((float*)(buffer.data() + i * sizeof(float)));
                 CString strValue;
                 if (�Ƿ��ӡʮ������) {
                     strValue.Format(_T("%f"), value);
                 }
                 else {
                     strValue.Format(_T("%f"), value); // ʮ���ƴ�ӡ
                 }
                 �б��->SetItemText(rowIndex, i + 1, strValue);
             }
         }
         else if (ѡ���ı� == _T("˫����")) {
             ��ǰ�������� = ˫����С������;
             for (SIZE_T i = 0; i < bytesRead / sizeof(double); ++i) {
                 double value = *((double*)(buffer.data() + i * sizeof(double)));
                 CString strValue;
                 if (�Ƿ��ӡʮ������) {
                     strValue.Format(_T("%lf"), value);
                 }
                 else {
                     strValue.Format(_T("%lf"), value); // ʮ���ƴ�ӡ
                 }
                 �б��->SetItemText(rowIndex, i + 1, strValue);
             }
         }
     }

     return TRUE;
 }





BOOLEAN ��_���Ͷ�ȡ(CListCtrl* �б��, CComboBox* ������, ULONG64 ��ַ )
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((LPCVOID)��ַ, &mbi, sizeof(mbi)) == 0)
    {
        return FALSE;
    }

    if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD))
    {
        return FALSE;
    }

    if (mbi.RegionSize < ��ȡ����)
    {
        return FALSE;
    }

    CString ѡ���ı�;
    ������->GetWindowText(ѡ���ı�);

    std::vector<CString> ��ַ����;
    std::vector<CString> ����;
    std::vector<CString> ƫ������;
    ��ַ����.reserve(��ȡ���� / sizeof(ULONG64));
    ����.reserve(��ȡ���� / sizeof(ULONG64));
    ƫ������.reserve(��ȡ���� / sizeof(ULONG64));

    SIZE_T ƫ���� = 0;

    if (ѡ���ı� == _T("���ֽ�"))
    {
        for (SIZE_T i = 0; i < ��ȡ���� / sizeof(short); ++i)
        {
            �б��4_д������ = ���ֽ�����;
            short ֵ = *((short*)(��ַ + i * sizeof(short)));
            CString ��ַ��, ������, ƫ����;
            ��ַ��.Format(_T("%016llX"), ��ַ + i * sizeof(short));
            ������.Format(_T("%d"), ֵ);
            ƫ����.Format(_T("+%X"), ƫ����);
            ƫ���� += sizeof(short);
            ��ַ����.push_back(��ַ��);
            ����.push_back(������);
            ƫ������.push_back(ƫ����);
        }
    }
    else if (ѡ���ı� == _T("���ֽ�"))
    {
        for (SIZE_T i = 0; i < ��ȡ���� / sizeof(ULONG); ++i)
        {
            �б��4_д������ = ���ֽ�����;
            ULONG ֵ = *((ULONG*)(��ַ + i * sizeof(ULONG)));
            CString ��ַ��, ������, ƫ����;
            ��ַ��.Format(_T("%016llX"), ��ַ + i * sizeof(ULONG));
            ������.Format(_T("%lu"), ֵ);
            ƫ����.Format(_T("+%X"), ƫ����);
            ƫ���� += sizeof(ULONG);
            ��ַ����.push_back(��ַ��);
            ����.push_back(������);
            ƫ������.push_back(ƫ����);
        }
    }
    else if (ѡ���ı� == _T("���ֽ�"))
    {
        for (SIZE_T i = 0; i < ��ȡ���� / sizeof(ULONG64); ++i)
        {
            �б��4_д������ = ���ֽ�����;
            ULONG64 ֵ = *((ULONG64*)(��ַ + i * sizeof(ULONG64)));
            CString ��ַ��, ������, ƫ����;
            ��ַ��.Format(_T("%016llX"), ��ַ + i * sizeof(ULONG64));
            ������.Format(_T("%llu"), ֵ);
            ƫ����.Format(_T("+%X"), ƫ����);
            ƫ���� += sizeof(ULONG64);
            ��ַ����.push_back(��ַ��);
            ����.push_back(������);
            ƫ������.push_back(ƫ����);
        }
    }
    else if (ѡ���ı� == _T("������"))
    {
        for (SIZE_T i = 0; i < ��ȡ���� / sizeof(float); ++i)
        {
            �б��4_д������ = С������;
            float ֵ = *((float*)(��ַ + i * sizeof(float)));
            CString ��ַ��, ������, ƫ����;
            ��ַ��.Format(_T("%016llX"), ��ַ + i * sizeof(float));
            ������.Format(_T("%f"), ֵ);
            ƫ����.Format(_T("+%X"), ƫ����);
            ƫ���� += sizeof(float);
            ��ַ����.push_back(��ַ��);
            ����.push_back(������);
            ƫ������.push_back(ƫ����);
        }
    }
    else if (ѡ���ı� == _T("˫����"))
    {
        for (SIZE_T i = 0; i < ��ȡ���� / sizeof(double); ++i)
        {
            �б��4_д������ = ˫����С������;
            double ֵ = *((double*)(��ַ + i * sizeof(double)));
            CString ��ַ��, ������, ƫ����;
            ��ַ��.Format(_T("%016llX"), ��ַ + i * sizeof(double));
            ������.Format(_T("%lf"), ֵ);
            ƫ����.Format(_T("+%X"), ƫ����);
            ƫ���� += sizeof(double);
            ��ַ����.push_back(��ַ��);
            ����.push_back(������);
            ƫ������.push_back(ƫ����);
        }
    }
    else
    {
       
        return FALSE;
    }

    // ����б���������
    �б��->DeleteAllItems();
    for (size_t i = 0; i < ��ַ����.size(); ++i)
    {
        int nItem = �б��->InsertItem(i, ƫ������[i]); 
        �б��->SetItemText(nItem, 1, ��ַ����[i]); 
        �б��->SetItemText(nItem, 2, ����[i]);
    }

    return TRUE;
}



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

ULONG ������(ULONG64 �ڴ��ַ, BOOLEAN *�Ƿ�ɹ�) {
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

float ��������(ULONG64 �ڴ��ַ,BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, sizeof(float))) {
        *�Ƿ�ɹ� = TRUE;
        return *(float*)�ڴ��ַ;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return 0;
    }
    return 0;
}

double ��˫����(ULONG64 �ڴ��ַ, BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, sizeof(double))) {
        *�Ƿ�ɹ� = TRUE;
        return *(double*)�ڴ��ַ;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return 0;
    }
    return 0;
}

BOOLEAN ���ֽڼ�(UCHAR* ������, ULONG64 �ڴ��ַ, SIZE_T ��ȡ���� , BOOLEAN* �Ƿ�ɹ�) {
    if (�ڴ��ַ�Ƿ�ɶ�(�ڴ��ַ, ��ȡ����)) {
        memcpy(������, (void*)�ڴ��ַ, ��ȡ����);////ʹ��memcpy��Դ��ַ�¸������ݵ�����һ�Ļ�������
        *�Ƿ�ɹ� = TRUE;
        return TRUE;
    }
    else {
        *�Ƿ�ɹ� = FALSE;
        return FALSE;
    }
    return FALSE;
}


//����Ϊд�뺯��
BOOLEAN �޸�Ŀ���ڴ�Ȩ��(ULONG64 �ڴ��ַ, SIZE_T �޸ĳ���, ULONG* ԭ��Ȩ��) {//�޸�Ŀ���ڴ�����ҳ����
    if (!VirtualProtect((LPVOID)�ڴ��ַ, �޸ĳ���, PAGE_EXECUTE_READWRITE, ԭ��Ȩ��)) {
        return FALSE;  ////���ִ�е���˵�����ڴ�ο�������������
    }
    return TRUE;
}

BOOLEAN �ָ�Ŀ���ڴ�Ȩ��(ULONG64 �ڴ��ַ, SIZE_T �޸ĳ���, ULONG ԭ��Ȩ��) {//�ָ�ԭ������ҳ������ֹ����Ϸ���
    ULONG Ȩ�޻�����;
    if (!VirtualProtect((LPVOID)�ڴ��ַ, �޸ĳ���, ԭ��Ȩ��, &Ȩ�޻�����)) {
        return FALSE;
    }
    return TRUE;
}

BOOLEAN д������(ULONG64 �ڴ��ַ, USHORT д����ֵ) {
    ULONG  ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(USHORT), &ԭ��Ȩ��)) {//�����ڴ�ҳ���Ƿ��д�����޸�Ŀ���ڴ�Ȩ��Ϊ�ɶ�д��ִ��,�ڰ�ȫ����д�룬������ڴ���������д��ᴥ��ҳ���쳣
        return FALSE;
    }
    *(USHORT*)�ڴ��ַ = д����ֵ;
    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(USHORT), ԭ��Ȩ��)) {//�����һ�γɹ��޸���Ŀ���ڴ�ҳ��Ȩ�ޣ��ڶ���һ��Ҳ������ʲô����
        return FALSE;
    }
    return TRUE;
}

BOOLEAN д����(ULONG64 �ڴ��ַ, ULONG д����ֵ) {
    ULONG ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(ULONG), &ԭ��Ȩ��)) {
        return FALSE;
    }

    *(ULONG*)�ڴ��ַ = д����ֵ;

    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(ULONG), ԭ��Ȩ��)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN д������(ULONG64 �ڴ��ַ, ULONG64 д����ֵ) {
    ULONG ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(ULONG64), &ԭ��Ȩ��)) {
        return FALSE;
    }

    *(ULONG64*)�ڴ��ַ = д����ֵ;

    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(ULONG64), ԭ��Ȩ��)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN дС����(ULONG64 �ڴ��ַ, float д����ֵ) {
    ULONG ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(float), &ԭ��Ȩ��)) {
        return FALSE;
    }

    *(float*)�ڴ��ַ = д����ֵ;

    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(float), ԭ��Ȩ��)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN д˫����С����(ULONG64 �ڴ��ַ, double д����ֵ) {
    ULONG ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(double), &ԭ��Ȩ��)) {
        return FALSE;
    }

    *(double*)�ڴ��ַ = д����ֵ;

    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, sizeof(double), ԭ��Ȩ��)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN д�ֽڼ�(ULONG64 �ڴ��ַ, UCHAR* ������, SIZE_T ����) {
    ULONG ԭ��Ȩ��;
    if (!�޸�Ŀ���ڴ�Ȩ��(�ڴ��ַ, ����, &ԭ��Ȩ��)) {
        return FALSE;
    }
    memcpy((LPVOID)�ڴ��ַ, ������, ����);//����һ��������UCHAR*�ֽڼ��Ļ�����ʹ��memcpy�������ƽ�ȥ

    if (!�ָ�Ŀ���ڴ�Ȩ��(�ڴ��ַ, ����, ԭ��Ȩ��)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN ��ȡ�ı�ת���ַ���(const char* �ı���ַ, WCHAR* ���ַ���) {//���ÿ��ַ�������ΪWINDOWS�Լ���Ϸ������ANSI�ַ����������ǿ��ַ�������
    SIZE_T ���ַ������ȼ��� = MultiByteToWideChar(CP_UTF8, 0, �ı���ַ, -1, NULL, 0);//����ʹ��MultiByteToWideChar�����Զ�������ڴ��ַ�µ����ݳ��ȵõ��ı�����
    if (MultiByteToWideChar(CP_UTF8, 0, �ı���ַ, -1, ���ַ���, ���ַ������ȼ���) == 0) {//�����ڴ��ַ�µ��ı����ݸ��Ƶ��������Ŀ��ַ����������У�ע�⻺������С�Լ�����ͺ�
        return FALSE;
    }

    return TRUE;
}




BOOLEAN д������(CString �ı���ַ, CString �༭���ȡ����ֵ, ULONG �б��4_д������) {
    // ���ı���ַת��Ϊ��ֵ��ַ
    ULONG64 ��ַ = _tcstoull(�ı���ַ, NULL, 16);

    // ���༭���ȡ����ֵת��Ϊ���ʵ���������
    if (�б��4_д������ == ���ֽ�����) {
        USHORT ��ֵ = static_cast<USHORT>(_tstoi(�༭���ȡ����ֵ));
        if (д������(��ַ, ��ֵ)) {
            return TRUE;
        }
    }
    else if (�б��4_д������ == ���ֽ�����) {
        ULONG ��ֵ = static_cast<ULONG>(_tstoi(�༭���ȡ����ֵ));
        if (д����(��ַ, ��ֵ)) {
            return TRUE;
        }
    }
    else if (�б��4_д������ == ���ֽ�����) {
        ULONG64 ��ֵ = _tcstoull(�༭���ȡ����ֵ, NULL, 10);
        if (д������(��ַ, ��ֵ)) {
            return TRUE;
        }
    }
    else if (�б��4_д������ == С������) {
        float ��ֵ = static_cast<float>(_tstof(�༭���ȡ����ֵ));
        if (дС����(��ַ, ��ֵ)) {
            return TRUE;
        }
    }
    else if (�б��4_д������ == ˫����С������) {
        double ��ֵ = static_cast<double>(_tstof(�༭���ȡ����ֵ));
        if (д˫����С����(��ַ, ��ֵ)) {
            return TRUE;
        }
    }
    else if (�б��4_д������ == �ֽ���������) {
        std::vector<UCHAR> ����;
        std::wistringstream stream(�༭���ȡ����ֵ.GetString());
        std::wstring token;
        while (stream >> token) {
            UCHAR byte = static_cast<UCHAR>(_tcstoul(token.c_str(), NULL, 16));
            ����.push_back(byte);
        }
        if (д�ֽڼ�(��ַ, ����.data(), ����.size())) {
            return TRUE;
        }
    }

    return FALSE;
}




