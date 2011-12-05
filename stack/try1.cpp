/*------------------------------
谢行出品
没有版权
欢迎盗版
2009.10.24
------------------------------*/

#include <stdio.h>
//#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define INIT_SIZE 100

//操作符栈
typedef struct{
	char arr[INIT_SIZE];				//注意此处类型
	int ptop;					//记得一定要初始化为-1
}cStack;

//操作数栈
typedef struct{
	double arr[INIT_SIZE];
	int ptop;
}dStack;

/*---------------------------
以下是函数啦
----------------------------*/

/*---------------------------
void input(char *s)
输入：控制台的字符输入，控制在100字符以内
输出：
功能：完成字符串的输入
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
输入：储存初始表达式的字符串
输出：0(表示出错) 1(表示成功)
功能：检查字符串的内容和“（”和“）”的匹配
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
输入：同上
输出：1(是操作符)，0(是字符串)
功能：区分操作符和字符串
---------------------------*/
int in(char ch){
	if(ch=='*' || ch=='/' || ch=='+' || ch=='-' || ch=='%' )
		return 1;
	else 
		return 0;
}

/*---------------------------
int isempty(Stack s)
功能：判断栈是否为空
返回值：1表示空栈
				  0表示非栈
---------------------------*/
int isempty(cStack s){
	return (s.ptop==-1);
}

int isempty(dStack s){
	return (s.ptop==-1);
}

/*--------------------------
函数需要两种，下次用重载解决
void push(Stack &s,char ch)
输入：操作符或者操作数栈，还有表达式的一个char
输出：
功能：压栈
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
输入：操作符或者操作数栈
功能：当然是pop啦
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
用于调试用的一个函数
void show(Stack s)
用来显示Stack的值
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
输入：两个值和一个操作符
输出：一个double操作数
功能：完成一次运算
注意：后面转化为char型
还有B是先pop出来的那个
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
输入：栈一个
输出：top指向的元素
功能:输出栈顶元素
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
输入：一段操作数的开始
输出：char(没有小数)
功能：如果char*s的输入中有小数点的话，把
			 字符串转变为小数再计算
注意：后面要把double转化为char，事实证明这是不行的
----------------------------*/
double convnum(char *c)
{
	double num=0.0;
	double a=1.0;
	int i=0,p=0,len=0;
	char temp[100];
	int tempi=0;
	int start=0;
	int f=1;   //正负符号指示器，若为1则为正数，为－1，此数为负数

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
			break;			//标记小数点的位置
		}
		temp[tempi++]=c[i];  //将整数部分复制到temp[]中
	}
	temp[tempi]='\0';			//整数结束

	if(p!=0)			//p等于0表示没有小数点
	{
		for(i=p+1;i<len;i++) //将小数部分计算出来
		{
			if(c[i]=='.')  //如果有多余的小数点，则表示输入错误
			{
				printf("there is more that one dot '.' in number!ERROR!\n");
				exit(0);
			}
			a=a*0.1;
			num+=(a*(c[i]-48));
		}
	}

	a=1.0;			//重置a,表示开始整数的计算

	len=strlen(temp);           //计算整数部分
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
功能：比较优先级
输入：op是gettop的stack
ch是读入的操作符
输出：如果op的优先级大于ch,返回1
相等返回0，小于返回-1
------------------------------*/
int compare(char op,char ch){
	if(op == '(' && ch== ')' || op=='#' && ch=='#')				//等下把后半句删了
		return 0;
	else if
		((op == '+' && ch == '*') || (op == '+' && ch == '/')
		|| (op == '-' && ch == '*') || (op == '-' && ch == '/')
		|| (op != ')' && ch == '(') || (op == '(' && ch!= ')'))
		return -1;
	else if				//错误处理情况
		(op==')'&& ch=='(' || op=='(' &&ch==')' ||op=='(' && ch=='#'){			//可能的错误还有#和),这种precheck掉了
		printf("INPUT ERROR!\n");
		exit(1);
	}
	else	return 1;
}

/*下面是一套更为完善的逻辑检查,觉得麻烦就算老
char Proceed(char op,char c) //op为栈顶元素，c为当前读入的运算符,比较二者的优先级
{                                                  
	char ch;              
	if(op=='(' && c==')' || op=='#' && c=='#' )
		ch = '=';
	else
		if(op=='+' || op=='-')     //栈顶元素为‘+’或‘-’的时候
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
			if(op=='*' || op=='/')    //栈顶元素为‘*’或‘/’的时候
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
				if(op=='(')             //栈顶元素为‘(’的时候
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
					if(op==')')     //栈顶元素为‘)’的时候
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
						if(op=='#')              //栈顶元素为‘#’的时候
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
难点！！！
double Evalexpress(char *s)
输入：char *s,改造好的输入
输出：double存储最后的值,gettop
---------------------------*/
double Evalexpress(char *s){
	dStack OPTD;
	cStack OPTR;
	char op;			//接受POP
	double num1,num2;
	char temp[INIT_SIZE];			//用来存储可能的数字
	int tempi=0;		//上面数组的位置
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
				s++;					//这么写是为了好读
				break;

			case 0:
				pop(OPTR);
				s++;
				break;
		}//switch
	}//while
	return gettop(OPTD);

}


//我是主函数！
int main(){
	int p=1;
	double v=0.0;
	char str[INIT_SIZE];
	while(1)
	{
		printf("欢迎进入完美表达式求值DEVELOPED BY SONIC\n");
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