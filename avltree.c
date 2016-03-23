#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define HEIGHT(node) ((node==NULL) ? 0 :(((avlnode *)(node))->height))
#define MAX(a,b) ((a)>(b)?(a):(b))

int getNode_height(avlnode *node)
{
    return HEIGHT(node);
}

avlnode *create_node(elementType key,avlnode *left,avlnode *right)
{
    avlnode *node=(avlnode *)malloc(sizeof(avlnode));
    if(node==NULL)
    {
        printf("�������ʧ��");
        return NULL;
    }
    node->key=key;
    node->left=left;
    node->right=right;
    node->height=0;

    return node;
}

avlnode *  maximun_node(avltree tree)
{
    if(tree==NULL)
        return NULL;
    while(tree->right)
        tree=tree->right;
    return tree;
}

avlnode *minimun_node(avltree tree)
{
    if(tree==NULL)
        return NULL;
    while(tree->left)
        tree=tree->left;

    return tree;
}

void pre_order_avltree(avltree tree)
{
    if(tree)
    {
        printf("%d    ",tree->key);
        pre_order_avltree(tree->left);
        pre_order_avltree(tree->right);
    }
}

void in_order_avltree(avltree tree)
{
    if(tree)
    {
        in_order_avltree(tree->left);
        printf("%d    ",tree->key);
        in_order_avltree(tree->right);

    }
}

void post_order_avltree(avltree tree)
{
    if(tree)
    {
        post_order_avltree(tree->left);
        post_order_avltree(tree->right);
        printf("%d    ",tree->key);

    }
}
/*LL��ת
                               k1                                                  k2
                             /      \                                               /   \
                          k2       K3                                          k4    k1
                        /   \               -------->                        /       / \
                      k4    k5                                              k6     k5 k3
                     /
                 k6

*/
static avltree left_left_rotation(avltree tree)
{
    avlnode *k2=tree->left;
    tree->left=k2->right;
    k2->right=tree;
    //���������м�������ת������Ҫ���µ������ĸ߶�
    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    k2->height=MAX(getNode_height(k2->left),getNode_height(k2->right))+1;
    return k2;
}

/*RR��ת
                          k1                                                       k3
                        /    \                                                    /    \
                      k2     k3                                               k1     k5
                            /     \              -------->                 /   \       \
                           k4     k5                                      k2     k4     k6
                                      \
                                       k6



*/
static avltree right_right_rotation(avltree tree)
{
    avlnode *k3=tree->right;
    tree->right=k3->left;
    k3->left=tree;
    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    k3->height=MAX(getNode_height(k3->left),getNode_height(k3->right))+1;
    return k3;
}

/*LR��ת
                          k1                                                 k1                                                k5
                        /     \                                             /    \                                             /    \
                      k2      k3                                       k5     k3                                         k2     k1
                    /    \           -------->                      /    \           --------->                       /      /   \
                 k4      k5                                        k2      k6                                          k4      k6   k3
                            \                                         /
                             k6                                     k4
      1.��k2��RR��ת
      2.��k1��LL��ת
*/
static avltree left_right_rotation(avltree tree)
{
    tree->left=right_right_rotation(tree->left);
    tree=left_left_rotation(tree);
    return tree;
}

/*RL��ת
                                  k1                                          k1                                              k4
                                /    \                                       /    \                                           /     \
                              k2     k3                                 k2      k4                                      k1     k3
                                     /    \    ---------->                    /   \    ---------->               /    \       \
                                    k4    k5                                  k6    k3                              k2     k6     k5
                                    /                                                      \
                                  k6                                                       k5
            1.��k3��LL��ת
            2.��k1��RR��ת
*/
static avltree right_left_rotation(avltree tree)
{
    tree->right=left_left_rotation(tree->right);
    tree=right_right_rotation(tree);
    return tree;
}

/*
    ������������ƶ�����������������avlҪ�ڲ����½���֤����ƽ����
 */
avltree  avltree_insertNode(avltree tree,elementType key)
{
    if(tree==NULL)
    {
        avlnode *node=create_node(key,NULL,NULL);

        tree=node;

    }
    else if(key<tree->key)//���������в�����
    {
        tree->left=avltree_insertNode(tree->left,key);//�ݹ�Ѱ�Ҳ���ڵ��λ��

        //����ڵ���������������Ĳ�ƽ�⣬����Ҫ�ڴ˽����ж�
        if(HEIGHT(tree->left)-HEIGHT(tree->right)==2)
        {
            //������ж���LL����LR
            if(key<tree->left->key)
            {
                //LL��ת
                tree= left_left_rotation(tree);

            }
            else
            {
                //LR��ת
                tree=left_right_rotation(tree);
            }
        }
    }
    else if(key>tree->key)//���������в�����
    {
        tree->right=avltree_insertNode(tree->right,key);
        if(getNode_height(tree->right)-getNode_height(tree->left)==2)
        {
            //RR��ת
            if(key>tree->right->key)
            {
                tree= right_right_rotation(tree);
            }
            else
            {
                //RL��ת
                tree=right_left_rotation(tree);
            }
        }
    }
    else
    {
        printf("�����������ֵͬ���");

    }
    //���������µ��������������
    tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;

    return tree;
}

/*
 * ��ӡ"AVL��"
 *
 * tree       -- AVL���Ľڵ�
 * key        -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
void print_avltree(avltree tree, elementType key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree�Ǹ��ڵ�
            printf("%2d is root\n", tree->key, key);
        else                // tree�Ƿ�֧�ڵ�
            printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

        print_avltree(tree->left, tree->key, -1);
        print_avltree(tree->right,tree->key,  1);
    }
}

avlnode *search_node(avltree tree,elementType key)
{
    if(tree==NULL||tree->key==key)
    {
        return tree;
    }
    else if(key<tree->key)
    {
        search_node(tree->left,key);
    }
    else
    {
        search_node(tree->right,key);
    }
}
/*
ɾ��avl�еĽ��  ------ ɾ�����Ͷ����������Ĳ������ƣ����ؼ���ά������ƽ����
*/
avltree  avltree_deleNode(avltree tree,elementType key)
{
    avlnode *node =search_node(tree,key);
    if(tree==NULL||node==NULL)
    {
        return tree;
    }
    if(key<tree->key)//Ҫɾ���Ľ����������
    {   //�ݹ��ҵ�Ҫɾ���Ľ��
        tree->left= avltree_deleNode(tree->left,key);
        //ɾ���Ҫ���ƽ����
        if(getNode_height(tree->right)-getNode_height(tree->left)==2)
        {
            if(key<tree->right->key)
            {
                tree=right_left_rotation(tree);//RL��ת
            }
            else
            {
                tree=right_right_rotation(tree);//RL��ת
            }
        }
    }
    else if(key>tree->key) //Ҫɾ���Ľ����������
    {
        tree->right= avltree_deleNode(tree->right,key);
        if(getNode_height(tree->left)-getNode_height(tree->right)==2)
        {
            if(key<tree->left->key)
            {
                tree=left_left_rotation(tree);//LL��ת
            }
            else
            {
                tree=left_right_rotation(tree);//LR��ת
            }

        }
    }
    else //�ҵ�Ҫɾ���Ľ��
    {
        /*���Ҫɾ���Ľ�����������ӣ�ɾ������ͬ����������������������С��㸳ֵ����ǰ��㣬
        ��ɾ����С��㣬������֤�˶������������ԣ����������۶�������ƽ����*/
        if(tree->left&&tree->right)
        {
            avlnode *min_node=minimun_node(tree->right);
            tree->key=min_node->key;
            tree->right= avltree_deleNode(tree->right,min_node);

        }
        else
        {
            tree=tree->left?tree->left:tree->right;//���ӻ����������ɾ�����ͬ����������
        }
    }
    if(tree)
        tree->height=MAX(getNode_height(tree->left),getNode_height(tree->right))+1;
    return tree;
}


