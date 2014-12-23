/*
 * �򵥴ʷ�������
 * ���ߣ�Coffee Cat
 * ʱ�䣺2014-11-23
 * No copyright, you can modified it freely
 * And it's better to tell me your changes
 * ע���в��淶֮���������½�
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

#define	BEGIN		1		// �ؼ��� begin
#define	END		2		// �ؼ��� end
#define	IF		3		// �ؼ��� if
#define	THEN		4		// �ؼ��� then
#define	ELSE		5		// �ؼ��� else
#define	ID		6		// ��ʶ��
#define	INT		7		// ���ͳ���
#define	LT		8		// ��ϵ����� <
#define	LE		9		// ��ϵ����� <=
#define	EQ		10		// ��ϵ����� =
#define	NE		11		// ��ϵ����� <>
#define	GT		12		// ��ϵ����� >
#define	GE		13		// ��ϵ����� >=
#define	IS		14		// ��ֵ�� :=
#define	PL		15		// ��������� +
#define	MI		16		// ��������� -
#define	MU		17		// ��������� *
#define	DI		18		// ��������� /
#define	LPAREN		19		// ������ (
#define RPAREN		20		// ������ )

/*
 * ��Ԫ���ʾ��(�����ֱ𣬵��������ֵ)
 * Լ�����£�
 * ��1����ʶ��	������6, ���������ֵ������ʶ����
 * ��2�����ͳ���������7�� ���������ֵ����������
 * ��3������	�������ֱ��룬���գ�
 * ע����ʱֻ֧������
 */

int row = 1;					// ������ʾ�к�
char token[50];					// �������δ��һ�����ʴ����еĸ����ַ�
map<string, int> keywords;			// �ؼ��ֱ��ڳ�ʼ�������г�ʼ��

/*
 * ���� void init()
 * ���ã���ʼ���ʷ�������
 * author: Coffee Cat
 */
void init()
{
	keywords["begin"] = BEGIN;
	keywords["end"]	  = END;
	keywords["if"]	  = IF;
	keywords["then"]  = THEN;
	keywords["else"]  = ELSE;
}

/*
 * ���� int lookup(const char * token)
 * �������ַ�����token
 * ���ã�ÿ����һ�Σ�����token�е��ַ����鱣���ֱ�
 * ����ֵ�����鵽���ͷ�����Ӧ�ؼ��ֵ�����룬���򷵻�0
 * author: Coffee Cat
 */
int lookup(const char * token)
{
	string word(token);
	int result;
	if (keywords.count(word))
	{
		result = keywords[word];
	}
	else
	{
		result = 0;
	}
	return result;
}

/*
 * ���� void report_error()
 * ������reason  ����ԭ������� 
 * ���ã�������������
 * author: Coffee Cat
 */
void report_error(string reason = "")
{
	if (reason != "")
		cerr << "Error in line " << row << " : " << reason << endl;
	else
		cerr << "Error in line " << row << endl;
}

/*
 * ���� void outToFile(int num, const char * val)
 * ������num  Ϊ��Ӧ���ʵ������������Ƿ�
 * ������val  ����ʶ��ĵ���Ϊ��ʶ��������ʱ��Ϊtoken�������ķֱ�Ϊ��ĸ���ִ������ִ�����������������ĵ��ʣ���Ϊ�մ�
 * ���ã����һ�����ʵ��ڲ���ʾ������̨��׼���
 * author: Coffee Cat
 */
void outToStdout(int num, const char * val)
{
	cout << "( " << num << " , " << val << " )" << endl;
}

/*
 * ���� void out(int num, const char * val)
 * ������num  Ϊ��Ӧ���ʵ������������Ƿ�
 * ������val  ����ʶ��ĵ���Ϊ��ʶ��������ʱ��Ϊtoken�������ķֱ�Ϊ��ĸ���ִ������ִ�����������������ĵ��ʣ���Ϊ�մ�
 * ���ã����һ�����ʵ��ڲ���ʾ���ڴʷ�����ʵ�������������̨��׼��������﷨����ʵ����������ڴ棬��Ϊ�ӿں���
 * author: Coffee Cat
 */
void out(int num, const char * val)
{
	outToStdout(num, val);
}

/*
 * ���� void scanner(const string &line, string::size_type &index)
 * ������line  Ϊ��ɨ���һ��Դ����
 * ������index Ϊ��ǰɨ����ַ���λ�ã���index������
 * ���ã�����ɨ�裬��������ķ��Ž�����Ӧ����
 * author: Coffee Cat
 */
void scanner(const string &line, string::size_type &index)
{
	char ch;							// �洢��ǰ�ַ�
	int i;
	int c;
	if (index >= line.size())
		return;							// ������ʩ�����ѵ���β�����˳�
	ch = line[index++];
	if (isalpha(ch))					// �ؼ��ֻ��ʶ��
	{
		i = 0;							// ����token������±ָ꣬�����ŵ�λ��
		token[i] = ch;
		ch = line[index++];				// ��ȡ��һ���ַ�����
		i++;
		while (isalnum(ch))
		{
			token[i] = ch;
			i++;
			ch = line[index++];			// ������һ��
		}
		token[i] = '\0';				// ��token��β
		index--;						// ���ݣ���Ϊ��������ַ�������ĸ������ʱ������ѭ����ֹ�ˣ�index����������
		if (c = lookup(token))
		{
			out(c, "");
		}
		else
		{
			out(ID, token);
		}
	}
	else if (isdigit(ch))				// ��������ֵ
	{
		i = 0;							// ����token������±ָ꣬�����ŵ�λ��
		token[i] = ch;
		ch = line[index++];				// ��ȡ��һ���ַ�����
		i++;
		while (isdigit(ch))
		{
			token[i] = ch;
			i++;
			ch = line[index++];			// ������һ��
		}
		if (isalpha(ch))				// ���ֺ��������ĸ
		{
			report_error("���ֺ��������ĸ�Ƿ���");
		}
		token[i] = '\0';				// ��token��β
		index--;						// ���ݣ���Ϊ��������ַ���������ʱ������ѭ����ֹ�ˣ�index����������
		out(INT, token);
	}
	else								// ������������ַ��Ĵ���
	{
		switch (ch)
		{
		case '<':
			ch = line[index++];
			if (ch == '=')				// ��ϵ����� <=
			{
				out(LE, "");
			}
			else if (ch == '>')			// ��ϵ����� <>
			{
				out(NE, "");
			}
			else						// ��ϵ����� <
			{
				index--;				// ���ݣ������
				out(LT, "");
			}
			break;
		case '=':						// ��ϵ����� =
			out(EQ, "");
			break;
		case '>':
			ch = line[index++];
			if (ch == '=')				// ��ϵ����� >=
			{
				out(GE, "");
			}
			else						// ��ϵ����� >
			{
				index--;				// ���ݣ������
				out(GT, "");
			}
			break;
		case ':':
			ch = line[index++];
			if (ch == '=')				// ��ֵ�� :=
			{
				out(IS, "");
			}
			else
			{
				index--;
				report_error("ð�ź�����Ⱥ���ɸ�ֵ��������Ƿ���");
			}
			break;
		case '+':						// ��������� +
			out(PL, "");
			break;
		case '-':						// ��������� -
			out(MI, "");
			break;
		case '*':						// ��������� *
			out(MU, "");
			break;
		case '/':						// ��������� /
			out(DI, "");
			break;
		case '(':
			out(LPAREN, "");
			break;
		case ')':
			out(RPAREN, "");
			break;
		default:						// �����ַ�
			report_error("�Ƿ��ַ���");
			break;
		}								// switch
	}									// else
}

int main()
{
	string filename;
	cout << "�������ļ����� ";
	getline(cin, filename);
	ifstream infile(filename.c_str());
	if (!infile)
	{
		cerr << "Error: unable to open input file: " << filename << endl;
		return -1;
	}
	init();								//�ڴ˴���ʼ���ʷ�������
	string line;						// ���ڴ��ÿһ�еĴ���
	while (getline(infile, line))		// һ�ζ�ȡһ��
	{
		string::size_type index = 0;	// ���ڱ�ʾ��ǰ��ȡ�ַ�����λ������
		while (index != line.size())
		{
			while (isspace(line[index++]))
				;						// �����հ��ַ�
			index--;					// ���ݣ���Ϊ�ڷǿհ��ַ����ж�ʱ����ʹ��Ϊ�Ƿǿհ��ַ�����ֹѭ����index����������
			scanner(line, index);		// index�����ã���scanner�и���
		}

		row++;
	}

	infile.close();
	return 0;
}