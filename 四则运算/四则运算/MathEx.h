#pragma once
#ifndef MATHEX_H
#define MATHEX_H

#include <string>

using std::string;

namespace MathExError
{
	//����Ϊ0
	const string DIVISOR_ERROR = "Divisor cannot be zero.";
	//��ָ��Ϊ0
	const string RADICAL_EXPONENT_ERROR = "Radical exponent cannot be zero";
	//��ָ���ͱ���������ͻ
	const string EXTRACT_ROOT_ERROR = "Radicand and radical exponent are conflicting.";
	//ģ����������ȫΪ����
	const string MOD_ERROR = "Both dividend and modulus need be a integer.";
	//ģ��Ϊ0
	const string MODULUS_ERROR = "Modulus cannot be zero";
	//0����ָ��Ϊ������
	const string POW_ERROR = "The exponent connot be a non-zero negative number when the base is zero";
	//����Ȼ���Ľ׳�
	const string FACTORIAL_ERROR = "Factorial is defined for natural numbers.";
	//���к������Ա���ȡֵ����
	const string TAN_ERROR = "Tangent error";
	//�����ң����Һ����Ա���ȡֵ��Χ[-1,1]
	const string ARCSIN_ARCCOS_ERROR = "The absolute value of x of arcsin x or arccos x cannot be great than 1";
	//����������Ϊ������
	const string ANTILOGARITHM_ERROR = "The antilogarithm cannot be  zero or a negative";
	//δ֪�쳣
	const string UNKNOWN_ERROR = "unknown error";
}

const double PI = 3.14159265358979323846;

class MathEx
{
private:
	double EPS = 1e-15;
public:
	MathEx();
	~MathEx();

	void set_eps(double e);

	//�ӷ�����
	double op_add(const double &op1, const double &op2) const;
	//��������
	double op_subtract(const double &op1, const double &op2) const;
	//�˷�����
	double op_multiply(const double &op1, const double &op2) const;
	//��������
	double op_divide(const double &op1, const double &op2) const;
	//ģ����
	double op_mod(const double &op1, const double &op2) const;
	//�˷�����
	double op_pow(const double &op1, const double &op2) const;
	//��������
	double op_extract_root(const double &op1, const double &op2) const;
	//�׳�����
	double op_factorial(const double &op) const;
	//�������㣬opΪ����
	double op_sin(const double &op) const;
	//�������㣬opΪ����
	double op_cos(const double &op) const;
	//�������㣬opΪ����
	double op_tan(const double &op) const;
	//���������㣬����ֵΪ����
	double op_arcsin(const double &op) const;
	//���������㣬����ֵΪ����
	double op_arccos(const double &op) const;
	//���������㣬����ֵΪ����
	double op_arctan(const double &op) const;
	//���ö���������Ϊ10
	double op_lg(const double &op) const;
	//��Ȼ����������Ϊe
	double op_ln(const double &op) const;
};

#endif // !MATHEX_H
