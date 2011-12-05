/*在TC2 和 VC6下都可以顺利运行。
做了一个下午。一定要用我这个噢。
有简单的输入错误检测。有完整的说明和
注释*/

#include<stdio.h> /*库文件包含*/
#include<string.h> /*用于字符串操作*/
#include<stdlib.h> /*用于exit函数*/

/**************************************************************************
int check(char *c)
输入参数：
char *c: 输入的字符串
返回参数：
0：字符串中有不符合规定的字符
1: 字符串字符符合规定，没有不符合规定的字符.
功能：
检查字符串中有否除了 0-9, +,-,*,/,(,),之外的其他字符，
如果有，则返回0, 表示出现错误。
若没有，则返回1,表式字符串符合规定。
**************************************************************************/
int check(char *c)
{
	int k=0;
	while(*c!='\0')
	{
		if((*c>='0' && *c<='9') || *c=='+' || 
			*c=='-' || *c=='*' || *c=='/' || 
			*c=='.' || *c=='(' ||  *c==')' )
		{

		}
		else
		{
			printf("input error, there have the char not the math expression char!\n");
			return 0;
		}

		if(*c=='(')
			k++;
		else if(*c==')')
			k--;

		c++;
	}
	if(k!=0)
	{
		printf("input error, there is not have correct bracket '()'!\n");
		return 0;
	}
	return 1;
}

/**************************************************************************
void  move(char *f, double *s,int p) 

输入参数：
char *f : 运算符数组
double *s: 数值数组
int p:  当前运算符数组位置。
返回参数:
无
功能：
将当前已经完成运算的运算符消去，同时将数值数组的位置调整以进行下一次运算。
传入值p若为3
则当前符号的数组位置为3.
f[3]=f[3+1].......f[len-2]=f[len-1]  f[len-1]='\0';
s[i]=s[i+1].......s[len-1]=s[len]  因为数值比运算符多一个。
***************************************************************************/

void  move(char *f, double *s,int p)  
{
	int i=0,len=strlen(f);
	for(i=p; i<len; i++)   /*将已经运算过的符号，空出来的位置用后面的符号来填充，*/      
	{      /*即把乘和除号的位置用后面的加和减号填充*/
		f[i]=f[i+1];
		s[i]=s[i+1];
	}
	s[i]=s[i+1];
	f[len-1]='\0';
}
/**************************************************************************
double convnum(char *c)
输入参数：
char *c :由数字和小数点组成的字符，用以转换成double型的数值。
返回参数：
num:返回转换好的值。
功能：
将输入的字符串先将其小数点以前的部分复制到temp[]数组中，
若有小数点，则将小数点之后的数值，也就是小数部分先进行计算,值存入num中
计算完成后，再对整数部分进行计算，值加上小数部分的值，存入num中。
***************************************************************************/
double convnum(char *c)
{
	double num=0.0;
	double a=1.0;
	int i=0,p=0,len=0;
	char temp[100];
	int tempi=0;
	int start=0;
	int f=1;   /*正负符号指示器，若为1则为正数，为－1，此数为负数*/

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
			break;
		}
		temp[tempi++]=c[i];  /*将整数部分复制到temp[]中*/
	}
	temp[tempi]='\0';

	if(p!=0)
	{
		for(i=p+1;i<len;i++) /*将小数部分计算出来*/
		{
			if(c[i]=='.')  /*如果有多余的小数点，则表示输入错误*/
			{
				printf("there is more that one dot '.' in number!error!\n");
				exit(0);
			}
			a=a*0.1;
			num+=(a*(c[i]-48));
		}
	}

	a=1.0;

	len=strlen(temp);           /*计算整数部分*/
	for(i=len-1;i>=0; i--)
	{
		num=num+(a*(temp[i]-48));
		a*=10;
	}

	num=num*f;
	return num;
}

/**************************************************************************
double good(char *c)
输入参数：
char *c :即将进行运算的字符串型数学表达式。如3.5+(2*3/5)
返回参数：
s[0]:计算结果将放入s[0]中
功能：
将输入的字符串中的数字分别调用convnum(char *c)函数进行数值变换，再将其依
次存入doulbe s[i]中，将加减乘除运算符依次存入字符串符号数组 char f[i]中，
然后如果遇到括号，则将括号内的字符串存入另一字符数组中，然后用此
good(char *c) 递归函数进行递归运算。 然后根据先乘除，后加减的顺序对已
存入数组的数值根 据存入字符串符号数组的运算符进行运算。结果存入s[0]中。
返回最终结果。
***************************************************************************/
double good(char *c)  /*可递归函数*/
{      /*取得数值字符串，并调用convnum转换成double*/
	char g[100],number[30];  /*g,保存当前的表达式串,number保存一个数的所有字符*/
	char f[80]; /*保存所有的符号的堆栈*/
	int fi=0; /*保存符号的位置指针*/
	double s[80]; /*保存当前所有的数的一个堆栈*/
	int si=0; /*保存数字位置指针*/
	int k=0; /* 若k=1则表示有一对括号*/
	int num=0,i=0; /*num保存新括号内的字符数,i 保存number里的字符位置*/
	int cc=0; /*乘除符号数量*/
	int jj=0; /*加减符号数量*/

	while(*c!='\0')/*当p==1 和k==0时，表示已经把括号里的内容全部复制到g[100]中了*/
	{
		k=0;
		num=0;

		switch(*c)
		{
		case '+':   /*当前字符为+-乘除时则表示*/
		case '-':
		case '*':
		case'/':
			f[fi++]=*c;
			if(*c=='*' || *c=='/')
				cc++;
			else
				jj++;
			if(*(c-1)!=')')
			{
				number[i]='\0';
				i=0;/*完成一个数字的复制，其位置指针i=0*/

				s[si++]=convnum(number);
			}
			break;
		case'(':   /*有括号，则将当前括号作用范围内的全部字符保存，作为*/
			k++; /*一个新的字符表达式进行递归调用good函数计算。*/
			while(k>0)
			{
				c++;
				g[num]=*c;
				num++;
				if(*c==')')
				{
					k--;
				}
				else if(*c=='(')
				{
					k++;
				}
			}
			g[num-1]='\0';
			num=0;/*完成一个括号内容的复制，其位置指针num=0*/
			s[si++]=good(g);
			break;
		default:
			number[i++]=*c;

			if(*(c+1)=='\0')
			{ number[i]='\0';
			s[si++]=convnum(number);
			}
			break;
		}

		c++;
	}

	f[fi]='\0';

	i=0;
	while(cc>0)
	{
		switch(f[i])
		{
		case '*': cc--;
			s[i+1]=s[i]*s[i+1];
			move(f,s,i);
			break;
		case '/': cc--;
			s[i+1]=s[i]/(float)s[i+1];
			move(f,s,i);
			break;
		default:
			i++;
			break;
		}
	}

	i=0;
	while(jj>0)
	{
		switch(f[i])
		{
		case '+': s[i+1]=s[i]+s[i+1];
			jj--;
			move(f,s,i);
			break;
		case '-': s[i+1]=s[i]-s[i+1];
			jj--;
			move(f,s,i);
			break;
		default:
			printf("operator error!");
			break;
		}
	}

	return s[0];
}

void main()
{
	char str[100];
	double sum=0;
	int p=1;

	while(1)
	{
		printf("enter expression: enter 'exit' end of program\n");
		scanf("%s",str);
		p=strcmp(str,"exit");
		if(p==0)
			break;
		p=check(str);

		if(p==0)
			continue;
		sum=good(str);
		printf("%s=%f",str,sum);
		printf("\n");
	}
	printf("good bye!\n");
}