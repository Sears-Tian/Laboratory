//MathFuncsDll.h  动态链接库-数学模型 头文件（接口文件）

#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

namespace MathFuncs  //命名空间MathFuncs
{
	class  MyMathFuncs  //类MyMathFuncs
	{
	public:
		//修饰符__declspec(dllexport)使 DLL 能够导出该方法以供其他应用程序使用
		//加
		static MATHFUNCSDLL_API double Add(double a, double b);	
		//减
		static MATHFUNCSDLL_API double Subtract(double a, double b);
		//乘
		static MATHFUNCSDLL_API double Multiply(double a, double b);	
		//除，如果b==0，抛出异常
		static MATHFUNCSDLL_API double Divide(double a, double b);		
	};
}