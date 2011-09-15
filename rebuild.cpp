/* filename:rebuild.cpp
 * author:hang@sonix
 * date:14 Sep 2011
 * g++ (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2
 */

/* README
 * usage:rebuild the binary tree using the pre-order trav string,togethter with in-order
 * careful:make sure the input is right
*/

#include <stdio.h>
#include <stack>

using namespace std;

struct Node{
    char val;
    Node *left, *right;
};

#define nn  6
// Node ** is right

void rebuild(char * pre_string, char * in_string, int len, Node ** root);

void pre_trav(Node *t){
    if(t){
        printf("%c ",t->val);
        pre_trav(t->left);
        pre_trav(t->right);                                       
    }
}

void in_trav(Node *t){
    if(t){
        in_trav(t->left);
        printf("%c ",t->val);
        in_trav(t->right);                                       
    }
}


void post_trav(Node *t){
    if(t){
        post_trav(t->left);
        post_trav(t->right);                                       
        printf("%c ",t->val);
    }
}

void in_trav_stack(Node *t);

int main(){
    char pre[nn] = {'a','b','d','c','e','f'};
    //char in[nn] = {'d','b','a','e','c','f'};
    char in[nn] = {'d','b','a','e','c','f'};
    //do not use char * here
    //sample input
    Node * root = NULL;

    rebuild(pre, in, nn, &root);
    //remember &

    //reverse test
    printf("pre order trav:\n");
    pre_trav(root);
    printf("\n");

    printf("\nin order trav:\n");
    in_trav(root);
    printf("\n");

    printf("\npost order trav:\n");
    post_trav(root);
    printf("\n");
    /*
    printf("\nin order trav stack version:\n");
    in_trav_stack(root);
    */
    return 0;
}


void rebuild(char * pre_string, char * in_string, int len, Node ** root){
    //i got the idea from <beauty of programming>
    //i didn't change it much,for practice only
    //new Node
    Node * first = new Node;
    //do not use Node()
    first->val = *pre_string;
    first->left = NULL;
    first->right = NULL;

    //check
    if( pre_string == NULL && in_string == NULL){
        return;
    }

    //check again,remember * root
    if(*root == NULL){
        *root = first;
    }

    //check return
    if(len == 1)
        return;

    //most important parts,handle the string

    //mark the left tree
    char *boundry = in_string;

    while(*pre_string != *boundry){
        if( boundry == NULL || pre_string == NULL)
            return;
        boundry++;
        //check
        if(boundry > in_string + len){
            printf("please recheck your input\n");
            break;
        }
    }

    int llen = 0, rlen = 0;
    llen = (int)(boundry - in_string);
    rlen = len - llen - 1;

    if(llen > 0)
        rebuild(pre_string + 1, in_string, llen, &((*root)->left));
    //be careful with last parm
    if(rlen > 0)
        rebuild(pre_string + llen + 1, in_string + llen + 1, rlen, &((*root)->right));
}

void in_trav_stack(Node *t){
    stack<Node> s;
    Node *p = t;

    while(p || !s.empty()){
        if(p){
            //printf("%c",p->val);
            s.push(*p);
            p = p->left;
        }
        else{
            *p = s.top();
            s.pop();
            printf("%c",p->val);
            p = p->right;
        }
    }

}
