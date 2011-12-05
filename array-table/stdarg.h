今天写数组的数据结构时，看到了函数参数不确定头文件stdarg.h的一些用法，典型的例子有大家熟悉的函数printf()、scanf()和系统调用execl()等，那么它们是怎样实现的呢？
 

现在先用一个使用过程讲解一下：

◎用法:
func( Type para1, Type para2, Type para3, ... )
{
/****** Step 1 ******/
va_list ap;
va_start( ap, para3 ); //一定要“...”之前的那个参数 ，而且这个参数不能使引用类型，因为引用类型不能根据其地址获取后面参数的地址

/****** Step 2 ******/
//此时ap指向第一个可变参数
//调用va_arg取得里面的值

Type xx = va_arg( ap, Type );

//Type一定要相同，如:
//char *p = va_arg( ap, char *);
//int i = va_arg( ap, int );

//如果有多个参数继续调用va_arg

/****** Step 3 ******/
va_end(ap); //For robust!
}
然后写个小程序，大家看看就明白了stdarg.h的用法了

 
#include <iostream>
#include <stdarg.h>
const int N=5;
using namespace std;
void Stdarg(int a1,...)
{
    va_list argp;
    int i;
    int  ary[N];
    va_start(argp,a1);
    ary[0]=a1;
    for(i=1;i< N;i++)
       ary[i]=va_arg(argp,int);
    va_end(argp);
    for(i=0;i< N;i++)
       cout<<ary[i]<<endl;
}
void main()
{
    Stdarg(5,12,64,34,23);
}

最后我们来分析一下stdarg.h这个头文件（呵呵，本人也是看的不太懂）

typedef char * va_list;

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#define _crt_va_start(ap,v) ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap) ( ap = (va_list)0 )
va_list argptr;
C语言的函数是从右向左压入堆栈的,调用va_start后，
按定义的宏运算，_ADDRESSOF得到v所在的地址，然后这个
地址加上v的大小，则使ap指向第一个可变参数如图:

栈底 高地址
| .......
| 函数返回地址
| .......
| 函数最后一个参数
| ....
| 函数第一个可变参数 <--va_start后ap指向
| 函数最后一个固定参数
| 函数第一个固定参数
栈顶 低地址


然后，用va_arg()取得类型t的可变参数值, 先是让ap指向下一个参数:
ap += _INTSIZEOF(t)，然后在减去_INTSIZEOF(t)，使得表达式结果为
ap之前的值，即当前需要得到的参数的地址，强制转换成指向此参数的
类型的指针，然后用*取值

最后，用va_end(ap)，给ap初始化，保持健壮性。


example:(chenguiming)

#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include <stdarg.h>

int average( int first, ... ) //变参数函数,C++里也有
{
int count=0,i=first,sum=0;
va_list maker; //va_list 类型数据可以保存函数的所有参数,做为一个列表一样保存
va_start(maker,first); //设置列表的起始位置
while(i!=-1)
{
sum+=i;
count++;
i=va_arg(maker,int);//返回maker列表的当前值,并指向列表的下一个位置
}
return sum/count;

}

void main(void)
{
printf( "Average is: %d\n", average( 2, 3, 4,4, -1 ) );
}


Linux下的stdarg.h

#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list; /* 定义va_list 是一个字符指针类型*/

/* Amount of space required in an argument list for an arg of type TYPE.
TYPE may alternatively be an expression whose type is used. */
/* 下面给出了类型为TYPE 的arg 参数列表所要求的空间容量。
TYPE 也可以是使用该类型的一个表达式 */

// 下面这句定义了取整后的TYPE 类型的字节长度值。是int 长度(4)的倍数。
#define __va_rounded_size(TYPE) \
(((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

// 下面这个函数（用宏实现）使AP 指向传给函数的可变参数表的第一个参数。
// 在第一次调用va_arg 或va_end 之前，必须首先调用该函数。
// 17 行上的__builtin_saveregs()是在gcc 的库程序libgcc2.c 中定义的，用于保存寄存器。
// 它的说明可参见gcc 手册章节“Target Description Macros”中的
// “Implementing the Varargs Macros”小节。
#ifndef __sparc__
#define va_start(AP, LASTARG) \
(AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#else
#define va_start(AP, LASTARG) \
(__builtin_saveregs (), \
AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

// 下面该宏用于被调用函数完成一次正常返回。va_end 可以修改AP 使其在重新调用
// va_start 之前不能被使用。va_end 必须在va_arg 读完所有的参数后再被调用。
void va_end (va_list); /* Defined in gnulib *//* 在gnulib 中定义 */
#define va_end(AP)

// 下面该宏用于扩展表达式使其与下一个被传递参数具有相同的类型和值。
// 对于缺省值，va_arg 可以用字符、无符号字符和浮点类型。
// 在第一次使用va_arg 时，它返回表中的第一个参数，后续的每次调用都将返回表中的
// 下一个参数。这是通过先访问AP，然后把它增加以指向下一项来实现的。
// va_arg 使用TYPE 来完成访问和定位下一项，每调用一次va_arg，它就修改AP 以指示
// 表中的下一参数。
#define va_arg(AP, TYPE) \
(AP += __va_rounded_size (TYPE), \
*((TYPE *) (AP - __va_rounded_size (TYPE))))

#endif /* _STDARG_H */ 


今天在写ini配置文件操作类时不小心遇到了标题中的几个宏，一时迷惑不解，花了半个钟左右才算是弄懂了它们。

当你的函数的参数个数不确定时，就可以使用上述宏进行动态处理，这无疑为你的程序增加了灵活性。

Example:

CString AppendString(CString str1,...)//一个连接字符串的函数，参数个数可以动态变化
{
    LPCTSTR str=str1;//str需为指针类型，因为va_arg宏返回的是你的参数的指针，但是如果你的参数为int等简                     //单类型，则不必为指针，因为变量名实际上即是指针。
    CString res;
    va_list marker;   //你的类型链表
    va_start(marker,str1);//初始化你的marker链表

    while(str!="ListEnd")//ListEnd:参数的结束标志，十分重要，在实际中需自行指定
    {
        res+=str;
        str=va_arg(marker,CString);//取得下一个指针
    }
    va_end(marker);//结束，与va_start合用
    return res;
}

int main()
{
    CString  str=AppendString("xu","zhi","hong","ListEnd");
    cout<<str.GetBuffer(str.GetLength())<<endl;
    return 0;
}

输出 xuzhihong
CString AppendString(CString str1,...)，因为连接字符串的参数可以动态变化，你不知用户要进行连接的字符串个数是多少，所以你可以用…来代替。但是要注意的是你的函数要有一个参数作为标志来表示结束，否则会出错。在下例中用ListEnd作为结束符。还有va_arg返回的是你参数内容的指针。上例在支持MFC程序的console下运行通过。

MSDN是你最好的老师，如果你还不明白请参看MSDN并且编多几个例子进行尝试，当然顿感开怀，说明此时你已经明白，呵呵。

自写的ini配置文件操作类已经完成，接下来会对注册表的常用操作进行封装。

 va_list 详解

VA_LIST 是在C语言中解决变参问题的一组宏

他有这么几个成员：

1） va_list型变量：

#ifdef  _M_ALPHA
typedef struct {
        char *a0;       /* pointer to first homed integer argument */
        int offset;     /* byte offset of next parameter */
} va_list;
#else
typedef char *  va_list;
#endif

2）_INTSIZEOF 宏，获取类型占用的空间长度，最小占用长度为int的整数倍：

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

3）VA_START宏，获取可变参数列表的第一个参数的地址（ap是类型为va_list的指针，v是可变参数最左边的参数）：

#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )

4）VA_ARG宏，获取可变参数的当前参数，返回指定类型并将指针指向下一参数（t参数描述了当前参数的类型）：

#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )

5）VA_END宏，清空va_list可变参数列表：

#define va_end(ap)      ( ap = (va_list)0 )

VA_LIST的用法：     
       （1）首先在函数里定义一具VA_LIST型的变量，这个变量是指向参数的指针；
       （2）然后用VA_START宏初始化变量刚定义的VA_LIST变量；
       （3）然后用VA_ARG返回可变的参数，VA_ARG的第二个参数是你要返回的参数的类型（如果函数有多个可变参数的，依次调用VA_ARG获取各个参数）；
       （4）最后用VA_END宏结束可变参数的获取。
使用VA_LIST应该注意的问题：
   （1）可变参数的类型和个数完全由程序代码控制,它并不能智能地识别不同参数的个数和类型；
   （2）如果我们不需要一一详解每个参数，只需要将可变列表拷贝至某个缓冲，可用vsprintf函数；
   （3）因为编译器对可变参数的函数的原型检查不够严格,对编程查错不利.不利于我们写出高质量的代码；

小结：可变参数的函数原理其实很简单，而VA系列是以宏定义来定义的，实现跟堆栈相关。我们写一个可变参数的C函数时，有利也有弊,所以在不必要的场合，我们无需用到可变参数，如果在C++里，我们应该利用C++多态性来实现可变参数的功能，尽量避免用C语言的方式来实现。