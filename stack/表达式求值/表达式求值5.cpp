/* 此程序的功能是求出用户输入的整形表达式的值20-10-07 17:43*/
/*输入的表达式请用#结尾，比如：2+3+5，应输入：2+3+5#。*/
#include <stdio.h>
#include <stdlib.h>
#define   MAXSIZE 16

typedef struct{
	int data[MAXSIZE];
	int top;
	int base;
}seqstack;   /* 顺序栈的定义*/

/*以下为函数声明*/
void InitStack(seqstack *);        
int Empty(seqstack *);
void Push(seqstack *, int );
int Pop(seqstack *);
int GetTop(seqstack *);
int Operate(int ,char ,int );
char Proceed(char ,char );
int In(char );
int EvalExpres(void);
/* 定义两个栈分别存放运算符和操作数*/
seqstack StackR,StackD;
/*主函数*/
int main()
{
	int v;
	char ch;
	while(1)
	{
		printf("@@@@@@@@本程序的功能为：用顺序栈实现整型算术表达式的求值@@@@@@@@\n");
		v = EvalExpres();        
		printf("The result is:%d",v);
		/*以下为程序控制*/        
		printf("\nInput 'q' to quit and ENTER run again:");
		do{  
			scanf("%c",&ch);      
			if(ch == 'q' || ch == 'Q')
				exit(0);
		}while(ch!='\n');
		system("cls");
	}
	return 0;
}

void InitStack(seqstack *s)
{     s->top = 0;
s->base = 0;
}   /* 初始化栈*/


int Empty(seqstack *s)
{   if(s->top == s->base)
return 1;
else
return 0;
}    /* 判断栈是否为空*/


void Push(seqstack *s, int x)
{    
	if(s->top == MAXSIZE)
	{    printf("OVER FLOW!\n");
	exit(0);
	}
	else
	{    s->data[s->top] = x;
	s->top++;
	}    
}    /* 进栈 */

int Pop(seqstack *s)
{    int e;
		if(Empty(s))
		{   printf("Under flow!\n");
		return 0;
		}   /* 下溢*/
		else
		{   s->top--;
		e = s->data[s->top];
		return e;
		}
} /* 出栈*/

int GetTop(seqstack *s)    /*取栈顶元素*/
{  
	if(Empty(s))
	{   printf("Under flow!\n");
	return 0;
	}
	else
		return s->data[s->top-1];      
}

int EvalExpres(void)    /* 表达式求解函数*/
{
	int a,b,i=0,s=0;
	char c[80],r;
	InitStack(&StackR);
	Push(&StackR,'#');
	InitStack(&StackD);
	printf(" 请输入表达式并以‘#’结束：");
	gets(c);
	while(c[i]!='#' || GetTop(&StackR)!='#')
	{      
		if(!In(c[i]))   /* 判断读入的字符不是运算符 是则进栈*/
		{ if(c[i] >= '0' && c[i] <= '9')
		{
			s += c[i]-'0';      
			while(!In(c[++i]))    /*此处实现的功能为当输入的数字为多位数时*/
			{ s*=10;
			s += c[i]-'0';
			}
			Push(&StackD,s+'0');
			s = 0;
		}
		else
		{
			printf("你输入的表达式有误!\n");
			return 0;
		}            
		}
		else        
			switch(Proceed(GetTop(&StackR),c[i])) /* 此函数用来比较读取的运算符和栈顶运算符的优先级*/
		{
			case '<':   /* 栈顶的元素优先级高*/
				Push(&StackR,c[i]);
				i++;
				break;
			case '=':   /* 遇到匹配的小括号时则去掉他*/
				Pop(&StackR);
				i++;
				break;
			case '>': /* 栈顶的优先级低则出栈并将结果写入栈内*/
				r = Pop(&StackR);
				a = Pop(&StackD)-'0';
				b = Pop(&StackD)-'0';
				Push(&StackD,Operate(a,r,b)) ;
				break;                
		}
	}
	return (GetTop(&StackD)-'0');   /* 返回运算结果*/
}

int In(char c)         /*问题2：解决In函数问题:判断C是否为运算符是返回1否则返回0*/
{
	char ch[7]={'+','-','*','/','#','(',')'};
	int i;
	for(i = 0; i < 7; i++)
		if(c == ch[i])
			return 1;

	return 0;            
}

char Proceed(char op,char c) /*op为栈顶元素，c为当前读入的运算符,比较二者的优先级*/
{                                                    /*问题1：解决Proceed函数*/
	char ch;              
	if(op=='(' && c==')' || op=='#' && c=='#' )
		ch = '=';
	else
		if(op=='+' || op=='-')     /*栈顶元素为‘+’或‘-’的时候*/
			switch(c)
		{
			case '+':
			case '-':
			case ')':
			case '#': ch = '>'; break;
			case '*':
			case '/':
			case '(': ch = '<';
		}
		else
			if(op=='*' || op=='/')    /*栈顶元素为‘*’或‘/’的时候*/
				switch(c)
			{
				case '+':
				case '-':
				case '*':
				case '/':    
				case ')':
				case '#':    ch = '>'; break;
				case '(':    ch = '<';
			}
			else
				if(op=='(')             /*栈顶元素为‘(’的时候*/
					switch(c)
				{
					case '+':
					case '-':
					case '*':
					case '/':
					case '(': ch = '<'; break;
					case '#':   printf("Error!\n"); exit(0);
				}
				else
					if(op==')')     /*栈顶元素为‘)’的时候*/
						switch(c)
					{
						case '+':
						case '-':
						case '*':
						case '/':
						case '#': ch = '>'; break;
						case '(': printf("Error!\n"); exit(0);
					}
					else
						if(op=='#')              /*栈顶元素为‘#’的时候*/
							switch(c)
						{
							case '+':
							case '-':
							case '*':
							case '/':
							case '(': ch = '<'; break;
							case ')':   printf("Error!\n"); exit(0);
						}
						return ch;                              
}          
/*   问题3：解决Operate函数*/
int Operate(int a,char r,int b) /*返回由aRb的值 */
{
	int s;
	int d1 = a;
	int d2 = b; /*把字符ab变为对应数字*/
	switch(r)
	{
	case '+': s = d1+d2; break;
	case '-': s = d2-d1; break;
	case '*': s = d1*d2; break;
	case '/': s = d2/d1;    
	}
	return (s+'0');    
} 