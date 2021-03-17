#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} NODE;

void insert(NODE **t, NODE *s)
{
    if (*t == NULL)
        *t = s;
    else
    {
        if (s->data < (*t)->data)
            insert(&((*t)->lchild), s);
        else if (s->data > (*t)->data)
            insert(&((*t)->rchild), s);
        else
            printf("\n数据%d已在二叉排序树中!", s->data);
    }
}

void creat(NODE **t)
{
    int x;
    NODE *s;
    printf("\n 输入待排序的数据序列(以-1结束):\n");
    scanf("%d", &x);
    while (x != -1) // 以-1结束输入
    {
        s = (NODE *)malloc(sizeof(NODE));
        s->data = x;
        s->lchild = NULL;
        s->rchild = NULL;
        insert(t, s); // 插入到二叉排序树中
        scanf("%d", &x);
    }
}

void midorder(NODE *t)
{
    if (t != NULL)
    {
        midorder(t->lchild);
        printf("%d ", t->data);
        midorder(t->rchild);
    }
}

int main()
{
    NODE *root = NULL;
    printf("\n 创建一棵二叉排序树！");
    creat(&root);
    printf("二叉排序树中序序列为：");
    midorder(root);
    putchar('\n');
}
