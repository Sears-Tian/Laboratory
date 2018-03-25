////MathFuncsDll.cpp  动态链接库-数学模型 源文件（实现文件）

#include <stdexcept>		//异常处理头文件
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
			throw invalid_argument("Divisor cannot be zero!");  //抛出异常
		}
		return a / b;
	}
}