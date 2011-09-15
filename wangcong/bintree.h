#ifndef _BIN_TREE_H
#define _BIN_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


/************************************************************
 *This header provides a set of functions that operating binary trees.
 *Author: Cong Wang
 *Date: 2005-05-20
 *Last Update: 2005-11-16
 *Version: 1.1
 *Notice that it is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *See the GNU General Public License for more details.
 *Report bugs to xiyou.wangcong@gmail.com .
 ************************************************************/

typedef struct bin_tree_node{
	void* pdata;
	struct bin_tree_node* lchild;
	struct bin_tree_node* rchild;
	}btnode_t;
typedef btnode_t* p_btnode_t;
typedef struct bin_tree{
	p_btnode_t root;
	int count;
	}btree_t;
typedef btree_t* p_btree_t;

extern p_btree_t btree_create(void);
extern int btree_insert(p_btree_t,void*,size_t,int (*)(void*,void*));
extern int btree_delete(p_btree_t,void*,size_t,int (*)(void*,void*));
extern int btree_post_trav(p_btree_t,int (*)(void*));
extern int btree_prev_trav(p_btree_t,int (*)(void*));
extern int btree_in_trav(p_btree_t,int (*)(void*));
extern p_btnode_t btree_search(p_btree_t,void*,int (*)(void*,void*));
extern void btree_destroy(p_btree_t);
extern int errno;

#endif
