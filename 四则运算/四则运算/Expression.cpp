#include "Expression.h"
#include <exception>
#include <stdexcept>
#include <regex>
#include <cctype>
#include <cmath>
#include <iostream>
using namespace std;

const map<string, metacharacter> Expression::METACHARACTER{
	{ "0",		metacharacter{ 0,0,0,0,0, "0" }},
	{ "1",		metacharacter{ 0,0,0,0,0, "1" }},
	{ "2",		metacharacter{ 0,0,0,0,0, "2" }},
	{ "3",		metacharacter{ 0,0,0,0,0, "3" }},
	{ "4",		metacharacter{ 0,0,0,0,0, "4" }},
	{ "5",		metacharacter{ 0,0,0,0,0, "5" }},
	{ "6",		metacharacter{ 0,0,0,0,0, "6" }},
	{ "7",		metacharacter{ 0,0,0,0,0, "7" }},
	{ "8",		metacharacter{ 0,0,0,0,0, "8" }},
	{ "9",		metacharacter{ 0,0,0,0,0, "9" }},
	{ ".",		metacharacter{ 0,0,0,0,0, "." }},

	{ "+",		metacharacter{ 1,1,1,2,2, "+" }},
	{ "-",		metacharacter{ 1,1,1,2,2, "-" }},
	{ "*",		metacharacter{ 1,2,2,2,2, "*" }},
	{ "/",		metacharacter{ 1,2,2,2,2, "/" }},
	{ "%",		metacharacter{ 1,2,2,2,2, "%" }},
	{ "^",		metacharacter{ 1,3,3,2,2, "^" }},
	{ "#",		metacharacter{ 1,3,3,2,2, "#" }},
	{ "!",		metacharacter{ 1,4,4,1,3, "!" }},

	{ "sin",	metacharacter{ 1,11,11,1,1, "sin" }},
	{ "cos",	metacharacter{ 1,11,11,1,1, "cos" }},
	{ "tan",	metacharacter{ 1,11,11,1,1, "tan" }},
	{ "arcsin",	metacharacter{ 1,11,11,1,1, "arcsin" }},
	{ "arccos",	metacharacter{ 1,11,11,1,1, "arccos" }},
	{ "arctan",	metacharacter{ 1,11,11,1,1, "arctan" }},
	{ "lg",		metacharacter{ 1,11,11,1,1, "lg" }},
	{ "log",	metacharacter{ 1,11,11,1,1, "log" }},
	{ "ln",		metacharacter{ 1,11,11,1,1, "ln" }},

	{ "(",		metacharacter{ 2,103,-1,0,0, "(" }},
	{ "[",		metacharacter{ 2,102,-1,0,0, "[" }},
	{ "{",		metacharacter{ 2,101,-1,0,0, "{" }},
	{ ")",		metacharacter{ 2,-1,103,0,0, ")" }},
	{ "]",		metacharacter{ 2,-1,102,0,0, "]" }},
	{ "}",		metacharacter{ 2,-1,101,0,0, "}" }},

	{ "$",		metacharacter{ 3,-10,-10,0,0, "$" }},
};

Expression::Expression(string str)
{
	raw_exp = str;
}

Expression::~Expression()
{
}

bool Expression::simpleCheck()
{
	string temp;
	bool getWord = false;
	int isAlpha = 0;
	for (auto &i : raw_exp)
	{
		isAlpha = isalpha(i);
		if (getWord)
		{
			if (isAlpha)
			{
				temp += i;
				continue;
			}
		}
		else
		{
			if (isAlpha)
			{
				getWord = true;
				temp += i;
				continue;
			}
			else
				temp += i;
		}
		if (getWord)
		{
			if (METACHARACTER.find(temp) == METACHARACTER.end() || temp == "$")
				throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);
			getWord = false;
		}

		if (METACHARACTER.find(temp) == METACHARACTER.end() || temp == "$")
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);
		temp = "";
	}

	if (getWord)
		throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
	return true;
}

bool Expression::split()
{
	string::size_type i = 0;
	string::size_type temp = 0;
	while (i<raw_exp.size())
	{
		string str_temp;
		str_temp += raw_exp[i];
		if (isdigit(raw_exp[i]))
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isdigit(raw_exp[i]) || raw_exp[i] == '.');
			exp.push_back(metacharacter{ 0,0,0,0,0, raw_exp.substr(temp, i - temp) });
		}
		else if (raw_exp[i] == '.')
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + ".");
		else if (METACHARACTER.find(str_temp)!=METACHARACTER.end())
		{
			exp.push_back(METACHARACTER.at(str_temp));
			++i;
		}
		else if (isalpha(raw_exp[i]))
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isalpha(raw_exp[i]));
			str_temp = raw_exp.substr(temp, i - temp);
			exp.push_back(METACHARACTER.at(str_temp));
		}
	}
	return true;
}

void Expression::negativeOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "-")
		{
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTER.at("0"));
			}
			else
			{
				--i;
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTER.at("0"));
				}
				++i;
			}
		}
	}
}

//ΪĬ��ʡ�Ը�ָ��2�Ŀ�ƽ�������ǰ����ϸ�ָ��2
void Expression::sqrtOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "#")
		{
			//��������ڱ��ʽ��һ��λ��
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTER.at("2"));
			}
			else
			{
				--i;
				//�������ǰΪ�����ţ�ֱ����Ӹ�ָ��2
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTER.at("2"));
					++i;
				}
				//�������ǰΪΪǰ��������������������˵������Ϊ��ƽ�����㣬Ϊ����Ӹ�ָ��2���������
				else if ((*i).position == 1 || (*i).position == 2)
				{
					//�ڸ���ǰ��ӡ���2��
					++i;
					i = exp.insert(i, { METACHARACTER.at("("),METACHARACTER.at("2") }); //(2#4
					++i, ++i, ++i;
					//������ź�Ϊ���֣�ֱ�������ֺ���ӡ�)��
					if ((*i).type == 0)
					{
						++i;
						i = exp.insert(i, METACHARACTER.at(")"));
					}
					//������ź�Ϊ�����ţ����Ҷ�Ӧ�������Ų��������ӡ�)��
					else if ((*i).type == 2)
					{
						int bracketCnt = 1;
						for (auto j = ++i; j != exp.end(); ++j)
						{
							if ((*j).out_priority > 100)
								++bracketCnt;
							else if ((*j).in_priority > 100)
								--bracketCnt;

							if (bracketCnt == 0)
							{
								++j;
								exp.insert(j, METACHARACTER.at(")"));
								break;
							}
						}
						--i;
						//������ź����������������ȣ��׳������쳣
						if (bracketCnt != 0)
							throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
					}
					//������ź�Ϊ������������ţ��׳��������쳣
					else if ((*i).type == 1 || (*i).out_priority > 100)
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
					//�����쳣
					else
						throw runtime_error(ExpressionError::UNKNOWN_ERROR);
				}
				else
					++i;
			}
		}
	}
}

//�������Ķ�%�����жϣ��������Ϊ���ʽβ�����úͺ������������%Ϊ�ٷֺŲ���������Ϊģ����
void Expression::percentOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "%")
		{
			++i;
			if (i == exp.end() || (*i).position == 2 || (*i).position == 3)
			{
				i = exp.insert(i, metacharacter{ 0,0,0,0,0, "100" });
				--i;
				(*i).e = "/";
			}
		}
	}
}

//����/�в���ת��Ϊ��Ӧ��С����
void Expression::bracketPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		//ת��������
		if ((*i).out_priority ==101 || (*i).out_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTER.at("("));
		}
		//ת��������
		else if ((*i).in_priority == 101 || (*i).in_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTER.at(")"));
		}
	}
}

//�Էָ��ı��ʽ����Ԥ�������ڽ������Ĳ���
void Expression::preprocessing()
{
	negativeOperatorPreprocessing();
	sqrtOperatorPreprocessing();
	percentOperatorPreprocessing();
	bracketPreprocessing();
}

void Expression::operation()
{
	if (op.top().operand == 1)
	{
		double op1; if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1);
	}
	else
	{
		double op1, op2;
		if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1, op2);
	}
	op.pop();
}


void Expression::transToPostfix()
{
	try {
		//metacharacter lastBracket;
		exp.push_front(METACHARACTER.at("$"));
		//exp.push_back(elementOfExpression{ "$",-2 });
		for (auto i : exp)
		{
			//�����ǰԪ��Ϊ��������ѹ�������ջ
			if (i.type == 0)
				number.push(stod(i.e));
			//�����ǰԪ��Ϊ��������Ƚ����������ջ��Ԫ�ص����ȼ�
			else if (i.type == 1)
			{
				/*���С��ջ����������ȼ���
				 *���ϳ�ջջ�������ֱ��ջ����������ȼ�С�ڵ�ǰ��������ȼ���
				 *�����ζԳ�ջ���������������
				 *Ȼ����ջ��ǰ�����
				 */
				if (i.out_priority <= op.top().in_priority)
				{
					do
					{
						operation();
					} while (i.out_priority <= op.top().in_priority);
				}
				op.push(i);
			}
			//�����ǰ�����Ϊ����
			else if (i.type == 2)
			{
				/*����Ǳ��ʽ�ĵ�һ�����ţ����䱣����lastBracket
				if (lastBracket.e == "")
				{
					op.push(i);
					lastBracket = i;
					continue;
				}*/

				//�����ǰ����Ϊ�����ţ���ջ
				if (i.out_priority > 0)
				{
					op.push(i);
					//lastBracket = i;
				}
				//�����ǰ����Ϊ�����ţ���ջ�����ջֱ��������һ��������
				else if (i.out_priority < 0)
				{
					//һ�������������ݣ��׳������쳣
					if (op.top().out_priority>100)
						throw runtime_error(ExpressionError::NEEDLESS_BARCKET_ERROR);

					do
					{
						operation();
					}while (op.top().type != 2);

					op.pop();
					if (op.empty())
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
					//��ͬ���͵�����ƥ����
					/*else
					{
						if (op.top().in_priority != i.out_priority)
						{
							throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
						}
						else
						{
							op.pop();
						}
					}*/
				}
			}
			//���ʽ��Ե��ʶ��$ֱ��ѹ�������ջ
			else if (i.type == 3)
				op.push(i);
		}

		//�������ջʣ�����������γ�ջ����������
		while (op.size() > 1)
		{
			operation();
		}
	}
	catch (...) {
		throw;
	}
}

//��Ŀ���������
void Expression::calc(metacharacter mc, double & op1)
{
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op1 = number.top();
		number.pop();
	}
	try {
		if (mc.e == "!")
			number.push(mathEx.op_factorial(op1));
		else if (mc.e == "sin")
			number.push(mathEx.op_sin(op1));
		else if (mc.e == "cos")
			number.push(mathEx.op_cos(op1));
		else if (mc.e == "tan")
			number.push(mathEx.op_tan(op1));
		else if (mc.e == "arcsin")
			number.push(mathEx.op_arcsin(op1));
		else if (mc.e == "arccos")
			number.push(mathEx.op_arccos(op1));
		else if (mc.e == "arctan")
			number.push(mathEx.op_arctan(op1));
		else if (mc.e == "log" || mc.e == "lg")
			number.push(mathEx.op_lg(op1));
		else if (mc.e == "ln")
			number.push(mathEx.op_ln(op1));
		else
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + mc.e);
	}
	catch (runtime_error) {
		throw;
	}

}

//˫Ŀ���������
void Expression::calc(metacharacter mc, double & op1, double & op2)
{
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op2 = number.top();
		number.pop();
	}
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op1 = number.top();
		number.pop();
	}
	try {
		if (mc.e == "+")
			number.push(mathEx.op_add(op1, op2));
		else if (mc.e == "-")
			number.push(mathEx.op_subtract(op1, op2));
		else if (mc.e == "*")
			number.push(mathEx.op_multiply(op1, op2));
		else if (mc.e == "/")
			number.push(mathEx.op_divide(op1, op2));
		else if (mc.e == "^")
			number.push(mathEx.op_pow(op1, op2));
		else if (mc.e == "%")
			number.push(mathEx.op_mod(op1, op2));
		else if (mc.e == "#")
			number.push(mathEx.op_extract_root(op1, op2));
		else
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + mc.e);
	}
	catch (runtime_error) {
		throw;
	}
}

string Expression::getResult()
{
	try {
		simpleCheck();
		split();
		preprocessing();
		transToPostfix();
		/*for (auto &i : exp)
		{
			cout << i.e << ' ';
		}*/
	} catch (runtime_error &){
		/*for (auto &i : exp)
		{
			cout << i.e << ' ';
		}*/
		throw;
	}
	result = number.top();
	return to_string(result);
}


