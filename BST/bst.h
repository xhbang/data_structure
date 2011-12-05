#include <iostream>
//#include <iomapip>		//set

using namespace std;

#ifndef BST_TREE_H
#define BST_TREE_H

template <typename DataType>
class BST{

	BST();
	bool empty() const;		//是否为空
	void inorder(ostream &out) const;
	bool search(const DataType &item) const;
//	void graph(ostream &out) const;

private:


//----------------------------------------节点类型
	class BinNode{
	public:							
		DataType data;
		BinNode *left;
		BinNode *right;

		BinNode():left(0),right(0)	{};		//两种构造函数，分别对应有无数据
		BinNode(DataType item=0):data(item),left(0),right(0)	{};		//記得大括號
	};
//------------------------------------------
	typedef BinNode*  pBinNode;
	pBinNode myroot;

	void inorderAux(ostream &out,BST<DataType>::pBinNode subtree) const;		//inorder的辅助函数
//	void graphAux(ostream &out,int indent,BST<DataType>::pBinNode subtree) const;
	bool  searchAux(const DataType &item,BST<DataType>::pBinNode) const;
	void insert(const DataType& item);
//删除，还未写

};
template <typename DataType>
inline BST<DataType>::BST():myroot(0);
{}

template <typename DataType>
inline bool BST<DataType>::empty() const{
	return myroot==0;
}

template <typename DataType>												//转移辅助函数,中序遍历binTreeObj.inorder(argument list)
inline void BST<DataType>::inorder(ostream &out) const{
	inorderAux(out,myroot);
}

template <typename DataType>												//开始定义,inorderAux(parameter_list,pointer)
void BST<DataType>::inorderAux(ostream &out,BST<DataType>::pBinNode subtree) const{	
	if(subtree !=0){
		inorderAux(out,subtree->left);
		out<<subtree->data<<endl;
		inorderAux(out,subtree->right);
	}
}

/*图形化输出部分暂时不管
template <typename DataType>
inline void BST<DataType>::graph(ostream &out) const{
	graphAux(out,0,myroot);
}

template <typename  DataType>		//图形化输出
void BST<DataType>::graphAux(ostream &out,int indent,BST<DataType>::pBinNode subtree) const{
	if(subtree!=0){
		graphAux(out,indent+8,subtree->right);
		out<<setw(indent)<<" "<<subtree->data<<endl;
		graphAux(out,indent+8,subtree->left);
	}
}
*/

//查找，非递归和递归
template <typename DataType>
inline bool BST<DataType>::search(const DataType &item) const{
	searchAux(item,myroot);
} 

template <typename DataTaype>
boo BST<DataType>::searchAux(const DataType& item,BST<DataType>::pBinNode subtree){
	if(subtree==0)
		return false;
	else if(subtree->data >item)
		return searchAux(item,subtree->left);
	else if(subtree->data <item)
		return searchAux(item,subtree->right);
	else 
		return true;		//所以都检查过去了，找到！
}

/*非递归方法，
template <typename DataType>
bool BST<DataType>::search(const DataType & item) const{
	pBinNode current=myroot;
	bool found=0;
	while(!found && current!=0){
		if(item<current->data)
			current=current->left;
		else if(item > current->data)
			current=current->right;
		else
			found=true;
	}
	return found;
}
*/

template <typename DataType>
void BST<DataType>::search(const DataType &item){
	pBinNode current=myroot,parent=0;
	bool found=false;
	while(!found && current!=0){
		parent=current;
		if(item<current->data)
			current=current->left;
		else if(item> current->data)
			current=current->right;
		else 
			found=true;
	}
	if(found){
		current= new BST<DataType>::BinNode(item);
		if(parent==0)
			myroot=current;		//对应上述current 为NULL
		else if(item<parent->data)
			parent->left=current;
		else if(item>parent->data)
			parent->right=current;
	}
	else{
		cout<<"This item is already in the BST"<<endl;
	}
}


/*插入的递归版本
template <DataType>
void BST<DataType>::insert(const DataType &item){
	insertAux(item,myroot);
}

void BST<DataType>::insertAux(const DataType &item,BST<DataType>::pBinNode & subtree){
	if(subtree==0)		//空树
		subtree=new BST<DataType>::BinNode(item);
	else if(item<subtree->data)
		searchAux(item,subtree->left);
	else if(item>subtree->data)
		seatchAux(item,subtree->right);
	else
		cerr<<"Already find the item in the BST"<<endl;
}
*/

#endif
