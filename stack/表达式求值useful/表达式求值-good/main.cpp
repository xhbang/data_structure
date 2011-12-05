#include <iostream>
#include <string.h>
#include "stack.h"
using namespace std;

int compare(char a,char b);

double Operandsolve();

int main()
{
	double result;
	result = Operandsolve();
	cout << "The result is:" << result << endl;
	return 0;
}

int compare(char a,char b)
{ //1��ʾջ�����ȼ����ڴ���ջ��Ԫ��
	if(a == '(' && b == ')') 
		return 0;
	else if
		((a == '+' && b == '*') || (a == '+' && b == '/')
		|| (a == '-' && b == '*') || (a == '-' && b == '/')
		|| (a != ')' && b == '(') || (a == '(' && b != ')'))
		return -1;
	else return 1;
}

double Operandsolve()
{
	stack<double> OPND;
	stack<char> OPTR;
	OPND.InitStack();
	OPTR.InitStack();
	char ch[8];
	char a,b;
	double value;
	cout << "�������������ʽ(����:2 + 3 * ( 5 - 8 / 4 ) #," << endl;
	cout << "������Ϻ���ĩβ����#,����ÿ����Ϣ���ӿո�):" << endl;
	cin >> ch;
	while(strcmp(ch,"#") != 0 || !OPTR.StackEmpty())
	{
		if(strcmp(ch,"+") != 0 && strcmp(ch,"-") != 0
			&& strcmp(ch,"*") != 0 && strcmp(ch,"/") != 0
			&& strcmp(ch,"(") != 0 && strcmp(ch,")") != 0
			&& strcmp(ch,"#") != 0)
		{
			value = atof(ch);
			OPND.Push(value);
			cin >> ch;
		}
		else if(OPTR.StackEmpty())
		{
			a = ch[0];
			OPTR.Push(a);
			cin >> ch;
		}
		else
		{
			a = ch[0];
			if(OPTR.GetTop(b),compare(b,a) < 0)
			{
				OPTR.Push(a);
				cin >> ch;
			}
			else if(OPTR.GetTop(b),compare(b,a) > 0)
			{
				OPTR.Pop(b);
				double pre,next;
				OPND.Pop(next);
				OPND.Pop(pre);
				switch(b)
				{
				case '+': OPND.Push(pre+next);break;
				case '-': OPND.Push(pre-next);break;
				case '*': OPND.Push(pre*next);break;
				case '/': OPND.Push(pre/next);break;
				}
			}
			else
			{
				OPTR.Pop(b);
				cin >> ch;
			}
		}
	}

	OPND.Pop(value);
	OPND.DestroyStack();
	OPTR.DestroyStack();
	return value;
}