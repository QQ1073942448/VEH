#include"������.h"


ULONG64 ȡ�༭�����ݵ�����(CEdit* �༭��)
{  // ��ȡ�༭���е��ı�
    CString �ı�;
    �༭��->GetWindowText(�ı�);

    // �� CString ת��Ϊ��׼�ַ���
    CT2CA ת��(�ı�);
    std::string ��׼�ַ���(ת��);

   
      ULONG64 ��ַ = std::stoull(��׼�ַ���, nullptr, 16);
      return ��ַ;
 
}

CString ȡ�������ı�(CComboBox* ������) {

    CString �ı�;
    ������->GetWindowText(�ı�);
    return �ı�;
}


CString ����תʮ�������ı�(ULONG64 ��ֵ)
{
    // ����ֵת��Ϊ���ַ��ı�
    CString �ı�;
    �ı�.Format(L"%016llX", ��ֵ);

    // ���ؿ��ַ��ı�
    return �ı�;
}


BOOLEAN  ȡ�ı��ֽڼ�����(UCHAR* ��Ҫ������ֽڼ�, CString �ַ��� ,SIZE_T *ʵ�ʳ����С) {
    std::vector<UCHAR> ����;
    std::wstring �ַ��� = static_cast<LPCTSTR>(�ַ���);
    std::wistringstream stream(�ַ���);
    std::wstring token;
    while (stream >> token) {
        UCHAR byte = static_cast<UCHAR>(_tcstoul(token.c_str(), NULL, 16));
        ����.push_back(byte);
    }

    // �����������ֽ����еĴ�С
    SIZE_T �ֽ����д�С = ����.size();

    // ����������ֽ����и��Ƶ���Ҫ������ֽڼ���
    memcpy(��Ҫ������ֽڼ�, ����.data(), �ֽ����д�С);

    // ����ʵ�ʳ����С
    *ʵ�ʳ����С = �ֽ����д�С;
    return TRUE;
}

CString ȡ�༭���ı�(CEdit* �༭��) {
    CString �ı�;
    �༭��->GetWindowTextW(�ı�);
    return �ı�;
}

double ȡ�༭�����ݵ�����(CEdit* �༭��) {
    CString �ı� = ȡ�༭���ı�(�༭��);
    return _tstof(�ı�);
}

ULONG ȡ����������(CComboBox* ������) {
    CString �����ı�;
   ������->GetWindowTextW(�����ı�);
   if (�����ı� == _T("���ֽ�")) {
       return ���ֽ�����;
   }
   else if (�����ı� == _T("���ֽ�")) {
       return  ���ֽ�����;
   }
   else if (�����ı� == _T("���ֽ�")) {
       return  ���ֽ�����;
   }
   else if (�����ı� == _T("������")) {
       return  С������;
   }
   else if (�����ı� == _T("˫����")) {
       return  ˫����С������;
   }
   else if (�����ı� == _T("�ֽ�����")) {
       return  �ֽ���������;
   }

   return 0;
}

ULONG ȡ����(CString �����ı�) {


    if (�����ı� == _T("���ֽ�")) {
        return ���ֽ�����;
    }
    else if (�����ı� == _T("���ֽ�")) {
        return  ���ֽ�����;
    }
    else if (�����ı� == _T("���ֽ�")) {
        return  ���ֽ�����;
    }
    else if (�����ı� == _T("������")) {
        return  С������;
    }
    else if (�����ı� == _T("˫����")) {
        return  ˫����С������;
    }
    else if (�����ı� == _T("�ֽ�����")) {
        return  �ֽ���������;
    }

    return 0;
}

ULONG64 �ı�ת����(CString �ı�) {
    // ȥ���ַ����е�ǰ׺"0x"��������ڣ�
    if (�ı�.Left(2) == _T("0x") || �ı�.Left(2) == _T("0X")) {
        �ı� = �ı�.Mid(2);
    }

    // ʹ�� CString ���ַ�ָ�����ת��
    LPCTSTR �ı����� = �ı�.GetString();
    ULONG64 ��ֵ = _tcstoull(�ı�����, nullptr, 16);

    return ��ֵ;
}

CString ����תʮ�����ı�(ULONG ��ֵ) {

    CString �ַ���1;
    �ַ���1.Format(_T("%lu"), ��ֵ);
    return  �ַ���1;

}