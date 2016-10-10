#ifndef MATHEX_H
#define MATHEX_H

#include <string>

using namespace std;

namespace MathExError
{
	//����Ϊ0
	const string DIVISOR_ERROR = "��������Ϊ0";
	//������������С��0
	const string RADICAND_ERROR = "������������С��0";
	//����������ƽ����
	const string EXTRACT_ROOT_ERROR = "����������ƽ����";
	//ģ����������ȫΪ����
	const string MOD_ERROR = "ģ���������������Ϊ����";
	//ģ��Ϊ0
	const string MODULUS_ERROR = "ģ������Ϊ0";
	//0����ָ��Ϊ������
	const string POW_ERROR = "0����ָ������Ϊ������";
	//����Ȼ���Ľ׳�
	const string FACTORIAL_ERROR = "�׳�����Ϊ��Ȼ��";
	//���к������Ա���ȡֵ����
	const string TAN_ERROR = "���к����Ա���ȡֵ����Ϊk��+��/2";
	//�����ң����Һ����Ա���ȡֵ��Χ[-1,1]
	const string ARCSIN_ARCCOS_ERROR = "�����Һͷ����Һ����Ա�������ֵ���ܴ���1";
	//����������Ϊ������
	const string ANTILOGARITHM_ERROR = "��������������Ϊ������";
	//δ֪�쳣
	const string UNKNOWN_ERROR = "δ֪�쳣";
}

const double PI = 3.14159265358979323846;

class MathEx
{
private:
	double EPS = 1e-4;  //С������
public:
	MathEx();
	~MathEx();

	void set_eps(int e);    //���þ���,eΪС����λ��
	double getRound(double d) const;    //���ݾ�����������

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
	//�Ƕ�ת����
	double op_degree_to_radian(const double &op) const;
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
