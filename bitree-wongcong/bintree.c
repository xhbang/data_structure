#include "bintree.h"

extern p_btree_t btree_create(void){
	p_btree_t bintree;
	if((bintree=(p_btree_t)malloc(sizeof(btree_t)))==NULL){
		errno=ENOMEM;
		return NULL;
		}
	bintree->count=0;
	if((bintree->root=(p_btnode_t)malloc(sizeof(btnode_t)))==NULL){
		free(bintree);
		errno=ENOMEM;
		return NULL;
		}
	bintree->root->pdata=NULL;
	bintree->root->lchild=bintree->root->rchild=NULL;
	return bintree;
	}

extern int btree_insert(p_btree_t bintree,void* pnew_item,size_t n,int (*comp)(void*,void*)){
	register p_btnode_t this;
	p_btnode_t newnode;
	void *newp;

	if(bintree==NULL){
		errno=EINVAL;
		return -1;
		}
	newp=malloc(n);
	if(!newp){
		errno=ENOMEM;
		return -1;
		}
	this=bintree->root;
	if(bintree->count==0){
		memcpy(newp,pnew_item,n);
		bintree->root->pdata=newp;
	}else{
		for(;;){
			if(comp(pnew_item,this->pdata)>0){
				if(this->rchild==NULL){
					if((newnode=(p_btnode_t)malloc(sizeof(btnode_t)))==NULL){
						free(newp);
						errno=ENOMEM;
						return -1;
						}
					memcpy(newp,pnew_item,n);
					newnode->pdata=newp;
					newnode->lchild=newnode->rchild=NULL;
					this->rchild=newnode;
					break;
					}
				else this=this->rchild;
				}
			else if(comp(pnew_item,this->pdata)<0){
				if(this->lchild==NULL){
					if((newnode=(p_btnode_t)malloc(sizeof(btnode_t)))==NULL){
						free(newp);
						errno=ENOMEM;
						return -1;
						}
					memcpy(newp,pnew_item,n);
					newnode->pdata=newp;
					newnode->lchild=newnode->rchild=NULL;
					this->lchild=newnode;
					break;
					}
				else this=this->lchild;
				}
			else{ 
				free(newp);
				errno=EINVAL;
				return -1;
				}
			}
		}
	bintree->count++;
	return 0;
	}
	
extern p_btnode_t btree_search(p_btree_t bintree,void* pitem,int (*comp)(void*,void*)){/*When you use this funcion, you must be careful, because it is not easy to detect errors!*/
	register p_btnode_t this;

	if(bintree==NULL || bintree->count==0){
		errno=EINVAL;
		return NULL;
		}
	this=bintree->root;
	for(;;){
		if(comp(this->pdata,pitem)>0){
			this=this->lchild;
			if(this==NULL)return NULL;
			}
		else if(comp(this->pdata,pitem)<0){
			this=this->rchild;
			if(this==NULL)return NULL;
			}
		else break;
		}
	return this;
	}
	
static void post_trav(p_btnode_t this,int (*process)(void*)){
	if(this==NULL)return;
	post_trav(this->lchild,process);
	post_trav(this->rchild,process);
	(*process)(this);
	return;
	}
extern int btree_post_trav(p_btree_t bintree,int (*process)(void*)){
	if(bintree==NULL || process==NULL){
		errno=EINVAL;
		return -1;
		}
	post_trav(bintree->root,process);
	return 0;
	}
	
static void prev_trav(p_btnode_t this,int (*process)(void*)){
	if(this==NULL)return;
	(*process)(this);
	prev_trav(this->lchild,process);
	prev_trav(this->rchild,process);
	return;
	}
extern int btree_prev_trav(p_btree_t bintree,int (*process)(void*)){
	if(bintree==NULL || process==NULL){
		errno=EINVAL;
		return -1;
		}
	prev_trav(bintree->root,process);
	return 0;
	}
	
static void in_trav(p_btnode_t this,int (*process)(void*)){
	if(this==NULL)return;
	in_trav(this->lchild,process);
	(*process)(this);
	in_trav(this->rchild,process);
	return;
	}
extern int btree_in_trav(p_btree_t bintree,int (*process)(void*)){
	if(bintree==NULL || process==NULL){
		errno=EINVAL;
		return -1;
		}
	in_trav(bintree->root,process);
	return 0;
	}
	
static int isleaf(p_btnode_t node){
	if(node==NULL){
		errno=EINVAL;
		return -1;
		}/*Notice that when this function returns a none-zero value it may detects some error!!*/
	if(node->lchild==NULL && node->rchild==NULL)return 1;
	else return 0;
	}
extern int btree_delete(p_btree_t bintree,void* pitem,size_t n,int (*comp)(void*,void*)){
	register p_btnode_t this;
	p_btnode_t temp;
	void* tmp;
	
	if(bintree==NULL || bintree->count==0){
		errno=EINVAL;
		return -1;
		}
	this=bintree->root;
	for(;;){
		if(comp(pitem,this->pdata)<0){
			if(this->lchild==NULL){
				errno=EINVAL;
				return -1;
				}
			if(isleaf(this->lchild)==0)
				this=this->lchild;
			else if(isleaf(this->lchild)==-1)return -1;
			else{
				if(comp(this->lchild->pdata,pitem)==0){
					free(this->lchild->pdata);
					free(this->lchild);
					this->lchild=NULL;
					break;
					}
				else{
					errno=EINVAL;
					return -1;
					}
				}
			}
		else if(comp(pitem,this->pdata)>0){
			if(this->rchild==NULL){
				errno=EINVAL;
				return -1;
				}
			if(isleaf(this->rchild)==0)
				this=this->rchild;
			else if(isleaf(this->lchild)==-1)return -1;
			else{
				if(comp(this->rchild->pdata,pitem)==0){
					free(this->rchild->pdata);
					free(this->rchild);
					this->rchild=NULL;
					break;
					}
				else{
					errno=EINVAL;
					return -1;
					}
				}
			}
		else{
			tmp=malloc(n);
			if(!tmp){
				errno=ENOMEM;
				return -1;
				}
			if(this->rchild==NULL && this->lchild!=NULL){
				if(bintree->count==1){
					free(this->pdata);
					break;
					}
				temp=this;
				this=this->lchild;
				while(this->rchild!=NULL)
					this=this->rchild;/*find max*/
				memcpy(tmp,this->pdata,n);
				if(btree_delete(bintree,tmp,n,comp)==-1)return -1;/*Recursion*/
				temp->pdata=tmp;
				}
			else{
				if(bintree->count==1){
					free(this->pdata);
					break;
					}
				temp=this;
				this=this->rchild;
				while(this->lchild!=NULL)
					this=this->lchild;/*find min*/
				memcpy(tmp,this->pdata,n);
				if(btree_delete(bintree,tmp,n,comp)==-1)return -1;/*Recursion*/
				temp->pdata=tmp;
				}
			return 0;/*Here is NOT break!*/
			}		
		}
	bintree->count--;
	return 0;
	}
	
static p_btnode_t freenode(p_btnode_t this){
	if(this==NULL)return NULL;
	else if(isleaf(this)){
		free(this->pdata);
		free(this);
		return NULL;
		}
	else{
		this->lchild=freenode(this->lchild);
		this->rchild=freenode(this->rchild);
		}/*Yeah,when you compile this program, here will produce a warning. Omit it!*/
	}
extern void btree_destroy(p_btree_t bintree){
	freenode(bintree->root);
	free(bintree);
	}

