/*
	2019.06.11 15:36 - 2019.10.31 23:18
	算法与数据结构：图 
	深度优先遍历 DFS，广度优先遍历 BFS，最小生成树：prim，kruskal
	2019.10.31 修改BFS为队列存储；增加了多源最短路径的Floyd算法，二维数组传参要转换为指针数组！
*/

#include "Graph.h"

int main(int argc, char* argv[])
{
	cout << "*** Graph Theory ***" << endl;
	cout << "** DFS & BFS **" << endl;
	// 定义图指针实例
	const int CAPACITY = 8;
	Graph* pGraph = new Graph(CAPACITY);
	
	//// 定义结点，方法1.
	//Node* pNodeA = new Node("A");
	//Node* pNodeB = new Node("B");
	//Node* pNodeC = new Node("C");
	//Node* pNodeD = new Node("D");
	//Node* pNodeE = new Node("E");
	//Node* pNodeF = new Node("F");
	//Node* pNodeG = new Node("G");
	//Node* pNodeH = new Node("H");

	// 定义结点，方法2.
	vector<Node*> vecpNode;
	vecpNode.push_back(new Node("A"));
	vecpNode.push_back(new Node("B"));
	vecpNode.push_back(new Node("C"));
	vecpNode.push_back(new Node("D"));
	vecpNode.push_back(new Node("E"));
	vecpNode.push_back(new Node("F"));
	vecpNode.push_back(new Node("G"));
	vecpNode.push_back(new Node("H"));

	// 向图中添加结点
	for (auto& pnode : vecpNode)
		pGraph->AddNode(pnode);

	//// 设置邻接矩阵的值，方法1.
	//pGraph->SetValueToMatrixForUndirectedGraph(0, 1);
	//pGraph->SetValueToMatrixForUndirectedGraph(0, 3);
	//pGraph->SetValueToMatrixForUndirectedGraph(1, 2);
	//pGraph->SetValueToMatrixForUndirectedGraph(1, 5);
	//pGraph->SetValueToMatrixForUndirectedGraph(2, 4);
	//pGraph->SetValueToMatrixForUndirectedGraph(3, 6);
	//pGraph->SetValueToMatrixForUndirectedGraph(3, 7);
	//pGraph->SetValueToMatrixForUndirectedGraph(4, 5);
	//pGraph->SetValueToMatrixForUndirectedGraph(6, 7);
	//pGraph->PrintMatrix();
	//cout << endl;

	// 设置邻接矩阵的值，方法2. 静态数组，传递函数参数需要强制转换！
	int matrix[CAPACITY][CAPACITY] = {
		/*		 A  B  C  D  E  F  G  H  */
		/* A */ {0, 1, 0, 1, 0, 0, 0, 0},
		/* B */ {1, 0, 1, 0, 0, 1, 0, 0},
		/* C */ {0, 1, 0, 0, 1, 0, 0, 0},
		/* D */ {1, 0, 0, 0, 0, 0, 1, 1},
		/* E */ {0, 0, 1, 0, 0, 1, 0, 0},
		/* F */ {0, 1, 0, 0, 1, 0, 0, 0},
		/* G */ {0, 0, 0, 1, 0, 0, 0, 1},
		/* H */	{0, 0, 0, 1, 0, 0, 1, 0} };
	pGraph->SetValueToMatrix((int**)matrix);	// (int**)matrix
	pGraph->PrintMatrix();

	cout << "=== Depth First Search ===" << endl;
	pGraph->ResetNode();
	pGraph->DepthFirstSearch(0);
	cout << endl;

	cout << "=== Breadth First Search ===" << endl;
	pGraph->ResetNode();
	pGraph->BreadthFirstSearch(0);
	cout << endl;

	cout << "=== Shortest Path Matrix: Floyd ===" << endl;
	const int LEN = 7;
	int matrix2[LEN][LEN] = {
		/*		 A  B  C  D  E  F  G  H  */
		/* A */ { 0,  5,  2, -1, -1, -1, -1},
		/* B */ { 5,  0, -1,  1,  6, -1, -1},
		/* C */ { 2, -1,  0,  6, -1,  8, -1},
		/* D */ {-1,  1,  6,  0,  1,  2, -1},
		/* E */ {-1,  6, -1,  1,  0, -1, 7 },
		/* F */ {-1, -1,  8,  2,  1,  0, 3 },
		/* G */ {-1, -1, -1, -1,  7,  3, 0 }};
	int* pm[LEN];
	for(int i = 0; i < LEN; i++)
		pm[i] = matrix2[i];
	Graph::Floyd(pm, LEN);		//二维数组传参要转换为指针数组！

	// 删除分配的堆空间
	delete pGraph;
	for (auto& pnodeDel : vecpNode)
		delete pnodeDel;

	cout << endl;
	cout << "** Minimum Spanning Tree **" << endl;
	const int CAPACITY2 = 6;
	//const string ALPHA[CAPACITY2] = { "A", "B", "C", "D", "E", "F" };
	enum EAlpha { A = 0, B = 1, C = 2, D = 3, E = 4, F = 5};

	Graph* pGraph2 = new Graph(CAPACITY2);

	//// 定义结点，方法3.
	//vector<Node*> vecpNode2;
	//for(int index = 0; index < CAPACITY2; index++)
	//	vecpNode2.push_back(new Node(ALPHA[index]));
	vector<Node*> vecpNode2;
	vecpNode2.push_back(new Node("A"));
	vecpNode2.push_back(new Node("B"));
	vecpNode2.push_back(new Node("C"));
	vecpNode2.push_back(new Node("D"));
	vecpNode2.push_back(new Node("E"));
	vecpNode2.push_back(new Node("F"));

	for (auto& pnode2 : vecpNode2)
		pGraph2->AddNode(pnode2);


	//// 格式1. 
	//pGraph2->SetValueToMatrixForUndirectedGraph(0, 1, 6);
	//pGraph2->SetValueToMatrixForUndirectedGraph(0, 4, 5);
	//pGraph2->SetValueToMatrixForUndirectedGraph(0, 5, 1);
	//pGraph2->SetValueToMatrixForUndirectedGraph(1, 2, 3);
	//pGraph2->SetValueToMatrixForUndirectedGraph(1, 5, 2);
	//pGraph2->SetValueToMatrixForUndirectedGraph(2, 5, 8);
	//pGraph2->SetValueToMatrixForUndirectedGraph(2, 3, 7);
	//pGraph2->SetValueToMatrixForUndirectedGraph(3, 5, 4);

	// 格式2. 
	pGraph2->SetValueToMatrixForUndirectedGraph(A, B, 6);
	pGraph2->SetValueToMatrixForUndirectedGraph(A, E, 5);
	pGraph2->SetValueToMatrixForUndirectedGraph(A, F, 1);
	pGraph2->SetValueToMatrixForUndirectedGraph(B, C, 3);
	pGraph2->SetValueToMatrixForUndirectedGraph(B, F, 2);
	pGraph2->SetValueToMatrixForUndirectedGraph(C, F, 8);
	pGraph2->SetValueToMatrixForUndirectedGraph(C, D, 7);
	pGraph2->SetValueToMatrixForUndirectedGraph(D, F, 4);
	pGraph2->SetValueToMatrixForUndirectedGraph(D, E, 2);
	pGraph2->SetValueToMatrixForUndirectedGraph(E, F, 9);


	cout << "=== Prim Tree ===" << endl;
	pGraph2->PrimTree(0/*, ALPHA*/);

	cout << "=== Kruskal Tree ===" << endl;
	pGraph2->KruskalTree(0);

	// 删除分配的堆空间
	delete pGraph2;
	for (auto& pnodeDel2 : vecpNode2)
		delete pnodeDel2;


	system("pause");
	return 0;
}

/*** VS2017运行结果：
*** Graph Theory ***
** DFS & BFS **
0 1 0 1 0 0 0 0
1 0 1 0 0 1 0 0
0 1 0 0 1 0 0 0
1 0 0 0 0 0 1 1
0 0 1 0 0 1 0 0
0 1 0 0 1 0 0 0
0 0 0 1 0 0 0 1
0 0 0 1 0 0 1 0
=== Depth First Search ===
A B C E F D G H
=== Breadth First Search ===
A B D C F G H E
=== Shortest Path Matrix: Floyd ===
 0  5  2 -1 -1 -1 -1
 5  0 -1  1  2 -1 -1
 2 -1  0  6 -1  8 -1
-1  1  6  0  1  2 -1
-1  2 -1  1  0 -1  7
-1 -1  8  2  1  0  3
-1 -1 -1 -1  4  3  0

** Minimum Spanning Tree **
=== Prim Tree ===
A 0 - 5 F = 1
F 5 - 1 B = 2
B 1 - 2 C = 3
F 5 - 3 D = 4
D 3 - 4 E = 2
=== Kruskal Tree ===
A 0 - 5 F = 1
B 1 - 5 F = 2
D 3 - 4 E = 2
B 1 - 2 C = 3
D 3 - 5 F = 4
请按任意键继续. . .
***/