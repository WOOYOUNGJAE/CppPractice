#pragma once

template <typename T>
struct tNode
{
	tNode* pNextNode;
	tNode* pPrevNode;
	T		data;

	tNode() : pNextNode(nullptr), pPrevNode(nullptr), data(0) {}
};

template <typename T>
class CMyList
{
public:
	CMyList(); // 기본 생성자
	//CMyList(int _iCount); // count개 0으로 채워진 원소
	//CMyList(T _default, int _iCount); // count개 default로 채워진 원소
	//CMyList(CMyList& rhs); // 깊은 복사 생성자
	//CMyList(CMyList&& rhs); // 깊은 복사 이동 생성자

	//~CMyList();
public:
	class iterator;
	void assign(T _default, int _iCount);
	T front();
	T back();
	tNode<T>* begin();
	tNode<T>* end();

	void SetFirstElem(T _data);

	void push_back(T _data);
	void push_front(T _data);
	void insert(iterator _iter, T _data);
	void erase(iterator _iter);

	void Initailize();

private:
	bool bHasElement;
	tNode<T>* pList;
	tNode<T>* pBegin; // 첫 원소의 첫 주소
	tNode<T>* pEnd; // 마지막 원소의 마지막 주소

};


template<typename T>
inline CMyList<T>::CMyList():
	bHasElement(false), pBegin(nullptr), pEnd(nullptr)
{
}

template<typename T>
inline T CMyList<T>::front()
{
	return pBegin->data;
}

template<typename T>
inline T CMyList<T>::back()
{
	return (pEnd - 1)->data;
}

template<typename T>
inline tNode<T>* CMyList<T>::begin()
{
	return pBegin;
}

template<typename T>
inline tNode<T>* CMyList<T>::end()
{
	return pEnd;
}

template<typename T>
inline void CMyList<T>::SetFirstElem(T _data)
{
	tNode<T>* pNode = new tNode<T>;
	pNode->data = _data;

	bHasElement = true;
	pBegin = pNode;
	pEnd = pBegin + 1;
}

template<typename T>
inline void CMyList<T>::push_back(T _data)
{
	if (bHasElement == false)
	{
		SetFirstElem(_data);
	}
	else
	{
		tNode<T>* pAnotherNode = new tNode<T>;
		tNode<T>* pPointer = pBegin; // 위치 지정 용.
		while (pPointer->pNextNode != nullptr)
		{
			pAnotherNode->pPrevNode = pPointer;
			pPointer->pNextNode = pAnotherNode;
			pPointer = pPointer->pNextNode;
		}
		pPointer->data = _data;
		pPointer->pNextNode = nullptr;
	}
}

template<typename T>
inline void CMyList<T>::push_front(T _data)
{
	if (bHasElement == false)
	{
		SetFirstElem(_data);
	}
	else
	{
		tNode<T>* pAnotherBegin = new tNode<T>;
		pBegin->pPrevNode = pAnotherBegin;
		
		pAnotherBegin->data = _data;
		pAnotherBegin->pPrevNode = nullptr;
		pAnotherBegin->pNextNode = pBegin;
	}
}

template<typename T>
inline void CMyList<T>::Initailize()
{

}

#pragma region Iterator

template <typename T>
class CMyList<T>::iterator
{
public:
	// 연산자 오버로딩: ++, ++, +, =
	tNode<T>& operator* ()
	{
		return *pCurrentNode;
	}

	iterator& operator+ (int _indx)
	{
		for (int i = 0; i < _indx; ++i)
		{
			if (pCurrentNode->pNextNode)
				pCurrentNode = pCurrentNode->pNextNode;
			else
			{
				cout << "잘못된 접근" << endl;
			}
		}
		return *this;
	}

	iterator& operator++ ()
	{
		if (pCurrentNode->pNextNode)
			pCurrentNode = pCurrentNode->pNextNode;
		return *this;
	}
	void operator++ (int)
	{
		iterator tmpIter = *this; // 깊은 복사 해야, 힙 공간 이용 안해서 필요 없을 듯?
		if (pCurrentNode->pNextNode)
			pCurrentNode = pCurrentNode->pNextNode;
		return tmpIter;
	}
	//iterator& operator= (iterator& rhs);
private:
	tNode<T>* pCurrentNode;
};
//
//template<typename T>
//inline tNode<T>& CMyList<T>::iterator::operator*()
//{
//	return *pCurrentNode;
//}
//template<typename T>
//inline iterator& CMyList<T>::iterator::operator+(int _indx)
//{
//	for (int i = 0; i < _indx; ++i)
//	{
//		if (pCurrentNode->pNextNode)
//			pCurrentNode = pCurrentNode->pNextNode;
//		else
//		{
//			cout << "잘못된 접근" << endl;
//		}
//	}
//	return *this;
//}
//
//template<typename T>
//inline iterator<T>& iterator<T>::operator++() //전위
//{
//	if (pCurrentNode->pNextNode)
//		pCurrentNode = pCurrentNode->pNextNode;
//	return *this;
//}
//
//template<typename T>
//inline void iterator<T>::operator++(int)
//{
//	iterator<T> tmpIter = *this; // 깊은 복사 해야, 힙 공간 이용 안해서 필요 없을 듯?
//	if (pCurrentNode->pNextNode)
//		pCurrentNode = pCurrentNode->pNextNode;
//	return tmpIter;
//}
#pragma endregion