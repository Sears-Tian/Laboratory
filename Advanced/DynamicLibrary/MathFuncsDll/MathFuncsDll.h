//MathFuncsDll.h  ��̬���ӿ�-��ѧģ�� ͷ�ļ����ӿ��ļ���

#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

namespace MathFuncs  //�����ռ�MathFuncs
{
	class  MyMathFuncs  //��MyMathFuncs
	{
	public:
		//���η�__declspec(dllexport)ʹ DLL �ܹ������÷����Թ�����Ӧ�ó���ʹ��
		//��
		static MATHFUNCSDLL_API double Add(double a, double b);	
		//��
		static MATHFUNCSDLL_API double Subtract(double a, double b);
		//��
		static MATHFUNCSDLL_API double Multiply(double a, double b);	
		//�������b==0���׳��쳣
		static MATHFUNCSDLL_API double Divide(double a, double b);		
	};
}