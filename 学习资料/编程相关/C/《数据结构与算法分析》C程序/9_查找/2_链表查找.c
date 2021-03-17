// 创建链表
#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    struct node *link;
}; // 结点结构
typedef struct node NODE;

NODE *create_link_list(int n) // n≥0为线性表长度
{
    int i;
    int a[] = {1, 2, 5, 3, 4, 6, 7, 8}; // XXX
    NODE *head, *p, *q;
    if (n <= 0)
        return (NULL);
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for (i = 1; i < n; i++) // 先处理 n-1个结点
    {                       // scanf("%c", &(p->data));  						// 输入表元素的内容
        p->data = a[i - 1]; // XXX

        q = (NODE *)malloc(sizeof(NODE));
        p->link = q; // 链入下一个结点
        p = q;       // p 指向表最后结点
    }

    // scanf (" %c",&(p->data) );							// 输入最后元素的数据
    p->data = a[i - 1]; // XXX

    p->link = NULL; // 置最后结点指针为空
                    //  getchar ( );										// 暂停
    return (head);  // 返回建成链表头指针
}

// 链表输出
print_link(NODE *head)
{
    NODE *p = head;
    while (p != NULL)
    {
        printf("  %d", p->data);
        p = p->link;
    }
    printf("\n");
}

// 链接存储的线性表的查找
NODE *seq_search_l(NODE *head, int v)
{
    while (head != NULL && head->data != v)
        head = head->link;
    return (head);
}

int main()
{
    NODE *head, *p;
    int v, n = 8;

    head = create_link_list(n);

    printf("链表查找\n线性表为：");
    print_link(head);

    printf("\n\n输入要查找的值：");
    scanf("%d", &v);

    p = seq_search_l(head, v);

    if (p)
        printf("\n找到要找的值 %d \n", p->data);
    else
        printf("\n%d 没找到\n", v);
}
