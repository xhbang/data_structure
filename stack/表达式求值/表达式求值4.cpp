//*****stack.h
#ifndef _STACK_H
#define _STACK_H
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
template<class QElemType>
class stack
{
public:
 void InitStack();
 void DestroyStack();
 void ClearStack();
 Status StackEmpty();
 Status StackLength();
 int GetTop(QElemType & e);
 void Push(QElemType e);
 int Pop(QElemType & e);
private:
 struct SqStack{
  QElemType *base;
  QElemType *top;
  int stacksize;
 }S;
};
//******stack.cpp------
template<class QElemType>
void stack<QElemType>::InitStack()
{
 S.base = (QElemType *)malloc(STACK_INIT_SIZE * sizeof(QElemType));
 if(!S.base) exit(0);
 S.top = S.base;
 S.stacksize = STACK_INIT_SIZE;
}
template <class QElemType>
void stack<QElemType>::DestroyStack()
{
 free(S.base);
}
template <class QElemType>
void stack<QElemType>::ClearStack()
{
 S.top = S.base;
}
template <class QElemType>
Status stack<QElemType>::StackEmpty()
{
 if(S.top == S.base) return 1;
 else return 0;
}
template <class QElemType>
Status stack<QElemType>::StackLength()
{
 return (S.top - S.base);
}
template <class QElemType>
int stack<QElemType>::GetTop(QElemType & e)
{
 if(S.top != S.base)
 {
  e = *(S.top - 1);
  return 1;
 }
 else return 0;
}
template <class QElemType>
void stack<QElemType>::Push(QElemType e)
{
 if(S.top - S.base >= S.stacksize)
 {
  S.base = (QElemType *)realloc(S.base,(S.stacksize + STACKINCREMENT) * sizeof(QElemType));
  if(!S.base) exit(0);
  S.top = S.base + S.stacksize;
  S.stacksize += STACKINCREMENT;
 }
 *S.top++ = e;
}
template <class QElemType>
int stack<QElemType>::Pop(QElemType & e)
{
 if(S.top == S.base) return 0;
 else
  e = * --S.top;
 return 1;
}
//**********stack.cpp
#endif     //stack.h ****

 

#include <iostream>
#include <string.h>
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
{ //1表示栈顶优先级高于待入栈的元素
 if(a == '(' && b == ')') return 0;
     else if((a == '+' && b == '*') || (a == '+' && b == '/')
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
 cout << "请输入算术表达式(例如:2 + 3 * ( 5 - 8 / 4 ) #," << endl;
  cout << "输入完毕后在末尾加上#,输入每条信息均加空格):" << endl;
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