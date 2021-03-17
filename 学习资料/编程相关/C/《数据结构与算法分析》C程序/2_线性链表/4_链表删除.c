#include <stdlib.h>
#include <stdio.h>

// 链表结点结构

typedef struct node
{
    int data;          // 视情况可扩展为多个域
    struct node *link; // 指针域
} NODE;

// 链表创建

NODE *create_link_list(int n) // n≥0为线性表长度
{
    int i;
    NODE *head, *p, *q;
    if (n <= 0)
        return (NULL);
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for (i = 1; i < n; i++) // 先处理 n-1个结点
    {
        printf("请输入第 %d 个元素(共 %d 个):", i, n);
        scanf("%d", &p->data); // 输入表元素的内容
        q = (NODE *)malloc(sizeof(NODE));
        p->link = q; // 链入下一个结点
        p = q;       // p 指向表最后结点
    }
    printf("请输入最后元素:");
    scanf(" %d", &(p->data)); // 输入最后元素的数据
    p->link = NULL;           // 置最后结点指针为空
    return (head);            // 返回建成链表头指针
}

// 链表输出

print_link(NODE *head)
{
    NODE *p = head;
    while (p != NULL)
    {
        printf(" %d", p->data);
        p = p->link;
    }
    printf("\n");
}

// 链表删除

int link_del(head, i)
    NODE **head; // head存头指针的地址
int i;           // i 为删除元素的位置
{
    int j;
    NODE *p, *q = *head;
    if (q == NULL)
        return (1); // 不能删 ⑴ 空链表
    if (i == 1)     //  可删 ① 删除头结点
    {
        *head = q->link; // 修改头指针
        free(q);         // 释放被删除结点的存储空间
        return (0);      // 删除成功返回 0
    }
    j = 1;
    p = *head;
    while (p->link != NULL && ++j < i) // 寻找删除的位置：
        p = p->link;                   //  (第i-1个结点的地址)

    if (i < 1 || j < i)
        return (2); // 不能删 ⑵  i 在不可删除位置上
    else            // 可删 ② 删除头结点外的结点
    {
        q = p->link;       // q 指向被删除结点
        p->link = q->link; // 修改指针
        free(q);           // 释放被删除结点的空间
        return (0);        // 删除成功返回 0
    }
}

int main()
{
    NODE *head;
    int m, n = 3, i = 5, x = 8;
    printf("\n请输入线性长度：");
    scanf("%d", &n);            // 输入线性表长度 n
    head = create_link_list(n); // 创建线性表

    printf("\n\n链接存储的线性表的删除\n\n线性表为：");
    print_link(head);

    printf("\n\n请输入删除位置: ");
    scanf("%d", &i); // 输入删除位置

    m = link_del(&head, i);

    if (m == 1)
        printf("list 为空不可删除!");
    else if (m == 2)
        printf("删除位置 %d 错误！", i);
    else
    {
        printf("\n删除成功!\n删除后的线性表为：");
        print_link(head); // 输出线性表
    }
    printf("\n\n");
}