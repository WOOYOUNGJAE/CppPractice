#include "stdafx.h"
#include "CMyString.h"

CMyString::CMyString()
	: m_pText(nullptr), m_iCurrentCount(0), m_iCurrentMaxLength(10), m_iResizingSize(10)
{
	cout << "생성자: String 생성" << endl;
	Initialize("");

}

CMyString::CMyString(const char* _szText, int _iMax, int _iResizingSize)
	: m_pText(nullptr), m_iCurrentCount(0), m_iCurrentMaxLength(_iMax), m_iResizingSize(_iResizingSize)
{
	cout << "생성자: String 생성" << endl;
	Initialize(_szText);
}

CMyString::~CMyString()
{
	DELETE_MAC(m_pText);
}

CMyString& CMyString::operator=(CMyString& rhs) // 깊은 복사
{
	// check size
	int iNewLength = strlen(rhs.Get_Text()) + 1; // 들어오는 글자 + 널포인터
	// maxcount 재조정, 포인터 해제 후 재할당
	while (true)
	{
		if (iNewLength > m_iCurrentMaxLength) // 초과하면
		{
			Resize(*this);
			continue;
		}
		else
			break;
	}
	// max는 Resize()에서 조정된 상태이지만 다시 조정
	strcpy_s(m_pText, iNewLength, rhs.Get_Text()); // pText조정, strcpy는 자동 깊은 복사
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
	// max 조정
	while (iFirstLength > m_iCurrentMaxLength)
	{
		m_iCurrentMaxLength += m_iResizingSize;
	}
	// 글자 복사
	m_pText = new char[m_iCurrentMaxLength];
	m_iCurrentCount = iFirstLength;
	strcpy_s(m_pText, sizeof(char) * (iFirstLength + 1), _szText);
	cout << "이니셜라이즈 완료: " << m_pText << endl;
}

void CMyString::Release()
{
	DELETE_MAC(m_pText);
}

CMyString& CMyString::AddText(const char* _szInput)
{
	// AnotherString에 현재 클래스를 복사한 후, 조정 후, 반환
	CMyString* AnotherString = new CMyString;
	*AnotherString = *this; // 깊은 복사 (오버라이딩)
	// check size
	int iNewLength = AnotherString->m_iCurrentCount + strlen(_szInput) + 1;
	while (true)
	{
		if (iNewLength > AnotherString->m_iCurrentMaxLength) // 초과하면
		{
			Resize(*AnotherString); // max랑 글자 변경
			continue;
		}
		else
			break;
	}
	strcat_s(AnotherString->m_pText, iNewLength, _szInput);
	AnotherString->m_iCurrentCount = iNewLength - 1;
	cout << "결합 완료: " << AnotherString->m_pText << endl;

	return *AnotherString; // 이 리턴 값을 복사 대입 연산자에 연결
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
				cout << "문자열 비교 연산 결과: 같음" << endl;
				return 0;
			}
			iIndx++;
			continue;
		}
		else // 가리키는 인덱스의 문자가 다를 경우
		{
			cout << "문자열 비교 연산 결과: 다름" << endl;
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
	//if (this == &_strInput) // 정체성이 같다면
	//{
	//	int iOriginalLength = strlen(m_pText);
	//	int iAnotherSize = iOriginalLength * 2 + 1;
	//	// 새로운 텍스트 만들기
	//	char* szAnotherText = nullptr;
	//	szAnotherText = new char[iAnotherSize];
	//	strcpy_s(szAnotherText, iOriginalLength + 1, m_pText);
	//	strcat_s(szAnotherText, iAnotherSize, m_pText);
	//	CMyString* AnotherString = new CMyString(szAnotherText, m_iCurrentMaxLength << 1, m_iResizingSize);
	//	return *AnotherString;
	//}
	return AddText(_strInput.Get_Text());
}
