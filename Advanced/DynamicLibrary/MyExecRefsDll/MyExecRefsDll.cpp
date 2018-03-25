//动态链接库使用的程序文件

#include <iostream>
#include <cstdlib>
#include "../MathFuncsDll/MathFuncsDll.h"  //包含数学模型动态链接库头文件
											// ..表示父级目录；.表示当前目录
using namespace std;

int main(void)
{
	double a = 13.4;
	double b = 2.0;

	cout << "a = " << a << "\n"
		<< "b = " << b << endl;
	cout << "a + b = " <<
		MathFuncs::MyMathFuncs::Add(a, b) << endl;
	cout << "a - b = " <<
		MathFuncs::MyMathFuncs::Subtract(a, b) << endl;
	cout << "a * b = " <<
		MathFuncs::MyMathFuncs::Multiply(a, b) << endl;
	cout << "a / b = " <<
		MathFuncs::MyMathFuncs::Divide(a, b) << endl;

	cout << "a / 0 = " << endl;
	try
	{	//对于可能出现异常的语句块进行try一下
		cout << MathFuncs::MyMathFuncs::Divide(a, 0) << endl;
	}
	catch (const invalid_argument& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	system("pause");
	return 0;
}