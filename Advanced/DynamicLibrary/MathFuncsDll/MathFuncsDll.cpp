////MathFuncsDll.cpp  ��̬���ӿ�-��ѧģ�� Դ�ļ���ʵ���ļ���

#include <stdexcept>		//�쳣����ͷ�ļ�
#include "MathFuncsDll.h"

using namespace std;

namespace MathFuncs
{
	double MyMathFuncs::Add(double a, double b)
	{
		return a + b;
	}

	double MyMathFuncs::Subtract(double a, double b)
	{
		return a - b;
	}

	double MyMathFuncs::Multiply(double a, double b)
	{
		return a * b;
	}

	double MyMathFuncs::Divide(double a, double b)
	{
		if (b == 0)
		{
			throw invalid_argument("Divisor cannot be zero!");  //�׳��쳣
		}
		return a / b;
	}
}