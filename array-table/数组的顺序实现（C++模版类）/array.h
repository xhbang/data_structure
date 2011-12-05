/*//////////////////////////////////////////////////////////////////////////////
// ��    �� (Unit Name)  :    ����Array.h ͷ�ļ�
// ��    �� (Author)     :    Hector(��ΰ)
// ��    �� (E-mail)     :    ourys@qq.com
// ֧    �� (Support)    :    http://www.ourys.com           
// ��    ע (Remarks)    :    ����<stdarg.h>�ɱ������ͷ�ļ����գ�http://www.ourys.com/post/56.html
//////////////////////////////////////////////////////////////////////////////*/
#ifndef _ARRAY_H
#define _ARRAY_H
#include<stdarg.h>         //�ɱ������ͷ�ļ�
#define MAX_ARRAY_DIM 8    //����Ԫ�����ά��
template <class DataType>
class Array{
public:
	Array(int _dim,...);                //����_dimά����
	~Array();                           //��������
	bool Locate(va_list ap,int &off);   //�����Ԫ����A�е���Ե�ַoff
	bool Value(DataType* e,...);        //e����ֵΪ�������ӦԪ�أ�stdarg.h���ܴ����ã������ô���ַ����ʽ��
	bool Assign(DataType e,...);        //��e��ֵΪ�������Ӧ��Ԫ��ֵ
private:
	DataType* base;      //����Ԫ�ػ�ַ
	int dim;             //����ά��
	int* bounds;         //����ά���ַ
	int* constants;      //����ӳ����������ַ

};
/*------------  ���캯��������_dimά����  --------------*/
template <class DataType>
Array<DataType>::Array(int _dim,...)
{
	int elemtotal=1,i;
	va_list ap;
	if(_dim<1||_dim>MAX_ARRAY_DIM) exit(1);
	dim=_dim;
	if(!(bounds=(int*)malloc(dim*sizeof(int)))) exit(1);
	va_start(ap,_dim);
	for(i=0;i<dim;++i){
		bounds[i]=va_arg(ap,int);   //�Ѹ�ά�ĳ��ȸ�ֵ��bounds[dim]
		if(bounds[i]<0) exit(1);    //���ά�ĳ���Ϊ0����
		elemtotal*=bounds[i];      //elemtotal ΪԪ���ܸ���
	}
	va_end(ap);                  //���ֽ�׳��
	if(!(base=(DataType*)malloc(elemtotal*sizeof(DataType)))) exit(1);
	if(!(constants=(int*)malloc(dim*sizeof(int)))) exit(1);
	constants[dim-1]=1;
	for(i=dim-2;i>=0;--i) constants[i]=bounds[i+1]*constants[i+1];
}
/*------------  ��������  --------------*/
template <class DataType>
Array<DataType>::~Array()
{
	if(base) free(base);
	if(bounds) free(bounds);
	if(constants) free(constants);
	bounds=constants=NULL;
	base=NULL;
	dim=0;
}
/*------------  �����Ԫ����A�е���Ե�ַoff  --------------*/
template <class DataType>
bool Array<DataType>::Locate(va_list ap, int &off)
{
	int ind;
	for(int i=0;i<dim;++i)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=bounds[i]) exit(1);
		off+=constants[i]*ind;
	}
	va_end(ap);
	return true;
}
/*------------  e����ֵΪ�������ӦԪ��  --------------*/
template <class DataType>
bool Array<DataType>::Value(DataType* e, ...)
{
	va_list ap;
	int off=0;
	va_start(ap,e);
	if(!Locate(ap,off)) return false;
	*e=*(base+off);
	return true;
}
/*------------  ��e��ֵΪ�������Ӧ��Ԫ��ֵ  --------------*/
template <class DataType>
bool Array<DataType>::Assign(DataType e, ...)
{
	va_list ap;
	int off=0;
	va_start(ap,e);
	if(!Locate(ap,off)) return false;
	*(base+off)=e;
	return true;
}

#endif

