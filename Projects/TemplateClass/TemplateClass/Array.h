/*
	2018.11.08 15:06 - 17:02
	类模板-动态数组：
	特点：位置连续，任意数量类型相同的元素。
	优点：元素个数可在程序运行时改变。
*/
#pragma once

#ifndef NULL

const int NULL = 0;

#endif // !NULL

#define ARRAY_SIZE 50	//默认动态数组大小


// 错误类型 枚举与信息
enum ErrorType
{
	InvalidArraySize,		//不合法的数组大小
	MemoryAllocateError,	//内存分配错误
	IndexOutOfRange			//数组下标越界
};

const char* errorInfo[] = {
	"Invalid Array Size",
	"Memory Allocate Error",
	"Invalid index: "
};


// 动态数组 类模板
template <class T>
class Array
{
public:
	~Array();

	// 构造函数
	Array(int size = ARRAY_SIZE);
	// 复制构造函数
	Array(const Array<T>& ra);

	// 重载赋值=操作符
	Array<T>& operator=(const Array<T>& ra);

	// 重载数组索引[]操作符
	T& operator[](int index);

	// 重载指针转换操作符，对象名类似数组名（首地址）
	T* operator*(void) { return m_list; }

	// 当前数组大小
	int Size(void) const { return m_size; }

	// 重设数组大小
	void Resize(const int newSize);

private:
	// 错误信息
	void Error(ErrorType error, int badIndex = 0);

private:
	int m_size;	//动态数组大小
	T* m_list;	//动态数组首地址指针
};

template <class T>
Array<T>::~Array()
{
	delete[] m_list;	//释放内存堆内空间
}

template<class T>
inline Array<T>::Array(int size)
{
	// 欲分配的数组元素<=0则输出错误信息
	if (size <= 0)
		Error(ErrorType::InvalidArraySize);

	// 动态分配size个类型的元素空间
	m_size = size;
	m_list = new T[size];
	if (NULL == m_list)
		Error(ErrorType::MemoryAllocateError);
}

template<class T>
inline Array<T>::Array(const Array<T>& ra)
{
	// 从对象ra中取得数组大小赋值给当前对象
	this->m_size = ra.m_size;
	int size = ra.m_size;

	// 申请内存
	this->m_list = new T[size];
	if (NULL == this->m_list)
		Error(ErrorType::MemoryAllocateError);

	// 深层复制
	T* srcptr = ra.m_list;		//对象ra的数组首地址
	T* dstptr = this->m_list;	//本对象中的数组首地址
	while (size--)
	{
		*dstptr++ = *srcptr++;	//逐个复制数组元素
	}
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array<T>& ra)
{
	int size = ra.m_size;

	// 如果大小不同，则删除数组原有内存重新分配
	if (this->m_size != size)
	{
		delete[] m_list;

		this->m_list = new T[size];
		if (NULL == this->m_list)
			Error(ErrorType::MemoryAllocateError);
	}

	T* srcptr = ra.m_list;
	T* dstprt = this->m_list;
	while (size)
	{
		*dstptr++ = *srcptr++;
	}
	
	return *this;
}

template<class T>
inline T & Array<T>::operator[](int index)
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	// 返回下标为index的数组元素
	return this->m_list[index];
}

template<class T>
inline void Array<T>::Resize(const int newSize)
{
	// 检查重设数组大小是否正常
	if (newSize <= 0)
		Error(ErrorType::InvalidArraySize);

	// 如果与原来数组大小一致，什么都不做，直接返回
	if (newSize == this->m_size)
		return;

	// 重设大小，取两者较小值
	T* newList = new T[newSize];
	if (NULL == newList)
		Error(ErrorType::MemoryAllocateError);

	int size = ((newSize <= this->m_size) ? newSize : this->m_size);
	T* srcptr = this->m_list;
	T* dstptr = newList;
	while (size--)
	{
		*dstptr++ = *srcptr++;
	}

	// 使m_list指向新数组，并更新m_size
	this->m_list = newList;
	this->m_size = newSize;	
}

template<class T>
inline void Array<T>::Error(ErrorType error, int badIndex)
{
	//根据错误类型，输出相应的错误信息
	cout << errorInfo[error];
	
	if (ErrorType::IndexOutOfRange == error)
		cout << badIndex;						//下标越界，输出错误的下标

	cout << endl;
}
