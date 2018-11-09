/*
	2018.11.08 17:13 - 18:03
	类模板-栈（静态数组）
	特点：先进后出，后进先出。
	应用：函数调用，表达式处理。
	基本状态：栈空，栈满，一般状态。
*/
#pragma once

#define STACK_SIZE 50

// 栈 类模板
template<class T>
class Stack
{
public:
	Stack() : m_top(-1) { }
	~Stack() { }

	// 压栈
	void Push(const T& item);

	// 出栈
	T Pop(void);

	// 清空栈，只需要将栈索引设置为-1即可
	void Clear(void) { m_top = -1; }

	// 读取栈顶元素
	T Peek(void) const;

	// 判断是否为栈空
	bool IsEmpty(void) { return m_top == -1; }

	// 判断是否为栈满
	bool IsFull(void) { return m_top == STACK_SIZE - 1; }

private:
	int m_top;				//栈索引，0 ~ STACK_SIZE-1
	T m_list[STACK_SIZE];	//栈数组
};

template<class T>
inline void Stack<T>::Push(const T & item)
{
	if (m_top >= STACK_SIZE - 1)
	{
		cerr << "Stack overflow!" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		m_top++;
		m_list[m_top] = item;
	}
}

template<class T>
inline T Stack<T>::Pop(void)
{
	if (m_top < 0)
	{
		cerr << "Attemp to pop an empty stack!" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		T temp = m_list[m_top];
		m_top--;
		return temp;
	}
}

template<class T>
inline T Stack<T>::Peek(void) const
{
	if (m_top < 0)
	{
		cerr << "Attempt to peek at an empty stack!" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		return m_list[m_top];
	}
}
