/*
	2018.11.08 15:01
	自定义实现群体数据结构：
	动态数组，链表，栈，队列
*/

#include <iostream>
#include "Array.h"
#include "Stack.h"
#include "List.h"
#include "Queue.h"
#include "DataIndex.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "*** Template Class ***" << endl;

	Array<int> a;
	cout << a.Size() << endl;

	for (int i = 0; i < a.Size(); i++)
	{
		a[i] = i + 1;
		cout << a[i] << " ";
	}
	cout << endl;

	Array<int> b = a;
	b.Resize(10);
	cout << *b << endl;
	for (int j = 0; j < b.Size(); j++)
		cout << b[j] << " ";
	cout << endl;

	cout << "======================================" << endl;
	Stack<int> stack;
	for (int ii = 0; ii < 5; ii++)
		stack.Push(ii + 100);
	cout << "Peek() = " << stack.Peek() << endl;
	cout << stack.Pop() << endl;
	cout << stack.Pop() << endl;

	stack.Clear();
	//cout << stack.Pop() << endl;
	cout << "empty? " << stack.IsEmpty() << endl;
	cout << "full? " << stack.IsFull() << endl;
	 
	cout << "=================================" << endl;
	List<int> list;
	list.SetName("list:");
	cout << list.GetName().c_str() << endl;
	list.AddTail(12);
	list.AddTail(13);
	list.AddHead(10);

	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	cout << list.InsertAfter(1, 14) << endl;
	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	//cout << list.InsertAt(10, 100) << endl;
	//list.PrintList();
	//cout << endl;

	cout << "insert index = 2" << endl;
	cout << list.InsertAfter(2, 15) << endl;
	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	list.SortAscent();
	cout << "sort: " << endl;
	list.PrintList();
	cout << endl;

	list.ModifyAt(2, 20);
	list.PrintList();
	cout << endl;

	int del = 0;
	list.DeleteHead(&del);
	list.PrintList();
	cout << endl;

	list.DeleteTail(&del);
	list.PrintList();
	cout << endl;

	int de = 0;
	list.DeleteAt(1, &de);
	cout << "delete index = 1 = " << de << endl;
	list.PrintList();
	cout << endl;

	cout << "pos = " << list.FindPosition(14) << endl;

	cout << list.IsEmpty() << endl;

	cout << "========================================" << endl;
	CircularQueue<int> cq;
	cq.QueueInsert(13);
	cq.QueueInsert(24);
	cq.QueueInsert(36);

	cout << cq.QueueDelete() << endl;
	cout << cq.QueueFront() << endl;
	cout << cq.QueueLength() << endl;
	cout << cq.IsEmpty() << endl;
	cout << cq.IsFull() << endl;

	cout << "============================================" << endl;
	int aa[] = { 14, 13, 11, 15, 12 };
	cout << DataIndex<int>::SequenceSearch(aa, 5, 11) << endl;
	cout << DataIndex<int>::BinarySearch(aa, 5, 11) << endl;

	//DataIndex<int>::BubleSort(aa, 5);
	//DataIndex<int>::SelectSort(aa, 5);
	//DataIndex<int>::InsertSort(aa, 5);
	DataIndex<int>::ExchangeSort(aa, 5);
	for (int i = 0; i < _countof(aa); i++)
		cout << aa[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}