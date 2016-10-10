#include "MathEx.h"
#include <cmath>
#include <exception>
#include <stdexcept>
using namespace std;

MathEx::MathEx()
{
}


MathEx::~MathEx()
{
}

void MathEx::set_eps(int e)
{
	EPS = pow(10, -e);
}

double MathEx::getRound(double d) const
{
	double abs_d = abs(d);
	int sign = 1;   //���d������
	if (d<0)
		sign = -1;
	return static_cast<int>(abs_d / EPS + 0.5)*EPS*sign;    //��������
}

double MathEx::op_add(const double &op1, const double &op2) const
{
	return op1 + op2;
}

double MathEx::op_subtract(const double &op1, const double &op2) const
{
	return op1 - op2;
}

double MathEx::op_multiply(const double &op1, const double &op2) const
{
	return op1 * op2;
}

double MathEx::op_divide(const double &op1, const double &op2) const
{
	if (abs(op2) < EPS) //����Ϊ0
		throw runtime_error(MathExError::DIVISOR_ERROR);
	return op1 / op2;
}

double MathEx::op_mod(const double &op1, const double &op2) const
{
	//��������������
	if (abs(op1 - static_cast<int>(op1)) > EPS || abs(op2 - static_cast<int>(op2)) > EPS)
		throw runtime_error(MathExError::MOD_ERROR);
	//ģ��Ϊ0
	if (abs(op2) <= EPS)
		throw runtime_error(MathExError::MODULUS_ERROR);
	return static_cast<int>(op1) % static_cast<int>(op2);
}

double MathEx::op_pow(const double &op1, const double &op2) const
{
	//������������0
	if (abs(op1) < EPS&&op2 < EPS)
		throw runtime_error(MathExError::POW_ERROR);
	return pow(op1, op2);
}

double MathEx::op_extract_root(const double &op1, const double &op2) const
{
	if (op1 == 2.0)
	{
		//��������С��0
		if (op2 < 0)
			throw runtime_error(MathExError::EXTRACT_ROOT_ERROR);
		return sqrt(op2);
	}
	else
	{
		//��������Ϊ��
		if (op2 < 0)
			throw runtime_error(MathExError::RADICAND_ERROR);
		return pow(op2, 1 / op1);
	}
}

double MathEx::op_factorial(const double &op) const
{
	int n = static_cast<int>(op), sum = n;
	if (op<0 || abs(op - n) > EPS)  //�׳�����Ϊ������
		throw runtime_error(MathExError::FACTORIAL_ERROR);
	if (n == 0 || n == 1)
		return 1;
	while (--n)
		sum *= n;
	return sum;
}

double MathEx::op_degree_to_radian(const double &op) const
{
	double rad = op * PI / 180;
	return rad;
}

double MathEx::op_sin(const double &op) const
{
	return sin(op);
}

double MathEx::op_cos(const double &op) const
{
	return cos(op);
}

double MathEx::op_tan(const double &op) const
{
	double angle = op * 180 / PI;
	int i_angle = static_cast<int>(angle);
	if (angle - i_angle <= EPS && (i_angle + 90) % 180 == 0)    //����ֵ��Ϊk��+��/2
		throw runtime_error(MathExError::TAN_ERROR);
	return tan(op);
}

double MathEx::op_arcsin(const double &op) const
{
	if (abs(op) > 1)    //�����ҵĶ�����Ϊ[-1,1]
		throw runtime_error(MathExError::ARCSIN_ARCCOS_ERROR);
	return asin(op);
}

double MathEx::op_arccos(const double &op) const
{
	if (abs(op) > 1)    //�����ҵĶ�����Ϊ[-1,1]
		throw runtime_error(MathExError::ARCSIN_ARCCOS_ERROR);
	return acos(op);
}

double MathEx::op_arctan(const double &op) const
{
	return atan(op);
}

double MathEx::op_lg(const double &op) const
{
	if (op < EPS)   //����������Ϊ(0,������)
		throw runtime_error(MathExError::ANTILOGARITHM_ERROR);
	return log10(op);
}

double MathEx::op_ln(const double &op) const
{
	if (op < EPS)
		throw runtime_error(MathExError::ANTILOGARITHM_ERROR);
	return log(op);
}
