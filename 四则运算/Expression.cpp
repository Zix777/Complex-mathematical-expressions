#include "Expression.h"
#include <exception>
#include <regex>
#include <cctype>
#include <cmath>
#include <iostream>
using namespace std;



Expression::Expression(string str, int precision)
{
	raw_exp = str;
	mathEx.set_eps(precision);
}

Expression::~Expression()
{
}

/*
* �Ա��ʽ���г����Ϸ��Լ�飬�����ַ��Լ��ַ���ɵ����㵥Ԫ�Ƿ�Ϸ�
*/
bool Expression::simpleCheck()
{
	string temp;
	bool getWord = false;   //��ȡ��������
	int isAlpha = 0;    //��ǰ�ַ��Ƿ�Ϊ��ĸ
	for (auto &i : raw_exp)
	{
		isAlpha = isalpha(i);   //�жϵ�ǰ�ַ��Ƿ�Ϊ��ĸ
		if (getWord)
		{
			/*
			* ���ڲ����ʹ��ɹ����У����������ĸ
			*/
			if (isAlpha)
			{
				temp += i;
				continue;   //��������
			}
		}
		else
		{
			/*
			* ��ȡ��һ����ĸ�����������ʹ��ɹ���
			*/
			if (isAlpha)
			{
				getWord = true;
				temp += i;
				continue;   //��������
			}
			else
				temp += i;  //��ȡ������ĸ�������ʹ��ɹ��̽���
		}

		/*
		* �����ȡ���Ĳ����ʲ���Ԫ�ַ����л�Ϊ���������׳��쳣
		*/
		if (METACHARACTERS.find(temp) == METACHARACTERS.end() || temp == "$")
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);

		/*
		* ���ò����ʹ��ɹ��̱�ʶ
		*/
		if (getWord)
		{
			getWord = false;
		}
		temp = "";  //���
	}

	if (getWord)
		throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
	return true;
}

/*
* �ʷ����������ֳɴ�
*/
bool Expression::split()
{
	string::size_type i = 0;
	string::size_type temp = 0;
	while (i<raw_exp.size())
	{
		string str_temp;
		str_temp += raw_exp[i];
		bool getPoint = false;
		if (isdigit(raw_exp[i]))    //��ȡ����
		{
			temp = i;
			do
			{
				if (raw_exp[i] == '.')
					getPoint = true;
				if (++i >= raw_exp.size())
					break;
			} while (isdigit(raw_exp[i]) || ((!getPoint) && raw_exp[i] == '.'));
			exp.push_back(Metacharacter{ 0,0,0,0,0, raw_exp.substr(temp, i - temp) });
		}
		else if (raw_exp[i] == '.') //��ȡ����������֮���С���㣬�׳��쳣
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + ".");
		else if (METACHARACTERS.find(str_temp) != METACHARACTERS.end()) //��ȡ��������
		{
			exp.push_back(METACHARACTERS.at(str_temp));
			++i;
		}
		else if (isalpha(raw_exp[i]))   //��ȡ��������
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isalpha(raw_exp[i]));
			str_temp = raw_exp.substr(temp, i - temp);
			exp.push_back(METACHARACTERS.at(str_temp));
		}
	}
	return true;
}

/*
* ���Ŵ���
*/
void Expression::negativeOperatorPreprocessing()
{
	for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "-")
		{
			//��������ڱ��ʽ��λ���ڸ���ǰ�������0
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTERS.at("0"));
			}
			else
			{
				//�������ǰΪ���ţ��ڸ���ǰ�������0
				--i;
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTERS.at("0"));
				}
				++i;
			}
		}
	}
}

//ΪĬ��ʡ�Ը�ָ��2�Ŀ�ƽ�������ǰ����ϸ�ָ��2
void Expression::sqrtOperatorPreprocessing()
{
	for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "#")
		{
			//��������ڱ��ʽ��һ��λ��
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTERS.at("2"));
			}
			else
			{
				--i;
				//�������ǰΪ�����ţ�ֱ����Ӹ�ָ��2
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTERS.at("2"));
					++i;
				}
				//�������ǰΪΪǰ��������������������˵������Ϊ��ƽ�����㣬Ϊ����Ӹ�ָ��2���������
				else if ((*i).position == 1 || (*i).position == 2)
				{
					//�ڸ���ǰ��ӡ���2��
					++i;
					i = exp.insert(i, { METACHARACTERS.at("("),METACHARACTERS.at("2") }); //(2#4
					++i, ++i, ++i;
					//������ź�Ϊ���֣�ֱ�������ֺ���ӡ�)��
					if ((*i).type == 0)
					{
						++i;
						i = exp.insert(i, METACHARACTERS.at(")"));
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
								exp.insert(j, METACHARACTERS.at(")"));
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
	for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "%")
		{
			++i;
			//���%��Ϊ���ʽβ,���û���������,��%Ϊ�ٷֺ�����,Ϊ���������,����ת��Ϊ����100��������������
			if (i == exp.end() || (*i).position == 2 || (*i).position == 3)
			{
				i = exp.insert(i, METACHARACTERS.at(")"));  //����������
				i = exp.insert(i, Metacharacter{ 0,0,0,0,0, "100" });   //���ϳ���100
				--i;
				(*i).e = "/";   //����%��/������������������һ��,ֱ�ӽ�%�޸�Ϊ/
				int interval = 0;   //��¼��ǰ�ƶ����
									/*
									* �ҵ�%ǰ��һ��Ϊǰ��,�������������ʽ�׵�λ��
									*/
				while ((--i)->position != 1 && i->position != 2 && i != exp.begin())
				{
					++interval;
				}
				//���ҵ���λ��֮�����������
				++i;
				i = exp.insert(i, METACHARACTERS.at("("));
				while (interval--)  //����ԭλ��
				{
					++i;
				}
				++i;
			}
		}
	}
}

/**
* Ϊ�˱�֤������ȼ���,���估ǰ������ּ�������
*/
void Expression::degreeOperatorPreprocessing()
{
	//��԰ٷֺŴ�������,ֻ������Ժ�һ�������ʽ����ж�,���޶�����,ֻ��ֱ�Ӽ����ż���
	for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "`")
		{
			++i;
			i = exp.insert(i, METACHARACTERS.at(")"));
			int interval = 0;
			while ((--i)->position != 1 && i->position != 2 && i != exp.begin())
			{
				++interval;
			}
			++i;
			i = exp.insert(i, METACHARACTERS.at("("));
			while (interval--)
			{
				++i;
			}
			++i;
		}
	}
}

//����/�в���ת��Ϊ��Ӧ��С����
void Expression::bracketPreprocessing()
{
	for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		//ת��������
		if ((*i).out_priority == 101 || (*i).out_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTERS.at("("));
		}
		//ת��������
		else if ((*i).in_priority == 101 || (*i).in_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTERS.at(")"));
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
	degreeOperatorPreprocessing();
}

void Expression::operation()
{
	if (op.top().operand == 1)  //��ΪһԪ�����
	{
		double op1; if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1);
	}
	else    //��Ϊ��Ԫ�����
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
		exp.push_front(METACHARACTERS.at("$"));
		for (auto i : exp)
		{
			//�����ǰԪ��Ϊ��������ѹ�������ջ
			if (i.type == 0)
				number.push(stod(i.e));
			//�����ǰԪ��Ϊ��������Ƚ����������ջ��Ԫ�ص����ȼ�
			else if (i.type == 1)
			{
				/*
				* ���С��ջ����������ȼ���
				* ���ϳ�ջջ�������ֱ��ջ����������ȼ�С�ڵ�ǰ��������ȼ���
				* �����ζԳ�ջ���������������
				* Ȼ����ջ��ǰ�����
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
				//�����ǰ����Ϊ�����ţ���ջ
				if (i.out_priority > 0)
				{
					op.push(i);
					//lastBracket = i;
				}
				//�����ǰ����Ϊ�����ţ���ջ�����ջֱ��������һ��������
				else if (i.out_priority < 0)
				{
					//					//һ�������������ݣ��׳������쳣
					//					if (op.top().out_priority>100)
					//						throw runtime_error(ExpressionError::NEEDLESS_BARCKET_ERROR);

					while (op.top().type != 2)
					{
						operation();
					}

					op.pop();
					if (op.empty())
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
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

		if (number.size() > 1)
		{
			throw runtime_error(ExpressionError::MISSING_OPERATOR_ERROR);
		}
	}
	catch (...) {
		throw;
	}
}

//��Ŀ���������
void Expression::calc(Metacharacter mc, double & op1)
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
		else if (mc.e == "`")
			number.push(mathEx.op_degree_to_radian(op1));
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
void Expression::calc(Metacharacter mc, double & op1, double & op2)
{
	if (number.empty()) //����ջΪ��,ȱ�ٲ�����2
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op2 = number.top();
		number.pop();
	}
	if (number.empty()) //����ջΪ��,ȱ�ٲ�����1
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

/*
* ����
*/
string Expression::getResult()
{
	try {
		simpleCheck();  //�ַ��Ϸ��Լ��
		split();    //���ֳɴ�
		preprocessing();    //���������Ԥ����
		transToPostfix();   //ת��Ϊ�沨��ʽ������
							//        for (auto &i : exp)
							//        {
							//            cout << i.e << ' ';
							//        }
	}
	catch (runtime_error &) {
		throw;
	}
	result = number.top();  //����ջ�����һ������Ϊ���
	return to_string(mathEx.getRound(result));
}


