#include "stdafx.h"
#include "CMyString.h"

CMyString::CMyString()
	: m_pText(nullptr), m_iCurrentCount(0), m_iCurrentMaxLength(10), m_iResizingSize(10)
{
	cout << "������: String ����" << endl;
	Initialize("");

}

CMyString::CMyString(const char* _szText, int _iMax, int _iResizingSize)
	: m_pText(nullptr), m_iCurrentCount(0), m_iCurrentMaxLength(_iMax), m_iResizingSize(_iResizingSize)
{
	cout << "������: String ����" << endl;
	Initialize(_szText);
}

CMyString::~CMyString()
{
	DELETE_MAC(m_pText);
}

CMyString& CMyString::operator=(CMyString& rhs) // ���� ����
{
	// check size
	int iNewLength = strlen(rhs.Get_Text()) + 1; // ������ ���� + ��������
	// maxcount ������, ������ ���� �� ���Ҵ�
	while (true)
	{
		if (iNewLength > m_iCurrentMaxLength) // �ʰ��ϸ�
		{
			Resize(*this);
			continue;
		}
		else
			break;
	}
	// max�� Resize()���� ������ ���������� �ٽ� ����
	strcpy_s(m_pText, iNewLength, rhs.Get_Text()); // pText����, strcpy�� �ڵ� ���� ����
	m_iCurrentCount = rhs.Get_CurrentCount();
	m_iCurrentMaxLength = rhs.Get_MaxLength();
	m_iResizingSize = rhs.Get_ResizingSize();

	return *this;
}

char* CMyString::Get_Text()
{
	return m_pText;
}

int CMyString::Get_CurrentCount()
{
	return m_iCurrentCount;
}

int CMyString::Get_MaxLength()
{
	return m_iCurrentMaxLength;
}

int CMyString::Get_ResizingSize()
{
	return m_iResizingSize;
}

void CMyString::Set_TextPointer(char* _szInput)
{
	m_pText = _szInput;
}

void CMyString::Initialize(const char* _szText)
{
	int iFirstLength = strlen(_szText);
	// max ����
	while (iFirstLength > m_iCurrentMaxLength)
	{
		m_iCurrentMaxLength += m_iResizingSize;
	}
	// ���� ����
	m_pText = new char[m_iCurrentMaxLength];
	m_iCurrentCount = iFirstLength;
	strcpy_s(m_pText, sizeof(char) * (iFirstLength + 1), _szText);
	cout << "�̴ϼȶ����� �Ϸ�: " << m_pText << endl;
}

void CMyString::Release()
{
	DELETE_MAC(m_pText);
}

CMyString& CMyString::AddText(const char* _szInput)
{
	// AnotherString�� ���� Ŭ������ ������ ��, ���� ��, ��ȯ
	CMyString* AnotherString = new CMyString;
	*AnotherString = *this; // ���� ���� (�������̵�)
	// check size
	int iNewLength = AnotherString->m_iCurrentCount + strlen(_szInput) + 1;
	while (true)
	{
		if (iNewLength > AnotherString->m_iCurrentMaxLength) // �ʰ��ϸ�
		{
			Resize(*AnotherString); // max�� ���� ����
			continue;
		}
		else
			break;
	}
	strcat_s(AnotherString->m_pText, iNewLength, _szInput);
	AnotherString->m_iCurrentCount = iNewLength - 1;
	cout << "���� �Ϸ�: " << AnotherString->m_pText << endl;

	return *AnotherString; // �� ���� ���� ���� ���� �����ڿ� ����
}

void CMyString::Resize(CMyString& _strOriginal)
{
	char* szAnotherText = nullptr;
	szAnotherText = new char[_strOriginal.m_iCurrentCount + _strOriginal.m_iResizingSize];

	memcpy_s(szAnotherText, _strOriginal.m_iCurrentCount + 1, _strOriginal.m_pText, _strOriginal.m_iCurrentCount + 1);
	_strOriginal.Release();
	_strOriginal.Set_TextPointer(szAnotherText);	
	_strOriginal.m_iCurrentMaxLength += _strOriginal.m_iResizingSize;
}

int CMyString::operator==(const char* _szInput)
{
	int iIndx = 0;
	while (true)
	{
		if (m_pText[iIndx] == _szInput[iIndx])
		{
			if (m_pText[iIndx] == '\0')
			{
				cout << "���ڿ� �� ���� ���: ����" << endl;
				return 0;
			}
			iIndx++;
			continue;
		}
		else // ����Ű�� �ε����� ���ڰ� �ٸ� ���
		{
			cout << "���ڿ� �� ���� ���: �ٸ�" << endl;
			return 1;
		}

	}

	return 0;
}

CMyString& CMyString::operator+(const char* _szInput)
{
	return AddText(_szInput);
}

CMyString& CMyString::operator+(CMyString& _strInput) 
{
	//if (this == &_strInput) // ��ü���� ���ٸ�
	//{
	//	int iOriginalLength = strlen(m_pText);
	//	int iAnotherSize = iOriginalLength * 2 + 1;
	//	// ���ο� �ؽ�Ʈ �����
	//	char* szAnotherText = nullptr;
	//	szAnotherText = new char[iAnotherSize];
	//	strcpy_s(szAnotherText, iOriginalLength + 1, m_pText);
	//	strcat_s(szAnotherText, iAnotherSize, m_pText);
	//	CMyString* AnotherString = new CMyString(szAnotherText, m_iCurrentMaxLength << 1, m_iResizingSize);
	//	return *AnotherString;
	//}
	return AddText(_strInput.Get_Text());
}
