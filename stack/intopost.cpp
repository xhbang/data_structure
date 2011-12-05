//中缀表达式转换为后缀表达式

#include <iostream>
#include <string>	//string,==,find,npos
#include <cassert>		//assert()
#include  <cctype> //isalnum() 
/*isalnum returns a non-zero value if either isalpha or isdigit is true for c, that is, if c is within the ranges A – Z, a – z, or 0 – 9. iswalnum returns a non-zero value if either iswalpha or iswdigit is true for c. Each of these routines returns 0 if c does not satisfy the test condition.
isalpha returns a non-zero value if c is within the ranges A – Z or a – z.
isdigit returns a non-zero value if c is a decimal digit (0 – 9). 
来自msdn
*/

#include "stack.h"
using namespace std;

string postfix(string exp);			//声明postfix的原型

int main(){
	string infixexp;
	while(1){
		cout<<"please enter a infix expression,# to quit\n";
		getline(cin,infixexp);
		
		if(infixexp=="#")
			break;
		cout<<"the postfix expression is:\n"<<postfix(infixexp)<<endl;

	}
}

//重头戏来的了
string postfix(string exp){
	char token,topToken;
	Stack opstack;		//操作符栈
	string postfixexp;			//后缀表达式
	const string BLANK = " ";		//定义空白
	for(string::size_type i=0;i < exp.size();i++){
		token=exp[i];
		switch (token){		//开始选择
			case  ' ':	break;
			case  '(':	opstack.push(token);
							break;
			case  ')':	for( ; ;){
								assert(!opstack.empty());
								topToken=opstack.top();
								opstack.pop();
								if(topToken=='(' )
									break;
								postfixexp.append(BLANK+topToken);
						}//for
			case '+': case '-':
			case '*': case '/' :case '%':
							for( ; ;){
								if(opstack.empty() || opstack.top()=='(' ||
									(token=='*' || token=='/' || token== '%')&& (opstack.top()=='+' || opstack.top() == '-')){
									opstack.push(token);
									break;
								}//if
								else{
									topToken=opstack.top();
									opstack.pop();
									postfixexp.append(BLANK+topToken);
								}//else
							}//for
							break;
			default:		postfixexp.append(BLANK+token);
							break;				//情况为操作数
			for(; ;){
				if(!isalnum(exp[i+1]))			//是数字或者字母则跳过
					break;
				token=exp[i];
				postfixexp.append(1,token);
			}//for
		}//switch
	}//for
		//弹出剩下的操作符
		for(; ;){
			if(opstack.empty())
				break;
			topToken=opstack.top();
			opstack.pop();
			if(token == '('){
				cout<<"error in infixexpression!\n";
				break;
			}
			else{
				postfixexp.append(BLANK+topToken);
			}
		}//for
	return postfixexp;
}//function