/*
ջ��Ӧ�úܹ㷺��ԭ��ֻ�����˱��ʽ��ֵ������Ҳ��ֻд��Щ��
����װ�����ݡ���
��ʵ��ջ��������;�ǽ���������⣬��Ҳ����������ݹ飻��������ջ��������������ϰ�ߵ�ʱ����ͺ����뵽�õݹ��ˣ������Թ���⡣���⣬�˵�ϰ��Ҳ������Ϊ���ģ��������ı�������ѧ�����쿪ʼ�����ǵݹ��㷨����Ȼ����Ҳ������ջʵ�ֵķ�������Ӧ�õ�ʱ���������뵽�Ļ��ǵݹ飻��Ȼ�ˣ�������Ա���֧�ֵݹ飨��BASIC������ջ����Ψһ��ѡ���ˡ����������ڵĸ߼����Զ���֧�ֵݹ�ġ�

�����Ǳ��ʽ��Ķ����ʵ�֣����ʽ��������׺��ʾҲ�����Ǻ�׺��ʾ����ͷ�ڵ����������type���֣�������һ��˵�����ǣ����ڵ�����ĸ�ֵ��������ԭ��д��ʱ��û�и���ͷ�ڵ�����ݣ����ԣ�Ҫ�����������ʽ֮�丳ֵ��ͷ�ڵ�������Ϣ�Ͷ��ˡ�����Ը�д������ĸ�ֵ����������������������������������������ʽ֮�丳ֵҲ�С�
*/
#ifndef Exdivssion_H
#define Exdivssion_H

#include "List.h"

#include "Stack.h"



#define INFIX 0

#define POSTFIX 1

#define OPND 4

#define OPTR 8



template <class Type> class ExpNode

{

public:

	int type;

	union { Type opnd; char optr;};

	ExpNode() : type(INFIX), optr('=') {}

	ExpNode(Type opnd) : type(OPND), opnd(opnd) {}

	ExpNode(char optr) : type(OPTR), optr(optr) {}

};



template <class Type> class Exdivssion : List<ExpNode<Type> >

{

public:

	void Input()

	{

		MakeEmpty(); Get()->type =INFIX;

		cout << endl << "������ʽ���ԣ���������" << endl;

		Type opnd; char optr = ' ';

		while (optr != '=')

		{

			cin >> opnd;

			if (opnd != 0)

			{

				ExpNode<Type> newopnd(opnd);

				LastInsert(newopnd);

			}

			cin >> optr;

			ExpNode<Type> newoptr(optr);

			LastInsert(newoptr);



		}

	}



	void Print()

	{

		First();

		cout << endl;

		for (ExpNode<Type> *p = Next(); p != NULL; p = Next() )

		{

			switch (p->type)

			{

			case OPND:

				cout << p->opnd; break;

			case OPTR:

				cout << p->optr; break;

			default: break;

			}

			cout << ' ';

		}

		cout << endl;

	}



	Exdivssion & Postfix() //����׺���ʽת��Ϊ��׺���ʽ

	{

		First();

		if (Get()->type == POSTFIX) return *this;

		Stack<char> s; s.Push('=');

		Exdivssion temp;

		ExpNode<Type> *p = Next();

		while (p != NULL)

		{

			switch (p->type)

			{

			case OPND:

				temp.LastInsert(*p); p = Next(); break;

			case OPTR:

				while (isp(s.GetTop()) > icp(p->optr) )

				{

					ExpNode<Type> newoptr(s.Pop());

					temp.LastInsert(newoptr);

				}

				if (isp(s.GetTop()) == icp(p->optr) )

				{

					s.Pop(); p =Next(); break;

				}

				s.Push(p->optr); p = Next(); break;

			default: break;

			}

		}

		*this = temp;

		pGetFirst()->data.type = POSTFIX;

		return *this;

	}



	Type Calculate()

	{

		Exdivssion temp = *this;

		if (pGetFirst()->data.type != POSTFIX) temp.Postfix();

		Stack<Type> s; Type left, right;

		for (ExpNode<Type> *p = temp.Next(); p != NULL; p = temp.Next())

		{

			switch (p->type)

			{

			case OPND:

				s.Push(p->opnd); break;

			case OPTR:

				right = s.Pop(); left = s.Pop();

				switch (p->optr)

				{

				case '+': s.Push(left + right); break;

				case '-': s.Push(left - right); break;

				case '*': s.Push(left * right); break;

				case '/': if (right != 0) s.Push(left/right); else return 0; break;

					//                          case '%': if (right != 0) s.Push(left%right); else return 0; break;

					//                          case '^': s.Push(Power(left, right)); break;

				default: break;

				}

			default: break;

			}

		}

		return s.Pop();

	}



private:

	int isp(char optr)

	{

		switch (optr)

		{

		case '=': return 0;

		case '(': return 1;

		case '^': return 7;

		case '*': return 5;

		case '/': return 5;

		case '%': return 5;

		case '+': return 3;

		case '-': return 3;

		case ')': return 8;

		default: return 0;

		}

	}



	int icp(char optr)

	{

		switch (optr)

		{

		case '=': return 0;

		case '(': return 8;

		case '^': return 6;

		case '*': return 4;

		case '/': return 4;

		case '%': return 4;

		case '+': return 2;

		case '-': return 2;

		case ')': return 1;

		default: return 0;

		}

	}


};



#endif
/*
����˵��

l         ���ʽ�õ������棬����Կ�����������м��в��������в�����������㿴���ҵġ������һ�����������벻ͬ���͵Ķ��󡷣�����ķ���Ҳ�Ƕ���ƪ���µĲ��䡣

l         ������ʽʱ���Ὣԭ����������գ����ұ��밴����׺��ʾ���롣�����ϸ��һ����׺���ʽ����ͻᷢ�֣��������ţ����ʽ�Ľṹ�ǡ���������������������������������������������������������Ϊ��ͳһ������ɣ�ͬʱҲΪ��ʹ���뺯����һ�㣬�涨���ű����������롰0����������0��������һ������0���Ͳ�����Ϊ�����������ڱ��ʽ���ˡ���Ϊ��û�������뺯���������ݴ����䣬����һ������ˣ��ǳ���͡������ˡ�

l         ���ʽ��ֵ�Ĺ����ǣ��ȱ�ɺ�׺��ʾ��Ȼ���ú�׺��ʾ��ֵ����Ϊԭ�齲������������㷨���������������㷨���������׺���ʽ����ֵ�������Ҿ�ûд��׺���ʽ��ֱ����ֵ�㷨�������㷨˵���μ�ԭ�飬�ҾͲ��ϻ��ˡ�

l         Calculate()ע�͵������У�����������Ϊֻ�����ͱ��ʽ�Ϸ�����^����Power()����û����ɡ�

l         isp()��icp()�ķ���ֵ��ԭ��˵�Ĳ�ϸ��������˵���䡣�����������ʽ��ʼ�ͽ�����־����ջ��ջ�����ȼ�������͡�������ջ����ߣ�ջ�ڴ���͡�������ջ�����ͣ�����ջ����^��ջ�ڴ���ߣ�ջ���ջ�ڵ͡������£���ջ�ڱȡ�^��ջ��ͣ�ջ���ջ�ڵ͡���������ջ�ڱȡ�����ջ��ͣ�ջ���ջ�ڵ͡��������ۺ�����������9�����ȼ������Ǿ͵ó������ϵ��Ǹ���

*/