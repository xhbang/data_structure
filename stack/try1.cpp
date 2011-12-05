/*------------------------------
л�г�Ʒ
û�а�Ȩ
��ӭ����
2009.10.24
------------------------------*/

#include <stdio.h>
//#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define INIT_SIZE 100

//������ջ
typedef struct{
	char arr[INIT_SIZE];				//ע��˴�����
	int ptop;					//�ǵ�һ��Ҫ��ʼ��Ϊ-1
}cStack;

//������ջ
typedef struct{
	double arr[INIT_SIZE];
	int ptop;
}dStack;

/*---------------------------
�����Ǻ�����
----------------------------*/

/*---------------------------
void input(char *s)
���룺����̨���ַ����룬������100�ַ�����
�����
���ܣ�����ַ���������
----------------------------*/
int input(char *str){
	int p=1;
	printf("enter expression: enter 'exit' end of program\n");
	scanf("%s",str);
	p=strcmp(str,"exit");
	if(p==0)
		return 0;
	else
		return 1;
}
/*--------------------------
int precheck(char *s)
���룺�����ʼ���ʽ���ַ���
�����0(��ʾ����) 1(��ʾ�ɹ�)
���ܣ�����ַ��������ݺ͡������͡�������ƥ��
---------------------------*/
int precheck(char *s){
	int k=0;
	while(*s!='\0'){
		if(*s=='*' || *s=='/' || *s=='+' || *s=='-' || *s=='%' || *s=='#' || *s<='9' && *s>='0')
			;
		else{
			printf("INVALID SYMBOL IN STRING!PLEASE REINPUT!\n");
			return 0;
		}
		if(*s=='(')
			k++;
		if(*s==')')
			k--;
		s++;
	}
	if(k != 0){
		printf("the num of ( and ) do NOT match,plsase re input:\n");
		return 0;
	}
	return 1;
}


/*--------------------------
int in(char ch)
���룺ͬ��
�����1(�ǲ�����)��0(���ַ���)
���ܣ����ֲ��������ַ���
---------------------------*/
int in(char ch){
	if(ch=='*' || ch=='/' || ch=='+' || ch=='-' || ch=='%' )
		return 1;
	else 
		return 0;
}

/*---------------------------
int isempty(Stack s)
���ܣ��ж�ջ�Ƿ�Ϊ��
����ֵ��1��ʾ��ջ
				  0��ʾ��ջ
---------------------------*/
int isempty(cStack s){
	return (s.ptop==-1);
}

int isempty(dStack s){
	return (s.ptop==-1);
}

/*--------------------------
������Ҫ���֣��´������ؽ��
void push(Stack &s,char ch)
���룺���������߲�����ջ�����б��ʽ��һ��char
�����
���ܣ�ѹջ
--------------------------*/
void cpush(cStack &s,char ch){
	if(s.ptop<INIT_SIZE-1){
		++s.ptop;
		s.arr[s.ptop]=ch;
	}
	else{
		printf("*******ERROR,OVERFLOW*********\n");
		exit(1);
	}
}

void dpush(dStack &s,double num){
	if(s.ptop<INIT_SIZE-1){
		++s.ptop;
		s.arr[s.ptop]=num;
	}
	else{
		printf("*******ERROR,OVERFLOW*********\n");
		exit(1);
	}
}
/*--------------------------
void pop(Stack &s)
���룺���������߲�����ջ
���ܣ���Ȼ��pop��
--------------------------*/
void pop(cStack &s){
	if(isempty(s)){
		printf("******NO ELEMENT TO POP******\n");
		exit(1);
	}
	else
		--s.ptop;
}

void pop(dStack &s){
	if(isempty(s)){
		printf("******NO ELEMENT TO POP******\n");
		exit(1);
	}
	else
		--s.ptop;
}

/*----------------------------
���ڵ����õ�һ������
void show(Stack s)
������ʾStack��ֵ
------------------------------*/
void show(cStack s){
	while(!isempty(s))
		printf("POPING:\t%c\n",s.arr[s.ptop--]);
}

void show(dStack s){
	while(!isempty(s))
		printf("POPING:\t%c\n",s.arr[s.ptop--]);
}

/*-------------------------
double operate(char a,char op,char b)
���룺����ֵ��һ��������
�����һ��double������
���ܣ����һ������
ע�⣺����ת��Ϊchar��
����B����pop�������Ǹ�
-------------------------*/
double operate(double a,char op,double b){
	double dval=0.0;
	if(op=='*')
		dval=(a-'0')*(b-'0');
	if(op=='/')
		dval=(a-'0')/(b-'0');
	if(op=='+')
		dval=(a-'0')+(b-'0');
	if(op=='-')
		dval=(a-'0')-(b-'0');
/*	if(op=='%')
		dval=(a-'0')%(b-'0');
*/
	return dval;
}

/*------------------------
char gettop(Stack s)
���룺ջһ��
�����topָ���Ԫ��
����:���ջ��Ԫ��
-------------------------*/
char gettop(cStack s){
	if(isempty(s)){
		printf("EMPTY STACK,CAN'T GET TOP!\n");
		exit(1);
	}
	return s.arr[s.ptop];
}

double gettop(dStack s){
	if(isempty(s)){
		printf("EMPTY STACK,CAN'T GET TOP!\n");
		exit(1);
	}
	return s.arr[s.ptop];
}
/*---------------------------
double convnum(char *s)
���룺һ�β������Ŀ�ʼ
�����char(û��С��)
���ܣ����char*s����������С����Ļ�����
			 �ַ���ת��ΪС���ټ���
ע�⣺����Ҫ��doubleת��Ϊchar����ʵ֤�����ǲ��е�
----------------------------*/
double convnum(char *c)
{
	double num=0.0;
	double a=1.0;
	int i=0,p=0,len=0;
	char temp[100];
	int tempi=0;
	int start=0;
	int f=1;   //��������ָʾ������Ϊ1��Ϊ������Ϊ��1������Ϊ����

	len=strlen(temp);

	if(c[0]=='-')
	{
		start=1;
		f=-1;
	}
	for(i=start; i<len; i++)
	{
		if(c[i]=='.') 
		{
			p=i;
			break;			//���С�����λ��
		}
		temp[tempi++]=c[i];  //���������ָ��Ƶ�temp[]��
	}
	temp[tempi]='\0';			//��������

	if(p!=0)			//p����0��ʾû��С����
	{
		for(i=p+1;i<len;i++) //��С�����ּ������
		{
			if(c[i]=='.')  //����ж����С���㣬���ʾ�������
			{
				printf("there is more that one dot '.' in number!ERROR!\n");
				exit(0);
			}
			a=a*0.1;
			num+=(a*(c[i]-48));
		}
	}

	a=1.0;			//����a,��ʾ��ʼ�����ļ���

	len=strlen(temp);           //������������
	for(i=len-1;i>=0; i--)
	{
		num=num+(a*(temp[i]-48));
		a*=10;
	}

	num=num*f;
	return num;
}

/*-----------------------------
int compare(char op,char ch)
���ܣ��Ƚ����ȼ�
���룺op��gettop��stack
ch�Ƕ���Ĳ�����
��������op�����ȼ�����ch,����1
��ȷ���0��С�ڷ���-1
------------------------------*/
int compare(char op,char ch){
	if(op == '(' && ch== ')' || op=='#' && ch=='#')				//���°Ѻ���ɾ��
		return 0;
	else if
		((op == '+' && ch == '*') || (op == '+' && ch == '/')
		|| (op == '-' && ch == '*') || (op == '-' && ch == '/')
		|| (op != ')' && ch == '(') || (op == '(' && ch!= ')'))
		return -1;
	else if				//���������
		(op==')'&& ch=='(' || op=='(' &&ch==')' ||op=='(' && ch=='#'){			//���ܵĴ�����#��),����precheck����
		printf("INPUT ERROR!\n");
		exit(1);
	}
	else	return 1;
}

/*������һ�׸�Ϊ���Ƶ��߼����,�����鷳������
char Proceed(char op,char c) //opΪջ��Ԫ�أ�cΪ��ǰ����������,�Ƚ϶��ߵ����ȼ�
{                                                  
	char ch;              
	if(op=='(' && c==')' || op=='#' && c=='#' )
		ch = '=';
	else
		if(op=='+' || op=='-')     //ջ��Ԫ��Ϊ��+����-����ʱ��
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
			if(op=='*' || op=='/')    //ջ��Ԫ��Ϊ��*����/����ʱ��
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
				if(op=='(')             //ջ��Ԫ��Ϊ��(����ʱ��
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
					if(op==')')     //ջ��Ԫ��Ϊ��)����ʱ��
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
						if(op=='#')              //ջ��Ԫ��Ϊ��#����ʱ��
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
*/


/*---------------------------
�ѵ㣡����
double Evalexpress(char *s)
���룺char *s,����õ�����
�����double�洢����ֵ,gettop
---------------------------*/
double Evalexpress(char *s){
	dStack OPTD;
	cStack OPTR;
	char op;			//����POP
	double num1,num2;
	char temp[INIT_SIZE];			//�����洢���ܵ�����
	int tempi=0;		//���������λ��
	double dtemp=0.0;
	OPTD.ptop=-1;
	OPTR.ptop=-1;
	cpush(OPTR,'#');
	while(*s!='#' || gettop(OPTR)!='#'){
		if(!in(*s) || (*s)=='.'){
			temp[tempi++]=*s++;
			dtemp=convnum(temp);
			dpush(OPTD,dtemp);
		}
		else
			switch(compare(gettop(OPTR),*s)){

			case 1:
				op=gettop(OPTR);
				pop(OPTR);
				num1=gettop(OPTD);
				pop(OPTD);
				num2=gettop(OPTD);
				pop(OPTD);
				dtemp=operate(num2,op,num1);
				dpush(OPTD,dtemp);
				break;

			case -1:
				cpush(OPTR,*s);
				s++;					//��ôд��Ϊ�˺ö�
				break;

			case 0:
				pop(OPTR);
				s++;
				break;
		}//switch
	}//while
	return gettop(OPTD);

}


//������������
int main(){
	int p=1;
	double v=0.0;
	char str[INIT_SIZE];
	while(1)
	{
		printf("��ӭ�����������ʽ��ֵDEVELOPED BY SONIC\n");
		p=input(str);
		if(p==0)
			break;
		p=precheck(str);
		if(p==0)
			continue;
		v = Evalexpress(str);        
		printf("The result is:%f\n",v);
	}
	return 0;
}