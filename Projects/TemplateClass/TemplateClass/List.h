/*
	2018.11.08 21:48 - 2018.11.09 20:22
	类模板-链表：单向链表（已实现），双向链表，循环链表
*/
#pragma once

// 添加新行 枚举
enum AppendNewLine
{
	NoNewLine,	//以空格分隔
	AddNewLine	//以换行分隔
};


// 单向链表 类模板
template <class T>
class List
{
protected:
	// 结点结构体模板
	template <class T>
	struct Node
	{
		T data;			//数据域
		Node<T>* pNext;	//指针域
	};

public:
	List();
	~List();

	// 新建结点，仅填充数据域
	Node<T>* NewNode(const T& newData);
	// 释放结点
	void FreeNode(Node<T>* node);

	// 头插法
	void AddHead(const T& value);
	// 尾插法
	void AddTail(const T& value);
	// 中间插入，在索引之后
	bool InsertAfter(const int index, const T& value);

	// 删除第一个结点，out_value: 被删除的结点数据
	bool DeleteHead(T* out_value);
	// 删除最后一个结点，out_value: 被删除的结点数据
	bool DeleteTail(T* out_value);
	// 删除位置为position的结点，out_value: 被删除的结点数据
	bool DeleteAt(const int index, T* out_value);

	// 清空链表
	void ClearAll();

	// 修改位置为position结点的数据为in_value
	bool ModifyAt(const int index, const T& in_value);

	// 查找第一个数据值为key的结点，返回其在链表的索引位置
	int FindPosition(const T& key);

	// 对链表排序，升序，针对于数值型数据域
	void SortAscent(void);

	// 判断链表是否为空
	bool IsEmpty() { return NULL == m_pHeadNode->pNext; }

	// 获取链表大小（长度）
	int GetSize() const { return m_size; }
	// 获取链表名字
	std::string GetName() const { return m_name; }
	// 设置链表名字
	void SetName(const std::string& name) { m_name = name; }

	// 打印链表数据
	void PrintList(AppendNewLine addnl = AppendNewLine::NoNewLine);

private:
	Node<T> * m_pHeadNode;		//指向第一个结点（头指针）
	//Node<T> * m_pRearNode;		//指向最后一个结点（尾指针）
	int m_size;				//链表元素个数
	//int m_position;			//索引位置，默认从0开始，与数组相似
	std::string m_name;			//链表名字
};

template <class T>
List<T>::List()
{
	m_pHeadNode = NULL;
	//m_pRearNode = NULL;
	m_size = 0;
	//m_position = -1;
	m_name.clear();
}

template <class T>
List<T>::~List()
{
	ClearAll();
}

template<class T>
inline List<T>::Node<T>* List<T>::NewNode(const T & newData)
{
	Node<T>* newNode = new Node<T>;
	if (NULL == newNode)
	{
		cout << "Memory allocate failure!" << endl;
		system("pause");
		exit(1);
	}
		
	newNode->data = newData;
	return newNode;
}

template<class T>
inline void List<T>::FreeNode(Node<T>* node)
{
	delete node;
	node = NULL;
}

template<class T>
inline void List<T>::AddHead(const T & value)
{
	Node<T>* newNode = NewNode(value);
	newNode->pNext = this->m_pHeadNode;
	this->m_pHeadNode = newNode;

	this->m_size++;
}

template<class T>
inline void List<T>::AddTail(const T & value)
{
	Node<T>* newNode = NewNode(value);
	newNode->pNext = NULL;
	if (!this->m_pHeadNode)
	{
		this->m_pHeadNode = newNode;

		this->m_size++;

		return;
	}

	Node<T>* tmpNode = this->m_pHeadNode;
	while (tmpNode->pNext != NULL)
	{
		tmpNode = tmpNode->pNext;
	}
	tmpNode->pNext = newNode;

	this->m_size++;
}

template<class T>
inline bool List<T>::InsertAfter(const int index, const T & value)
{
	int position = 0;
	Node<T>* prevNode = this->m_pHeadNode;

	if (index <= 0)
	{
		AddHead(value);
		return true;
	}

	while (prevNode != NULL && position < index - 1)
	{
		prevNode = prevNode->pNext;
		position++;
	}
	if (NULL == prevNode || position > index - 1)
		return false;

	Node<T>* newNode = NewNode(value);
	newNode->pNext = prevNode->pNext;
	prevNode->pNext = newNode;

	this->m_size++;

	return true;
}

template<class T>
inline bool List<T>::DeleteHead(T * out_value)
{
	if (NULL == this->m_pHeadNode)
		return false;
	
	Node<T>* deletedNode = this->m_pHeadNode;
	*out_value = deletedNode->data;
	this->m_pHeadNode = this->m_pHeadNode->pNext;
	FreeNode(deletedNode);
	
	this->m_size--;

	return true;
}

template<class T>
inline bool List<T>::DeleteTail(T * out_value)
{
	if (NULL == this->m_pHeadNode)
		return false;

	Node<T>* prevNode = NULL;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode->pNext != NULL)
	{
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	*out_value = currNode->data;
	FreeNode(currNode);
	prevNode->pNext = NULL;

	this->m_size--;

	return true;
}

template<class T>
inline bool List<T>::DeleteAt(const int index, T * out_value)
{
	int position = 1;
	Node<T>* prevNode = this->m_pHeadNode;

	if (index <= 1)
	{
		DeleteHead(out_value);
		return true;
	} 

	while (prevNode != NULL && position < index - 1)
	{
		prevNode = prevNode->pNext;
		position++;
	}
	if (NULL == prevNode || position > index - 1)
		return false;

	Node<T>* deletedNode = prevNode->pNext;
	*out_value = deletedNode->data;			//取出被删除结点的数据
	prevNode->pNext = deletedNode->pNext;
	
	FreeNode(deletedNode);

	this->m_size--;

	return true;
}

template<class T>
inline void List<T>::ClearAll()
{
	Node<T>* prevNode = nullptr;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		prevNode = currNode;

		currNode = currNode->pNext;

		FreeNode(prevNode);
	}
	this->m_pHeadNode = NULL;

	this->m_size = 0;
}

template<class T>
inline bool List<T>::ModifyAt(const int index, const T & in_value)
{
	int position = 1;
	Node<T>* currNode = this->m_pHeadNode;

	while (currNode != NULL && position < index)
	{
		currNode = currNode->pNext;
		position++;
	}
	if (NULL == currNode || position > index)
		return false;

	currNode->data = in_value;

	return true;
}

template<class T>
inline int List<T>::FindPosition(const T & key)
{
	int position = 1;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		if (key == currNode->data)
			return position;

		currNode = currNode->pNext;
		position++;
	}

	return -1;
}

template<class T>
inline void List<T>::SortAscent(void)
{
	int i, j, temp;
	int size = this->m_size;
	Node<T>* prevNode;
	Node<T>* nextNode;
	
	for(i = 0, prevNode = this->m_pHeadNode; i < size - 1; i++, prevNode = prevNode->pNext)
		for (j = i + 1, nextNode = prevNode->pNext; j < size; j++, nextNode = nextNode->pNext)
		{
			if (prevNode->data > nextNode->data)
			{
				temp = prevNode->data;
				prevNode->data = nextNode->data;
				nextNode->data = temp;
			}
		}

	return;
}

template<class T>
inline void List<T>::PrintList(AppendNewLine addnl)
{
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		if (AppendNewLine::NoNewLine == addnl)
			cout << currNode->data << " ";
		else
			cout << currNode->data << endl;

		currNode = currNode->pNext;
	}
}
