/*
	2018.11.09 20:37 - 21:11
	类模板-队列：一般队列，循环队列（已实现）
	特点：先进先出，后进后出。
	基本状态：队空，队满，一般状态。
*/

#pragma once

#define QUEUE_SIZE 50	//默认循环队列空间

// 循环队列 类模板
template<class T>
class CircularQueue
{
public:
	CircularQueue();
	~CircularQueue();

	// 入队
	void QueueInsert(const T& value);

	// 出队
	T QueueDelete(void);

	// 清空队列
	void ClearQueue(void) { m_front = m_rear = m_count = 0; }

	// 访问队首元素
	T QueueFront(void) const { return m_qlist[m_front]; }

	// 队列长度
	int QueueLength(void) const { return m_count; }

	// 判断是否队空
	bool IsEmpty(void) const { return 0 == m_count; }

	// 判断是否队满
	bool IsFull(void) const { return QUEUE_SIZE == m_count; }

private:
	int m_front;	//队头
	int m_rear;		//队尾
	int m_count;	//元素计数器，区分是否为队空或队满
	T* m_qlist;		//队列指针，构建动态队列
};

template<class T>
CircularQueue<T>::CircularQueue()
{
	m_front = m_rear = m_count = 0;
	m_qlist = new T[QUEUE_SIZE];
}

template<class T>
CircularQueue<T>::~CircularQueue()
{
	delete[]m_qlist;
}

template<class T>
inline void CircularQueue<T>::QueueInsert(const T & value)
{
	if (QUEUE_SIZE == m_count)
	{
		cerr << "Queue overflow!" << endl;
		system("pause");
		exit(1);
	}

	m_qlist[m_rear] = value;			//队尾插入元素
	m_count++;

	m_rear = (m_rear + 1) % QUEUE_SIZE;	//取余实现循环队列
}

template<class T>
inline T CircularQueue<T>::QueueDelete(void)
{
	if (0 == m_count)
	{
		cerr << "Empty queue!" << endl;
		system("pause");
		exit(1);
	}

	T temp = m_qlist[m_front];
	m_count--;

	m_front = (m_front + 1) % QUEUE_SIZE;	//队首增1

	return temp;
}
