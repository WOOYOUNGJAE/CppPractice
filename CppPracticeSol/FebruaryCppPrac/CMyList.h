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
	CMyList(int _iCount); // count개 0으로 채워진 원소
	CMyList(T _default, int _iCount); // count개 default로 채워진 원소
	CMyList(CMyList& rhs); // 깊은 복사 생성자 완료
	//CMyList(CMyList&& rhs); // 깊은 복사 이동 생성자

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
	tNode<T>* pBegin; // 첫 원소의 첫 주소
	tNode<T>* pEnd; // 마지막 원소의 마지막 주소

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

	// 새로운 backk이랑 end랑 연결해놓기

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
		cout << "이미 원소가 채워져 있어 초기화 할 수 없습니다." << endl;
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

	// end 상징하는 노드
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

	tNode<T>* pPointer = pBegin; // 위치 지정 용.
	while (pPointer->pNextNode != pEnd)
	{
		//pAnotherNode->pPrevNode = pPointer;
		//pPointer->pNextNode = pAnotherNode;
		pPointer = pPointer->pNextNode;
	}
	// while문에서 탈출하면 pPointer 가 endP 바로이전 노드 가리킨다는 뜻
	// 기존 back이랑과 새 back끼리 연결
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
		// 새로운 backk이랑 end랑 연결해놓기
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
	tNode<T>* pPointer = pBegin; // 위치 지정 용.
	// end 전 전까지만 해제함
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

	// 새로운 backk이랑 end랑 연결해놓기

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
	// 연산자 오버로딩: =, ==, !=, ++, ++, +, 
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

	tNode<T>* Get_pCurrentNode()
	{
		return pCurrentNode;
	}
	//iterator& operator= (iterator& rhs);
private:
	tNode<T>* pCurrentNode;
};
#pragma endregion