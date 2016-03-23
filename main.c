#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#define LENGTH(a) ((sizeof(a))/(sizeof(a[0])))
int main()
{
    avltree tree=NULL;
    int a[]={3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    //int a[]={7,4,13,12,15,11};
    int length=LENGTH(a);
    for(int i=0;i<length;i++)
    {
        tree=avltree_insertNode(tree,a[i]);
    }


    int max_height=getNode_height(tree);
    printf("树高度为：%d\n",max_height);
    printf("前序遍历：");
    pre_order_avltree(tree);

    printf("\n");
    printf("中序遍历：");
    in_order_avltree(tree);
    printf("\n");
    printf("后序遍历：");
    post_order_avltree(tree);
    printf("\n");

    printf("min=%d\n",minimun_node(tree)->key);
    printf("max=%d\n",maximun_node(tree)->key);
    print_avltree(tree,tree->key,0);


    printf("删除结点\n");
    tree=avltree_deleNode(tree,6);
    print_avltree(tree,tree->key,0);
}
