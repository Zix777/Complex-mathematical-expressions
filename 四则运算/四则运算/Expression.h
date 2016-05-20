#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <list>
#include <string>
#include <stack>
#include <map>
#include "MathEx.h"

using namespace std;

struct metacharacter {
	//0Ϊ���֣�����С���㣩��1Ϊ�������2Ϊ����
	int type;
	//ջ�����ȼ�������Ϊ0
	int out_priority;
	//ջ�����ȼ�������Ϊ0
	int in_priority;
	//���������������ֺ�����Ϊ0
	int operand;
	/*�����λ�ã����ֺ�����Ϊ0
	 *������ڲ�����֮ǰ��֮���֮��ֱ�Ϊ1,2��3��ʾ
	 */
	int position;
	//�����Ԫ��
	string e;
};

//�쳣�����ռ�
namespace ExpressionError
{
	//�Ƿ��ַ�
	const string ILLEGAL_CHARACTER_ERROR = "Illegal character: ";
	//���Ų�ƥ��
	const string ILLEGAL_BRACKET_ERROR = "Unmatched bracket";
	//��������
	const string NEEDLESS_BARCKET_ERROR = "Needless bracket";
	//ȱʧ������
	const string MISSING_OPERAND_ERROR = "Missing operand";
	//δ֪�쳣
	const string UNKNOWN_ERROR = "Unknown error";
}

class Expression
{
private:
	//���ʽԪ����Ϣ
	const static map<string,metacharacter> METACHARACTER;
	//��ѧ����
	MathEx mathEx;
	//ԭʼ�ַ���
	string raw_exp;
	//��ֺ�ı��ʽԪ���б�
	list<metacharacter> exp;
	//������ջ
	stack<metacharacter> op;
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
	//��ͬ���ż�⼰����
	void bracketPreprocessing();
	//�����������⼰����
	void preprocessing();
	//��ջ���������
	void operation();
	//ת���ɺ�׺���ʽ����ת������ֵ
	void transToPostfix();
	//��Ŀ���������
	void calc(metacharacter mc, double &op1);
	//˫Ŀ���������
	void calc(metacharacter mc, double &op1, double &op2);
public:
	Expression(string str);
	~Expression();
	//��ȡ������
	string getResult();
};


#endif