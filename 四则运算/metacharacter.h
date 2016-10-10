#ifndef METACHARACTER
#define METACHARACTER
#include <string>
#include <map>

struct Metacharacter {
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

const string ZERO = "0";
const string ONE = "1";
const string TWO = "2";
const string THREE = "3";
const string FOUR = "4";
const string FIVE = "5";
const string SIX = "6";
const string SEVEN = "7";
const string EIGHT = "8";
const string NINE = "9";
const string POINT = ".";
const string ADD = "+";
const string MINUS = "-";
const string MULTIPLY = "��";
const string DIVIDE = "��";
const string EQUAL = "=";
const string DEGREE = "��";
const string MOD_PERCENT = "%";
const string POW = "^";
const string EXTRACT_ROOT = "��";
const string FACTORIAL = "!";
const string SIN = "sin";
const string COS = "cos";
const string TAN = "tan";
const string ARCSIN = "arcsin";
const string ARCCOS = "arccos";
const string ARCTAN = "arctan";
const string LG = "lg";
const string LOG = "log";
const string LN = "ln";
const string LEFT_BRACKET = "(";
const string RIGHT_BRACKET = ")";

const map<string, Metacharacter> METACHARACTERS{
	/*
	* ����0-9��С����
	*/
	{ "0",		Metacharacter{ 0,0,0,0,0, "0" } },
	{ "1",		Metacharacter{ 0,0,0,0,0, "1" } },
	{ "2",		Metacharacter{ 0,0,0,0,0, "2" } },
	{ "3",		Metacharacter{ 0,0,0,0,0, "3" } },
	{ "4",		Metacharacter{ 0,0,0,0,0, "4" } },
	{ "5",		Metacharacter{ 0,0,0,0,0, "5" } },
	{ "6",		Metacharacter{ 0,0,0,0,0, "6" } },
	{ "7",		Metacharacter{ 0,0,0,0,0, "7" } },
	{ "8",		Metacharacter{ 0,0,0,0,0, "8" } },
	{ "9",		Metacharacter{ 0,0,0,0,0, "9" } },
	{ ".",		Metacharacter{ 0,0,0,0,0, "." } },

	/*
	* �Ӽ��˳�
	*/
	{ "+",		Metacharacter{ 1,1,1,2,2, "+" } },
	{ "-",		Metacharacter{ 1,1,1,2,2, "-" } },
	{ "*",		Metacharacter{ 1,2,2,2,2, "*" } },
	{ "/",		Metacharacter{ 1,2,2,2,2, "/" } },

	{ "%",		Metacharacter{ 1,2,2,2,2, "%" } },   //�����ٷֺ�
	{ "^",		Metacharacter{ 1,3,3,2,2, "^" } },   //�˷�
	{ "#",		Metacharacter{ 1,3,3,2,2, "#" } },   //����
	{ "!",		Metacharacter{ 1,4,4,1,3, "!" } },   //�ײ�
	{ "`",		Metacharacter{ 1,4,4,1,3, "`" } },   //��(�Ƕ�)

	{ "sin",	Metacharacter{ 1,11,11,1,1, "sin" } },   //���ң�Ĭ�ϻ��ȣ�
	{ "cos",	Metacharacter{ 1,11,11,1,1, "cos" } },   //����
	{ "tan",	Metacharacter{ 1,11,11,1,1, "tan" } },   //����
	{ "arcsin",	Metacharacter{ 1,11,11,1,1, "arcsin" } },    //������
	{ "arccos",	Metacharacter{ 1,11,11,1,1, "arccos" } },    //������
	{ "arctan",	Metacharacter{ 1,11,11,1,1, "arctan" } },    //������
	{ "lg",		Metacharacter{ 1,11,11,1,1, "lg" } },    //���ö�������10Ϊ��
	{ "log",	Metacharacter{ 1,11,11,1,1, "log" } },   //���ö�������10Ϊ��
	{ "ln",		Metacharacter{ 1,11,11,1,1, "ln" } },    //��Ȼ��������eΪ��

														 /*
														 * ���ţ�����δ����������ʽ�����ȼ�����5*(3+1}�ǺϷ���
														 */
	{ "(",		Metacharacter{ 2,103,-1,0,0, "(" } },
	{ "[",		Metacharacter{ 2,102,-1,0,0, "[" } },
	{ "{",		Metacharacter{ 2,101,-1,0,0, "{" } },
	{ ")",		Metacharacter{ 2,-1,103,0,0, ")" } },
	{ "]",		Metacharacter{ 2,-1,102,0,0, "]" } },
	{ "}",		Metacharacter{ 2,-1,101,0,0, "}" } },

	{ "$",		Metacharacter{ 3,-10,-10,0,0, "$" } },   //��������
};
#endif // METACHARACTER

