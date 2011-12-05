/******************************************************************
stack����̬����ʵ�ַ���

******************************************************************/


#ifndef STACK_H
#define STACK_H

#include <iostream>

const int STACK_SIZE=100;
typedef int ElemType;

class Stack{
public:
	Stack();
	void pop();
	bool empty() const;		//���const��ʲô��˼
	void push(const ElemType &value);
	void display(std::ostream &out) const;
	ElemType top() const;

private:
	ElemType myArray[STACK_SIZE];
	int ptop;
};

#endif