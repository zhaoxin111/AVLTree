#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef int elementType;
typedef struct node
{
    elementType key;
    struct node *left;
    struct node *right;
    int height;//��ǰ������
} avlnode,*avltree;
int getNode_height(avlnode *node);//��ȡ��ǰ�������

avlnode *create_node(elementType key,avlnode *left,avlnode *right);//�������

avlnode *  maximun_node(avltree tree);//�����������

avlnode *minimun_node(avltree tree);//��������С���

avltree  avltree_insertNode(avltree tree,elementType key);//�����в�����

avltree  avltree_deleNode(avltree tree,elementType key);//ɾ�����

void pre_order_avltree(avltree tree);//ǰ�����

void in_order_avltree(avltree tree);//�������

void post_order_avltree(avltree tree);//�������

void print_avltree(avltree tree, elementType key, int direction);//��ӡ������Ϣ

avlnode *search_node(avltree tree,elementType key);//����key ��ֵ�������

#endif // AVLTREE_H_INCLUDED
