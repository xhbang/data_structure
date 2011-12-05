/*//////////////////////////////////////////////////////////////////////////////
// 名    称 (Unit Name)  :    数组Array.h 头文件
// 作    者 (Author)     :    Hector(张伟)
// 邮    箱 (E-mail)     :    ourys@qq.com
// 支    持 (Support)    :    http://www.ourys.com           
// 备    注 (Remarks)    :    关于<stdarg.h>可变参数的头文件参照：http://www.ourys.com/post/56.html
//////////////////////////////////////////////////////////////////////////////*/
#ifndef _ARRAY_H
#define _ARRAY_H
#include<stdarg.h>         //可变参数的头文件
#define MAX_ARRAY_DIM 8    //数组元素最大维数
template <class DataType>
class Array{
public:
	Array(int _dim,...);                //构造_dim维数组
	~Array();                           //销毁数组
	bool Locate(va_list ap,int &off);   //求出该元素在A中的相对地址off
	bool Value(DataType* e,...);        //e被赋值为数组的相应元素（stdarg.h不能传引用，所以用传地址的形式）
	bool Assign(DataType e,...);        //将e赋值为数组的相应的元素值
private:
	DataType* base;      //数组元素基址
	int dim;             //数组维数
	int* bounds;         //数组维界基址
	int* constants;      //数组映像函数常量基址

};
/*------------  构造函数，构造_dim维数组  --------------*/
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
		bounds[i]=va_arg(ap,int);   //把各维的长度赋值给bounds[dim]
		if(bounds[i]<0) exit(1);    //如果维的长度为0错误
		elemtotal*=bounds[i];      //elemtotal 为元素总个数
	}
	va_end(ap);                  //保持健壮性
	if(!(base=(DataType*)malloc(elemtotal*sizeof(DataType)))) exit(1);
	if(!(constants=(int*)malloc(dim*sizeof(int)))) exit(1);
	constants[dim-1]=1;
	for(i=dim-2;i>=0;--i) constants[i]=bounds[i+1]*constants[i+1];
}
/*------------  销毁数组  --------------*/
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
/*------------  求出该元素在A中的相对地址off  --------------*/
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
/*------------  e被赋值为数组的相应元素  --------------*/
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
/*------------  将e赋值为数组的相应的元素值  --------------*/
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

