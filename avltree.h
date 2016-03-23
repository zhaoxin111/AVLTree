#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef int elementType;
typedef struct node
{
    elementType key;
    struct node *left;
    struct node *right;
    int height;//当前结点深度
} avlnode,*avltree;
int getNode_height(avlnode *node);//获取当前结点的深度

avlnode *create_node(elementType key,avlnode *left,avlnode *right);//创建结点

avlnode *  maximun_node(avltree tree);//求树中最大结点

avlnode *minimun_node(avltree tree);//求树中最小结点

avltree  avltree_insertNode(avltree tree,elementType key);//向树中插入结点

avltree  avltree_deleNode(avltree tree,elementType key);//删除结点

void pre_order_avltree(avltree tree);//前序遍历

void in_order_avltree(avltree tree);//中序遍历

void post_order_avltree(avltree tree);//后序遍历

void print_avltree(avltree tree, elementType key, int direction);//打印树的信息

avlnode *search_node(avltree tree,elementType key);//根据key 的值搜索结点

#endif // AVLTREE_H_INCLUDED
