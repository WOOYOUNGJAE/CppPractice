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
	CMyList(); // �⺻ ������
	CMyList(int _iCount); // count�� 0���� ä���� ����
	CMyList(T _default, int _iCount); // count�� default�� ä���� ����
	CMyList(CMyList& rhs); // ���� ���� ������ �Ϸ�
	//CMyList(CMyList&& rhs); // ���� ���� �̵� ������

	~CMyList();
public:
	class iterator;
	void assign(T _default, int _iCount);
	T front();
	T back();
	tNode<T>* begin();
	tNode<T>* end();

	void SetFirstElem(T _data);
	void AddNode(tNode<T>* _pAnotherNode ,T _data);

	void push_back(T _data);
	void push_front(T _data);
	void insert(iterator _iter, T _data);
	void erase(iterator _iter);

	void Initailize();
	void Release();

	CMyList<T>& operator= (CMyList<T>& rhs);
private:
	bool bHasElement;
	tNode<T>* pBegin; // ù ������ ù �ּ�
	tNode<T>* pEnd; // ������ ������ ������ �ּ�

};


template<typename T>
inline CMyList<T>::CMyList():
	bHasElement(false), pBegin(nullptr), pEnd(nullptr)
{
}

template<typename T>
inline CMyList<T>::CMyList(int _iCount) :
	bHasElement(false), pBegin(nullptr), pEnd(nullptr)
{
	assign(0, _iCount);
}

template<typename T>
inline CMyList<T>::CMyList(T _default, int _iCount) :
	bHasElement(false), pBegin(nullptr), pEnd(nullptr)
{
	assign(_default, _iCount);
}

template<typename T>
inline CMyList<T>::CMyList(CMyList& rhs)
{
	bHasElement = rhs.bHasElement;
	SetFirstElem(rhs.pBegin->data);

	// ���ο� backk�̶� end�� �����س���

	tNode<T>* pPointer = rhs.pBegin->pNextNode;
	while (true)
	{
		tNode<T>* pAnotherBack = new tNode<T>;
		AddNode(pAnotherBack, pPointer->data);
		pPointer = pPointer->pNextNode;

		if (pPointer == rhs.pEnd)
		{
			break;
		}
	}
}

template<typename T>
inline CMyList<T>::~CMyList()
{
	Release();
}

template<typename T>
inline void CMyList<T>::assign(T _default, int _iCount)
{
	if (bHasElement == true)
	{
		cout << "�̹� ���Ұ� ä���� �־� �ʱ�ȭ �� �� �����ϴ�." << endl;
		return;
	}
	tNode<T>** pInitArr = new tNode<T>*[_iCount];

	SetFirstElem(_default);

	for (int i = 1; i < _iCount; ++i)
	{
		pInitArr[i] = new tNode<T>;
		AddNode(pInitArr[i], _default);
	}

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

	// end ��¡�ϴ� ���
	tNode<T>* pEndNode = new tNode<T>;
	pEnd = pEndNode;

	pBegin->pNextNode = pEndNode;
	pEnd->pPrevNode = pBegin;
}

template<typename T>
inline void CMyList<T>::AddNode(tNode<T>* _pAnotherNode, T _data)
{
	_pAnotherNode->data = _data;
	_pAnotherNode->pNextNode = pEnd;
	pEnd->pPrevNode = _pAnotherNode;

	tNode<T>* pPointer = pBegin; // ��ġ ���� ��.
	while (pPointer->pNextNode != pEnd)
	{
		//pAnotherNode->pPrevNode = pPointer;
		//pPointer->pNextNode = pAnotherNode;
		pPointer = pPointer->pNextNode;
	}
	// while������ Ż���ϸ� pPointer �� endP �ٷ����� ��� ����Ų�ٴ� ��
	// ���� back�̶��� �� back���� ����
	pPointer->pNextNode = _pAnotherNode;
	_pAnotherNode->pPrevNode = pPointer;
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
		// ���ο� backk�̶� end�� �����س���
		tNode<T>* pAnotherBack = new tNode<T>;
		
		AddNode(pAnotherBack, _data);
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
		pAnotherBegin->data = _data;
		pAnotherBegin->pNextNode = pBegin;
		pBegin->pPrevNode = pAnotherBegin;

		pBegin = pAnotherBegin;
	}
}

template<typename T>
inline void CMyList<T>::insert(iterator _iter, T _data)
{
	tNode<T>* pAnotherNode = new tNode<T>;
	pAnotherNode->data = _data;

	pAnotherNode->pPrevNode = _iter.Get_pCurrentNode();
	pAnotherNode->pNextNode = (*_iter).pNextNode;

	(*_iter).pNextNode = pAnotherNode;
	pAnotherNode->pNextNode->pPrevNode = pAnotherNode;
}

template<typename T>
inline void CMyList<T>::erase(iterator _iter)
{
	(*_iter).pPrevNode->pNextNode = (*_iter).pNextNode;
	(*_iter).pNextNode->pPrevNode = (*_iter).pPrevNode;

	tNode<T>* eraseP = _iter.Get_pCurrentNode();
	DELETE_MAC(eraseP);
}

template<typename T>
inline void CMyList<T>::Initailize()
{

}

template<typename T>
inline void CMyList<T>::Release()
{
	if (bHasElement == false)
		return;
	tNode<T>* pPointer = pBegin; // ��ġ ���� ��.
	// end �� �������� ������
	while (pPointer->pNextNode != pEnd)
	{
		tNode<T>* pTmp = pPointer;
		pPointer = pPointer->pNextNode;
		DELETE_MAC(pTmp);
	}
	DELETE_MAC(pEnd->pPrevNode);
	DELETE_MAC(pEnd);
	bHasElement = false;
}

template<typename T>
inline CMyList<T>& CMyList<T>::operator=(CMyList<T>& rhs)
{
	bHasElement = rhs.bHasElement;
	SetFirstElem(rhs.pBegin->data);

	// ���ο� backk�̶� end�� �����س���

	tNode<T>* pPointer = rhs.pBegin->pNextNode;
	while (true)
	{
		tNode<T>* pAnotherBack = new tNode<T>;
		AddNode(pAnotherBack, pPointer->data);
		pPointer = pPointer->pNextNode;

		if (pPointer == rhs.pEnd)
		{
			break;
		}
	}

	return *this;
}

#pragma region Iterator

template <typename T>
class CMyList<T>::iterator
{
public:
	// ������ �����ε�: =, ==, !=, ++, ++, +, 
	iterator& operator= (tNode<T>* _pNode)
	{
		pCurrentNode = _pNode;
		return *this;
	}

	bool operator== (tNode<T>* _pNode)
	{
		return pCurrentNode == _pNode;
	}

	bool operator!= (tNode<T>* _pNode)
	{
		return pCurrentNode != _pNode;
	}

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
				cout << "�߸��� ����" << endl;
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
		iterator tmpIter = *this; // ���� ���� �ؾ�, �� ���� �̿� ���ؼ� �ʿ� ���� ��?
		if (pCurrentNode->pNextNode)
			pCurrentNode = pCurrentNode->pNextNode;
		return tmpIter;
	}

	tNode<T>* Get_pCurrentNode()
	{
		return pCurrentNode;
	}
	//iterator& operator= (iterator& rhs);
private:
	tNode<T>* pCurrentNode;
};
#pragma endregion