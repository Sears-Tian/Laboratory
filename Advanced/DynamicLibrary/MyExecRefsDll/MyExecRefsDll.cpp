//��̬���ӿ�ʹ�õĳ����ļ�

#include <iostream>
#include <cstdlib>
#include "../MathFuncsDll/MathFuncsDll.h"  //������ѧģ�Ͷ�̬���ӿ�ͷ�ļ�
											// ..��ʾ����Ŀ¼��.��ʾ��ǰĿ¼
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
	{	//���ڿ��ܳ����쳣���������tryһ��
		cout << MathFuncs::MyMathFuncs::Divide(a, 0) << endl;
	}
	catch (const invalid_argument& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	system("pause");
	return 0;
}