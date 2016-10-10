#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <list>
#include <string>
#include <stack>
#include <map>
#include "MathEx.h"
#include "metacharacter.h"

using namespace std;

//�쳣�����ռ�
namespace ExpressionError
{
	//�Ƿ��ַ�
	const string ILLEGAL_CHARACTER_ERROR = "�Ƿ��ַ�: ";
	//���Ų�ƥ��
	const string ILLEGAL_BRACKET_ERROR = "���Ų�ƥ��";
	//ȱʧ������
	const string MISSING_OPERAND_ERROR = "ȱ�ٲ�����";
	//����Ĳ�����
	const string MISSING_OPERATOR_ERROR = "ȱ�������";
	//δ֪�쳣
	const string UNKNOWN_ERROR = "δ֪����";
}

class Expression
{
private:
	//��ѧ����
	MathEx mathEx;
	//ԭʼ�ַ���
	string raw_exp;
	//��ֺ�ı��ʽԪ���б�
	list<Metacharacter> exp;
	//������ջ
	stack<Metacharacter> op;
	//����ջ
	stack<double> number;
	//���ʽ��ֵ
	double result = 0;

	//�Ա��ʽ�����ַ��Ϸ��Եĳ������
	bool simpleCheck();
	//��ֱ��ʽ
	bool split();
	//���ż�⼰����
	void negativeOperatorPreprocessing();
	//�������ż�⼰����
	void sqrtOperatorPreprocessing();
	//�ٷֺ�/������ż�⼰����
	void percentOperatorPreprocessing();
	//�ȷ��ż�⼰����
	void degreeOperatorPreprocessing();
	//��ͬ���ż�⼰����
	void bracketPreprocessing();
	//�����������⼰����
	void preprocessing();
	//��ջ���������
	void operation();
	//ת���ɺ�׺���ʽ����ת������ֵ
	void transToPostfix();
	//��Ŀ���������
	void calc(Metacharacter mc, double &op1);
	//˫Ŀ���������
	void calc(Metacharacter mc, double &op1, double &op2);
public:
	Expression(string str, int precision = 3);
	~Expression();
	//��ȡ������
	string getResult();
};


#endif
