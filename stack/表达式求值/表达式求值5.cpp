/* �˳���Ĺ���������û���������α��ʽ��ֵ20-10-07 17:43*/
/*����ı��ʽ����#��β�����磺2+3+5��Ӧ���룺2+3+5#��*/
#include <stdio.h>
#include <stdlib.h>
#define   MAXSIZE 16

typedef struct{
	int data[MAXSIZE];
	int top;
	int base;
}seqstack;   /* ˳��ջ�Ķ���*/

/*����Ϊ��������*/
void InitStack(seqstack *);        
int Empty(seqstack *);
void Push(seqstack *, int );
int Pop(seqstack *);
int GetTop(seqstack *);
int Operate(int ,char ,int );
char Proceed(char ,char );
int In(char );
int EvalExpres(void);
/* ��������ջ�ֱ���������Ͳ�����*/
seqstack StackR,StackD;
/*������*/
int main()
{
	int v;
	char ch;
	while(1)
	{
		printf("@@@@@@@@������Ĺ���Ϊ����˳��ջʵ�������������ʽ����ֵ@@@@@@@@\n");
		v = EvalExpres();        
		printf("The result is:%d",v);
		/*����Ϊ�������*/        
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
}   /* ��ʼ��ջ*/


int Empty(seqstack *s)
{   if(s->top == s->base)
return 1;
else
return 0;
}    /* �ж�ջ�Ƿ�Ϊ��*/


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
}    /* ��ջ */

int Pop(seqstack *s)
{    int e;
		if(Empty(s))
		{   printf("Under flow!\n");
		return 0;
		}   /* ����*/
		else
		{   s->top--;
		e = s->data[s->top];
		return e;
		}
} /* ��ջ*/

int GetTop(seqstack *s)    /*ȡջ��Ԫ��*/
{  
	if(Empty(s))
	{   printf("Under flow!\n");
	return 0;
	}
	else
		return s->data[s->top-1];      
}

int EvalExpres(void)    /* ���ʽ��⺯��*/
{
	int a,b,i=0,s=0;
	char c[80],r;
	InitStack(&StackR);
	Push(&StackR,'#');
	InitStack(&StackD);
	printf(" ��������ʽ���ԡ�#��������");
	gets(c);
	while(c[i]!='#' || GetTop(&StackR)!='#')
	{      
		if(!In(c[i]))   /* �ж϶�����ַ���������� �����ջ*/
		{ if(c[i] >= '0' && c[i] <= '9')
		{
			s += c[i]-'0';      
			while(!In(c[++i]))    /*�˴�ʵ�ֵĹ���Ϊ�����������Ϊ��λ��ʱ*/
			{ s*=10;
			s += c[i]-'0';
			}
			Push(&StackD,s+'0');
			s = 0;
		}
		else
		{
			printf("������ı��ʽ����!\n");
			return 0;
		}            
		}
		else        
			switch(Proceed(GetTop(&StackR),c[i])) /* �˺��������Ƚ϶�ȡ���������ջ������������ȼ�*/
		{
			case '<':   /* ջ����Ԫ�����ȼ���*/
				Push(&StackR,c[i]);
				i++;
				break;
			case '=':   /* ����ƥ���С����ʱ��ȥ����*/
				Pop(&StackR);
				i++;
				break;
			case '>': /* ջ�������ȼ������ջ�������д��ջ��*/
				r = Pop(&StackR);
				a = Pop(&StackD)-'0';
				b = Pop(&StackD)-'0';
				Push(&StackD,Operate(a,r,b)) ;
				break;                
		}
	}
	return (GetTop(&StackD)-'0');   /* ����������*/
}

int In(char c)         /*����2�����In��������:�ж�C�Ƿ�Ϊ������Ƿ���1���򷵻�0*/
{
	char ch[7]={'+','-','*','/','#','(',')'};
	int i;
	for(i = 0; i < 7; i++)
		if(c == ch[i])
			return 1;

	return 0;            
}

char Proceed(char op,char c) /*opΪջ��Ԫ�أ�cΪ��ǰ����������,�Ƚ϶��ߵ����ȼ�*/
{                                                    /*����1�����Proceed����*/
	char ch;              
	if(op=='(' && c==')' || op=='#' && c=='#' )
		ch = '=';
	else
		if(op=='+' || op=='-')     /*ջ��Ԫ��Ϊ��+����-����ʱ��*/
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
			if(op=='*' || op=='/')    /*ջ��Ԫ��Ϊ��*����/����ʱ��*/
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
				if(op=='(')             /*ջ��Ԫ��Ϊ��(����ʱ��*/
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
					if(op==')')     /*ջ��Ԫ��Ϊ��)����ʱ��*/
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
						if(op=='#')              /*ջ��Ԫ��Ϊ��#����ʱ��*/
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
/*   ����3�����Operate����*/
int Operate(int a,char r,int b) /*������aRb��ֵ */
{
	int s;
	int d1 = a;
	int d2 = b; /*���ַ�ab��Ϊ��Ӧ����*/
	switch(r)
	{
	case '+': s = d1+d2; break;
	case '-': s = d2-d1; break;
	case '*': s = d1*d2; break;
	case '/': s = d2/d1;    
	}
	return (s+'0');    
} 