����д��������ݽṹʱ�������˺���������ȷ��ͷ�ļ�stdarg.h��һЩ�÷������͵������д����Ϥ�ĺ���printf()��scanf()��ϵͳ����execl()�ȣ���ô����������ʵ�ֵ��أ�
 

��������һ��ʹ�ù��̽���һ�£�

���÷�:
func( Type para1, Type para2, Type para3, ... )
{
/****** Step 1 ******/
va_list ap;
va_start( ap, para3 ); //һ��Ҫ��...��֮ǰ���Ǹ����� �����������������ʹ�������ͣ���Ϊ�������Ͳ��ܸ������ַ��ȡ��������ĵ�ַ

/****** Step 2 ******/
//��ʱapָ���һ���ɱ����
//����va_argȡ�������ֵ

Type xx = va_arg( ap, Type );

//Typeһ��Ҫ��ͬ����:
//char *p = va_arg( ap, char *);
//int i = va_arg( ap, int );

//����ж��������������va_arg

/****** Step 3 ******/
va_end(ap); //For robust!
}
Ȼ��д��С���򣬴�ҿ�����������stdarg.h���÷���

 
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

�������������һ��stdarg.h���ͷ�ļ����Ǻǣ�����Ҳ�ǿ��Ĳ�̫����

typedef char * va_list;

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#define _crt_va_start(ap,v) ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap) ( ap = (va_list)0 )
va_list argptr;
C���Եĺ����Ǵ�������ѹ���ջ��,����va_start��
������ĺ����㣬_ADDRESSOF�õ�v���ڵĵ�ַ��Ȼ�����
��ַ����v�Ĵ�С����ʹapָ���һ���ɱ������ͼ:

ջ�� �ߵ�ַ
| .......
| �������ص�ַ
| .......
| �������һ������
| ....
| ������һ���ɱ���� <--va_start��apָ��
| �������һ���̶�����
| ������һ���̶�����
ջ�� �͵�ַ


Ȼ����va_arg()ȡ������t�Ŀɱ����ֵ, ������apָ����һ������:
ap += _INTSIZEOF(t)��Ȼ���ڼ�ȥ_INTSIZEOF(t)��ʹ�ñ��ʽ���Ϊ
ap֮ǰ��ֵ������ǰ��Ҫ�õ��Ĳ����ĵ�ַ��ǿ��ת����ָ��˲�����
���͵�ָ�룬Ȼ����*ȡֵ

�����va_end(ap)����ap��ʼ�������ֽ�׳�ԡ�


example:(chenguiming)

#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include <stdarg.h>

int average( int first, ... ) //���������,C++��Ҳ��
{
int count=0,i=first,sum=0;
va_list maker; //va_list �������ݿ��Ա��溯�������в���,��Ϊһ���б�һ������
va_start(maker,first); //�����б����ʼλ��
while(i!=-1)
{
sum+=i;
count++;
i=va_arg(maker,int);//����maker�б�ĵ�ǰֵ,��ָ���б����һ��λ��
}
return sum/count;

}

void main(void)
{
printf( "Average is: %d\n", average( 2, 3, 4,4, -1 ) );
}


Linux�µ�stdarg.h

#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list; /* ����va_list ��һ���ַ�ָ������*/

/* Amount of space required in an argument list for an arg of type TYPE.
TYPE may alternatively be an expression whose type is used. */
/* �������������ΪTYPE ��arg �����б���Ҫ��Ŀռ�������
TYPE Ҳ������ʹ�ø����͵�һ�����ʽ */

// ������䶨����ȡ�����TYPE ���͵��ֽڳ���ֵ����int ����(4)�ı�����
#define __va_rounded_size(TYPE) \
(((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

// ��������������ú�ʵ�֣�ʹAP ָ�򴫸������Ŀɱ������ĵ�һ��������
// �ڵ�һ�ε���va_arg ��va_end ֮ǰ���������ȵ��øú�����
// 17 ���ϵ�__builtin_saveregs()����gcc �Ŀ����libgcc2.c �ж���ģ����ڱ���Ĵ�����
// ����˵���ɲμ�gcc �ֲ��½ڡ�Target Description Macros���е�
// ��Implementing the Varargs Macros��С�ڡ�
#ifndef __sparc__
#define va_start(AP, LASTARG) \
(AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#else
#define va_start(AP, LASTARG) \
(__builtin_saveregs (), \
AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

// ����ú����ڱ����ú������һ���������ء�va_end �����޸�AP ʹ�������µ���
// va_start ֮ǰ���ܱ�ʹ�á�va_end ������va_arg �������еĲ������ٱ����á�
void va_end (va_list); /* Defined in gnulib *//* ��gnulib �ж��� */
#define va_end(AP)

// ����ú�������չ���ʽʹ������һ�������ݲ���������ͬ�����ͺ�ֵ��
// ����ȱʡֵ��va_arg �������ַ����޷����ַ��͸������͡�
// �ڵ�һ��ʹ��va_arg ʱ�������ر��еĵ�һ��������������ÿ�ε��ö������ر��е�
// ��һ������������ͨ���ȷ���AP��Ȼ�����������ָ����һ����ʵ�ֵġ�
// va_arg ʹ��TYPE ����ɷ��ʺͶ�λ��һ�ÿ����һ��va_arg�������޸�AP ��ָʾ
// ���е���һ������
#define va_arg(AP, TYPE) \
(AP += __va_rounded_size (TYPE), \
*((TYPE *) (AP - __va_rounded_size (TYPE))))

#endif /* _STDARG_H */ 


������дini�����ļ�������ʱ��С�������˱����еļ����꣬һʱ�Ի󲻽⣬���˰�������Ҳ�����Ū�������ǡ�

����ĺ����Ĳ���������ȷ��ʱ���Ϳ���ʹ����������ж�̬����������Ϊ��ĳ�������������ԡ�

Example:

CString AppendString(CString str1,...)//һ�������ַ����ĺ����������������Զ�̬�仯
{
    LPCTSTR str=str1;//str��Ϊָ�����ͣ���Ϊva_arg�귵�ص�����Ĳ�����ָ�룬���������Ĳ���Ϊint�ȼ�                     //�����ͣ��򲻱�Ϊָ�룬��Ϊ������ʵ���ϼ���ָ�롣
    CString res;
    va_list marker;   //�����������
    va_start(marker,str1);//��ʼ�����marker����

    while(str!="ListEnd")//ListEnd:�����Ľ�����־��ʮ����Ҫ����ʵ����������ָ��
    {
        res+=str;
        str=va_arg(marker,CString);//ȡ����һ��ָ��
    }
    va_end(marker);//��������va_start����
    return res;
}

int main()
{
    CString  str=AppendString("xu","zhi","hong","ListEnd");
    cout<<str.GetBuffer(str.GetLength())<<endl;
    return 0;
}

��� xuzhihong
CString AppendString(CString str1,...)����Ϊ�����ַ����Ĳ������Զ�̬�仯���㲻֪�û�Ҫ�������ӵ��ַ��������Ƕ��٣�����������á������档����Ҫע�������ĺ���Ҫ��һ��������Ϊ��־����ʾ������������������������ListEnd��Ϊ������������va_arg���ص�����������ݵ�ָ�롣������֧��MFC�����console������ͨ����

MSDN������õ���ʦ������㻹��������ο�MSDN���ұ�༸�����ӽ��г��ԣ���Ȼ�ٸп�����˵����ʱ���Ѿ����ף��Ǻǡ�

��д��ini�����ļ��������Ѿ���ɣ����������ע���ĳ��ò������з�װ��

 va_list ���

VA_LIST ����C�����н����������һ���

������ô������Ա��

1�� va_list�ͱ�����

#ifdef  _M_ALPHA
typedef struct {
        char *a0;       /* pointer to first homed integer argument */
        int offset;     /* byte offset of next parameter */
} va_list;
#else
typedef char *  va_list;
#endif

2��_INTSIZEOF �꣬��ȡ����ռ�õĿռ䳤�ȣ���Сռ�ó���Ϊint����������

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

3��VA_START�꣬��ȡ�ɱ�����б�ĵ�һ�������ĵ�ַ��ap������Ϊva_list��ָ�룬v�ǿɱ��������ߵĲ�������

#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )

4��VA_ARG�꣬��ȡ�ɱ�����ĵ�ǰ����������ָ�����Ͳ���ָ��ָ����һ������t���������˵�ǰ���������ͣ���

#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )

5��VA_END�꣬���va_list�ɱ�����б�

#define va_end(ap)      ( ap = (va_list)0 )

VA_LIST���÷���     
       ��1�������ں����ﶨ��һ��VA_LIST�͵ı��������������ָ�������ָ�룻
       ��2��Ȼ����VA_START���ʼ�������ն����VA_LIST������
       ��3��Ȼ����VA_ARG���ؿɱ�Ĳ�����VA_ARG�ĵڶ�����������Ҫ���صĲ��������ͣ���������ж���ɱ�����ģ����ε���VA_ARG��ȡ������������
       ��4�������VA_END������ɱ�����Ļ�ȡ��
ʹ��VA_LISTӦ��ע������⣺
   ��1���ɱ���������ͺ͸�����ȫ�ɳ���������,�����������ܵ�ʶ��ͬ�����ĸ��������ͣ�
   ��2��������ǲ���Ҫһһ���ÿ��������ֻ��Ҫ���ɱ��б�����ĳ�����壬����vsprintf������
   ��3����Ϊ�������Կɱ�����ĺ�����ԭ�ͼ�鲻���ϸ�,�Ա�̲����.����������д���������Ĵ��룻

С�᣺�ɱ�����ĺ���ԭ����ʵ�ܼ򵥣���VAϵ�����Ժ궨��������ģ�ʵ�ָ���ջ��ء�����дһ���ɱ������C����ʱ������Ҳ�б�,�����ڲ���Ҫ�ĳ��ϣ����������õ��ɱ�����������C++�����Ӧ������C++��̬����ʵ�ֿɱ�����Ĺ��ܣ�����������C���Եķ�ʽ��ʵ�֡�