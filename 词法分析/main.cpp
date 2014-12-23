/*
 * 简单词法分析器
 * 作者：Coffee Cat
 * 时间：2014-11-23
 * No copyright, you can modified it freely
 * And it's better to tell me your changes
 * 注释有不规范之处，还请谅解
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

#define	BEGIN		1		// 关键字 begin
#define	END		2		// 关键字 end
#define	IF		3		// 关键字 if
#define	THEN		4		// 关键字 then
#define	ELSE		5		// 关键字 else
#define	ID		6		// 标识符
#define	INT		7		// 整型常数
#define	LT		8		// 关系运算符 <
#define	LE		9		// 关系运算符 <=
#define	EQ		10		// 关系运算符 =
#define	NE		11		// 关系运算符 <>
#define	GT		12		// 关系运算符 >
#define	GE		13		// 关系运算符 >=
#define	IS		14		// 赋值符 :=
#define	PL		15		// 算术运算符 +
#define	MI		16		// 算术运算符 -
#define	MU		17		// 算术运算符 *
#define	DI		18		// 算术运算符 /
#define	LPAREN		19		// 左括号 (
#define RPAREN		20		// 右括号 )

/*
 * 二元组表示：(单词种别，单词自身的值)
 * 约定如下：
 * （1）标识符	——（6, 单词自身的值，即标识符）
 * （2）整型常数——（7， 单词自身的值，即整数）
 * （3）其他	——（种别码，留空）
 * 注：暂时只支持整数
 */

int row = 1;					// 用来表示行号
char token[50];					// 用来依次存放一个单词词文中的各个字符
map<string, int> keywords;			// 关键字表，在初始化函数中初始化

/*
 * 函数 void init()
 * 作用：初始化词法分析器
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
 * 函数 int lookup(const char * token)
 * 参数：字符数组token
 * 作用：每调用一次，就以token中的字符串查保留字表
 * 返回值：若查到，就返回相应关键字的类别码，否则返回0
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
 * 函数 void report_error()
 * 参数：reason  出错原因的描述 
 * 作用：报告出错的行数
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
 * 函数 void outToFile(int num, const char * val)
 * 参数：num  为相应单词的类别码或其助记符
 * 参数：val  当所识别的单词为标识符和整数时，为token（即词文分别为字母数字串和数字串），对于其余种类的单词，均为空串
 * 作用：输出一个单词的内部表示至控制台标准输出
 * author: Coffee Cat
 */
void outToStdout(int num, const char * val)
{
	cout << "( " << num << " , " << val << " )" << endl;
}

/*
 * 函数 void out(int num, const char * val)
 * 参数：num  为相应单词的类别码或其助记符
 * 参数：val  当所识别的单词为标识符和整数时，为token（即词文分别为字母数字串和数字串），对于其余种类的单词，均为空串
 * 作用：输出一个单词的内部表示，在词法分析实验中输出至控制台标准输出，在语法分析实验中输出至内存，作为接口函数
 * author: Coffee Cat
 */
void out(int num, const char * val)
{
	outToStdout(num, val);
}

/*
 * 函数 void scanner(const string &line, string::size_type &index)
 * 参数：line  为待扫描的一行源代码
 * 参数：index 为当前扫描的字符的位置，即index的索引
 * 作用：进行扫描，对所读入的符号进行相应处理
 * author: Coffee Cat
 */
void scanner(const string &line, string::size_type &index)
{
	char ch;							// 存储当前字符
	int i;
	int c;
	if (index >= line.size())
		return;							// 保护措施，若已到行尾，则退出
	ch = line[index++];
	if (isalpha(ch))					// 关键字或标识符
	{
		i = 0;							// 跟踪token数组的下标，指向待存放的位置
		token[i] = ch;
		ch = line[index++];				// 读取下一个字符存入
		i++;
		while (isalnum(ch))
		{
			token[i] = ch;
			i++;
			ch = line[index++];			// 又是下一个
		}
		token[i] = '\0';				// 给token结尾
		index--;						// 回溯，因为当读入的字符不是字母或数字时，尽管循环终止了，index还是自增了
		if (c = lookup(token))
		{
			out(c, "");
		}
		else
		{
			out(ID, token);
		}
	}
	else if (isdigit(ch))				// 整数字面值
	{
		i = 0;							// 跟踪token数组的下标，指向待存放的位置
		token[i] = ch;
		ch = line[index++];				// 读取下一个字符存入
		i++;
		while (isdigit(ch))
		{
			token[i] = ch;
			i++;
			ch = line[index++];			// 又是下一个
		}
		if (isalpha(ch))				// 数字后面紧跟字母
		{
			report_error("数字后面跟随字母非法！");
		}
		token[i] = '\0';				// 给token结尾
		index--;						// 回溯，因为当读入的字符不是数字时，尽管循环终止了，index还是自增了
		out(INT, token);
	}
	else								// 运算符和其它字符的处理
	{
		switch (ch)
		{
		case '<':
			ch = line[index++];
			if (ch == '=')				// 关系运算符 <=
			{
				out(LE, "");
			}
			else if (ch == '>')			// 关系运算符 <>
			{
				out(NE, "");
			}
			else						// 关系运算符 <
			{
				index--;				// 回溯，多读了
				out(LT, "");
			}
			break;
		case '=':						// 关系运算符 =
			out(EQ, "");
			break;
		case '>':
			ch = line[index++];
			if (ch == '=')				// 关系运算符 >=
			{
				out(GE, "");
			}
			else						// 关系运算符 >
			{
				index--;				// 回溯，多读了
				out(GT, "");
			}
			break;
		case ':':
			ch = line[index++];
			if (ch == '=')				// 赋值符 :=
			{
				out(IS, "");
			}
			else
			{
				index--;
				report_error("冒号后需跟等号组成赋值符，否则非法！");
			}
			break;
		case '+':						// 算术运算符 +
			out(PL, "");
			break;
		case '-':						// 算术运算符 -
			out(MI, "");
			break;
		case '*':						// 算术运算符 *
			out(MU, "");
			break;
		case '/':						// 算术运算符 /
			out(DI, "");
			break;
		case '(':
			out(LPAREN, "");
			break;
		case ')':
			out(RPAREN, "");
			break;
		default:						// 其它字符
			report_error("非法字符！");
			break;
		}								// switch
	}									// else
}

int main()
{
	string filename;
	cout << "请输入文件名： ";
	getline(cin, filename);
	ifstream infile(filename.c_str());
	if (!infile)
	{
		cerr << "Error: unable to open input file: " << filename << endl;
		return -1;
	}
	init();								//在此处初始化词法分析器
	string line;						// 用于存放每一行的代码
	while (getline(infile, line))		// 一次读取一行
	{
		string::size_type index = 0;	// 用于表示当前读取字符串的位置索引
		while (index != line.size())
		{
			while (isspace(line[index++]))
				;						// 跳过空白字符
			index--;					// 回溯，因为在非空白字符处判断时，即使因为是非空白字符而终止循环，index还是自增了
			scanner(line, index);		// index传引用，在scanner中更改
		}

		row++;
	}

	infile.close();
	return 0;
}