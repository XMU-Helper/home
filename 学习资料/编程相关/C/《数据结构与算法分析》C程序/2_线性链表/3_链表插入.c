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

// 链表插入

int link_ins(head, i, x)
    NODE **head; // head为存放头指针的地址
int i, x;        // i 为插入位置,x为插入元素的值
{
    int j;
    NODE *p, *q;
    q = (NODE *)malloc(sizeof(NODE)); // 要插入的新结点
    q->data = x;
    if (i == 1) // ① 插入在第一个结点之前
    {
        q->link = *head;
        *head = q;  // 以上两个语句的顺序不能对调
        return (0); // 插入成功返回0
    }
    p = *head;
    j = 1;
    while (++j < i && p->link != NULL) // 寻找插入的位置
        p = p->link;                   // 即第 i-1个结点的地址
    if (i < 1 || j < i)
        return (1); // ② i 在不可以插入的位置上
    else            // ③ 插入在任一个结点之
    {
        q->link = p->link; // 以下两句的顺序不能对调
        p->link = q;
        return (0);
    }
}

int main()
{
    NODE *head;
    int m, n, i, x = 0;

    printf("\n请输入线性表长度：");
    scanf("%d", &n);            // 输入线性表长度 n
    head = create_link_list(n); // 创建线性表

    printf("\n链接存储的线性表的插入\n\n线性表为：");
    print_link(head);

    printf("\n\n请输入 (插入位置，插入元素):");
    scanf("%d,%d", &i, &x); // 输入插入位置和插入元素

    m = link_ins(&head, i, x);

    if (m == 1)
        printf("插入位置 %d 错误!\n", i);
    else
    {
        printf("\n插入成功!\n插入后的线性表为：");
        print_link(head); // 输出线性表
    }
    printf("\n");
}
