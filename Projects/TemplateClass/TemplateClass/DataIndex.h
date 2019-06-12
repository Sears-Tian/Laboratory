/*
	2018.11.09 21:14 - 22:16
	数据检索 类模板：
	查找：顺序查找，折半查找
2018.11.19 10:05 - 11:45 增加表外排序，通过二级指针指向元素或一级指针记录下标，存储序列而元素原始位置保持不变。
2019.05.29 增加快速排序并测试

*/
#pragma once

template<class T>
class DataIndex
{
public:
	// 表外排序回调函数指针
	using OrderCallback = bool(*)(T, T);

public:
	DataIndex();
	~DataIndex();

	// 顺序查找，返回查到的值的索引，没有则返回-1
	static int SequenceSearch(const T list[], int n, const T& key);

	// 折半查找
	static int BinarySearch(const T list[], int n, const T& key);

	// 冒泡排序
	static void BubleSort(T list[], int n);

	// 选择排序
	static void SelectSort(T list[], int n);

	// 插入排序
	static void InsertSort(T list[], int n);

	// 交换排序
	static void ExchangeSort(T list[], int n);

	// 快速排序
	static int FindPos(T list[], int low, int high);
	static void QuickSort(T list[], int low, int high);

	// 数组表外排序，二级指针
	static T** ExternalOrderArray(T list[], int n, OrderCallback function);
	// 表外排序打印，二级指针
	static void ExternalPrintArray(T** pOrder, int n);

	// 数组表外排序，一级指针，记录下标
	static T* ExternalOrderIndex(T list[], int n, OrderCallback function);
	// 表外排序打印，一级指针，记录下标
	static void ExternalPrintIndex(T* pOrder, T list[], int n);


	// 交换。亦可用于交换指针指向
	static void Swap(T& x, T& y);
};

template<class T>
DataIndex<T>::DataIndex()
{
}

template<class T>
DataIndex<T>::~DataIndex()
{
}

template<class T>
inline int DataIndex<T>::SequenceSearch(const T list[], int n, const T& key)
{
	for (int i = 0; i < n; i++)
	{
		if (list[i] == key)
		{
			return i;
		}
	}

	return -1;
}

template<class T>
inline int DataIndex<T>::BinarySearch(const T list[], int n, const T& key)
{
	int mid, low = 0, high = n - 1;	//中间，低与高索引下标
	T midValue;
	while (low <= high)
	{
		mid = (low + high) / 2;
		midValue = list[mid];
		
		if (key == midValue)
			return mid;
		else if (key < midValue)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

template<class T>
inline void DataIndex<T>::BubleSort(T list[], int n)
{
	//for (int i = 0; i < n - 1; i++)
	//	for (int j = i + 1; j < n; j++)
	//		if (list[i] > list[j])
	//			DataIndex::Swap(list[i], list[j]);

	// 算法2
	for (int ii = 0; ii < n - 1; ii++)
		for (int jj = 0; jj < n - ii - 1; jj++)
			if (list[jj] > list[jj + 1])
				DataIndex::Swap(list[jj], list[jj + 1]);
}

template<class T>
inline void DataIndex<T>::SelectSort(T list[], int n)
{
	int small;
	for (int i = 0; i < n - 1; i++)
	{
		small = i;
		for (int j = i + 1; j < n; j++)
			if (list[j] < list[small])
				small = j;
		if (small != i)
			DataIndex::Swap(list[small], list[i]);
	}
}

template<class T>
inline void DataIndex<T>::InsertSort(T list[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i;
		T temp = list[i];
		while (j > 0 && temp < list[j - 1])
		{
			list[j] = list[j - 1];
			j--;
		}
		list[j] = temp;
	}
}

template<class T>
inline void DataIndex<T>::ExchangeSort(T list[], int n)
{
	int last;
	int i = n - 1;
	while (i > 0)
	{
		last = 0;
		for(int j = 0; j < i; j++)
			if (list[j + 1] < list[j])
			{
				DataIndex::Swap(list[j + 1], list[j]);
				last = j;
			}
		i = last;
	}
}

template<class T>
int DataIndex<T>::FindPos(T list[], int low, int high)
{
	T value = list[low];
	// 循环结束时，low == high
	while (low < high)
	{
		while (low < high && list[high] >= value)
			--high;
		list[low] = list[high];

		while (low < high && list[low] <= value)
			++low;
		list[high] = list[low];
	}
	list[low] = value;

	return low;
}

template<class T>
void DataIndex<T>::QuickSort(T list[], int low, int high)
{
	int pos = 0;
	if (low < high)
	{
		pos = DataIndex<T>::FindPos(list, low, high);
		DataIndex<T>::QuickSort(list, low, pos - 1);
		DataIndex<T>::QuickSort(list, pos + 1, high);
	}
}

template<class T>
inline T ** DataIndex<T>::ExternalOrderArray(T list[], int n, OrderCallback function)
{
	T** pOrder = new T*[n];
	for (int index = 0; index < n; index++)
		pOrder[index] = &list[index];

	int i, j, m;
	for (i = 0; i < n - 1; i++)
	{
		m = i;
		for (j = i + 1; j < n; j++)
			if (function(*pOrder[j], *pOrder[m]))		//通过函数指针调用
				m = j;
		if (m != i)
			DataIndex<T*>::Swap(pOrder[m], pOrder[i]);	//交换指针指向
	}
	return pOrder;
}

template<class T>
inline void DataIndex<T>::ExternalPrintArray(T ** pOrder, int n)
{
	for (int i = 0; i < n; i++)
		std::wcout << *pOrder[i] << " ";
	std::wcout << std::endl;
}

template<class T>
inline T * DataIndex<T>::ExternalOrderIndex(T list[], int n, OrderCallback function)
{
	T* pOrder = new T[n];
	for (int index = 0; index < n; index++)
		pOrder[index] = index;

	int i, j, m;
	for (i = 0; i < n - 1; i++)
	{
		m = i;
		for (j = i + 1; j < n; j++)
			if (function(list[pOrder[j]], list[pOrder[m]]))		//通过函数指针调用
				m = j;
		if (m != i)
			DataIndex<T>::Swap(pOrder[m], pOrder[i]);			//交换数值引用
	}
	return pOrder;
}

template<class T>
inline void DataIndex<T>::ExternalPrintIndex(T* pOrder, T list[], int n)
{
	for (int i = 0; i < n; i++)
		std::wcout << list[pOrder[i]] << " ";
	std::wcout << std::endl;
}

template<class T>
inline void DataIndex<T>::Swap(T & x, T & y)
{
	T t;
	t = x;
	x = y;
	y = t;
}
