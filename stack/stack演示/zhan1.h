//zhan1.h

#define MAX 100
typedef struct stack{
	int cout;
	char data[MAX];
}stack;
//初始化栈
int Init(stack *L)
{
	*L->data=(char)malloc(sizeof(stack));
	if(!L->data){printf("内存分配出错！！");exit(0);}
	L->cout=0;
	L->data[L->cout]='#';
	return 0;
}
//初始元素e入栈
int Push(stack *L,char e)
{
	L->data[L->cout++]=e;
	return 0;
}
//初始元素c出栈
int Pop(stack *L,char *c)
{
	*c=L->data[--L->cout];
	// printf("%c",c);
	return 0;
}
//返回栈的长度
int stacklength(stack *L)
{
	char c;
	int i=0;
	while(L->cout>0)
	{
		++i;
		Pop(L,&c);
		printf(" %c ",c);
	}
	return i;

}
//判断是否是空栈
int StackEmpty(stack *L)
{
	if(L->cout>=0)return 1;
	else return 0;
}
//清栈
int ClearStack(stack *L)
{
	if(L->cout>=0)
	{
		L->cout=0;
		L->data[L->cout]='#';
		printf("\n清栈成功！！！\n");
		return 0;
	}
	else
	{
		printf("\n此栈不存在！！\n");

		return 1;
	}
}
//摧毁栈
int Destory(stack *L)
{
	if(L->cout>=0)
	{
		L->cout=0;
		L->data[L->cout]=NULL;
		return 0;
	}
	else
	{
		printf("\n此栈不存在！！\n");
		return 1;
	}

}

//判断是否是运算符
int is_operator(char op)
{
	switch(op)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':return 1;
	default:return 0;
	}
}
//判断是否是/或者-
int is_special_code(char str)
{
	if(str=='/'||str=='-')return 1;
	else return 0;
}
//判断运算符的优先级
int operator_grade(char op)
{
	switch(op)
	{
	case'+': case'-':return 1;
	case'*': case'/':return 2;
	case'(': case')':return 3;
	default:return 0;
	}
}
//将b与c进行str3运算
int opera(int b,int c,char str3)
{
	int n;
	if(str3=='+')n=b+c;
	if(str3=='-')n=b-c;
	if(str3=='*')n=b*c;
	if(str3=='/')n=b/c;
	return n;
}
//将a与b进行str3运算(小数和负数类)
double operad(double a,double b,char str3)
{
	double n;
	if(str3=='+')n=a+b;
	if(str3=='-')n=a-b;
	if(str3=='*')n=a*b;
	if(str3=='/')n=a/b;
	return n;
}
int numberchar(char number[5])
{
	char number1[5];
	for(int i=0,j=strlen(number)-1;j>=0;number1[i++]=number[j--])
		number1[i]='\0';
	return atoi(number1);
}
//取出连续的数字字符转换成正序数字
int winnumber(stack *L,char *c,char number1[5])
{
	int i;
	Pop(L,c);
	for(i=0;*c>='0'&&*c<='9';number1[i++]=*c,Pop(L,c));
	number1[i]='\0';
	Push(L,*c); //将最后出栈不是数字的字符重新推入栈中
	// puts(number1);
	// printf("%d",numberchar(number1));
	return numberchar(number1);
}
//将数字转换一个个字符存入栈中
int innumber(stack *L,int k)
{
	int i;
	char a;
	for(i=10;(k/i)>=10;i*=10);
	for(;i>=10;a=k/i+48,Push(L,a),k%=i,i/=10);
	a=k+48;
	Push(L,a);
	return 0;
}
//如果是*或者/的话就把它拿出来
char getachar(stack *L,char *c)
{
	Pop(L,c);
	if(*c=='*'||*c=='/'){return *c;}
	else{Push(L,*c);return 0;}  
}