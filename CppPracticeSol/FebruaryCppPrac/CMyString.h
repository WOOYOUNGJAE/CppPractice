#pragma once
class CMyString
{
public:
	CMyString();
	CMyString(const char* _szText, int _iMax, int _iResizingSize);
	~CMyString();
	
	
	// strcpy
	CMyString& operator = (const char* _szInput); // ���� �������� ������
	CMyString& operator = (CMyString& rhs); // ���� �������� ������

private:
	char* m_pText;
	int m_iCurrentCount;
	int m_iCurrentMaxLength;
	int m_iResizingSize; // max �ʰ� �� char �߰� �޸� �Ҵ� ����

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

	// �迭 ����
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