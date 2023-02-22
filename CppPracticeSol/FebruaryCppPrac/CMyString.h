#pragma once
class CMyString
{
public:
	CMyString();
	CMyString(const char* _szText, int _iMax, int _iResizingSize);
	~CMyString();
	
	
	// strcpy
	CMyString& operator = (const char* _szInput); // 대입 깊은복사 연산자
	CMyString& operator = (CMyString& rhs); // 대입 깊은복사 연산자

private:
	char* m_pText;
	int m_iCurrentCount;
	int m_iCurrentMaxLength;
	int m_iResizingSize; // max 초과 시 char 추가 메모리 할당 개수

public:
	// getter
	char* Get_Text();
	int Get_CurrentCount();
	int Get_MaxLength();
	int Get_ResizingSize();

	// setter
	void Set_TextPointer(char* _szInput);

	// 
	void Initialize(const char* _szText);
	void Release();

	// 배열 관리
	CMyString& AddText(const char* _szInput);
	void Resize(CMyString& _strOriginal);

	// strcmp
	int operator == (const char* _szInput);
	// strcat
	//+
	CMyString& operator + (const char* _szInput);
	CMyString& operator + (CMyString& _strInput);
	// +=
	void operator += (const char* _szInput);
	void operator += (CMyString& _strInput);
	// <<
	friend ostream& operator<< (ostream& c, CMyString& _strInput);
};