/******************************************************************
stack：动态分配实现方法

******************************************************************/


#ifndef STACK_H
#define STACK_H

#include <iostream>

typedef int ElemType;

class Stack{
public:
	Stack(int firstSize=100);
	Stack(const Stack& original);
	const Stack& operator=(const Stack &right);
	~Stack();
	void pop();
	bool empty() const;	
	void push(const ElemType &value);
	void display(std::ostream &out) const;
	ElemType top() const;

private:
	ElemType* myArray;
	int itop,icapacity;
};

#endif