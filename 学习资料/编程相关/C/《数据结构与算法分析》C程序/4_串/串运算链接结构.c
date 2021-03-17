#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;         // 视情况可扩展为多个域
    struct node *link; // 指针域
} NODE;

// 创建链表
NODE *create_link_list(int n, char a[]) // n≥0为线性表长度
{
    int i;
    NODE *head, *p, *q;
    if (n <= 0)
        return (NULL);
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for (i = 1; i < n; i++) // 先处理 n-1个结点
    {
        p->data = a[i - 1]; // scanf("%c",&(p->data)); 		// 输入表元素的内容
        q = (NODE *)malloc(sizeof(NODE));
        p->link = q; // 链入下一个结点
        p = q;       // p 指向表最后结点
    }
    p->data = a[i - 1]; //scanf (" %c",&(p->data) );		// 输入最后元素的数据
    p->link = NULL;     // 置最后结点指针为空
    return (head);      // 返回建成链表头指针
}

// 输出链表
void prn_link(NODE *hd)
{
    NODE *p = hd;
    while (p)
    {
        printf("%c", p->data);
        p = p->link;
    }
    printf("\n");
}

// 1. 求串长度
int L_strlen(NODE *s)
{
    NODE *p = s;
    int i;
    for (i = 0; p != NULL; i++)
        p = p->link;
    return (i); // 返回串长度
}

// 2. 串比较
int L_strcmp(NODE *s1, NODE *s2)
{
    NODE *p1 = s1, *p2 = s2;
    while (p1 != NULL && p2 != NULL && p1->data == p2->data)
    {
        p1 = p1->link;
        p2 = p2->link;
    }
    if (p1 == NULL && p2 == NULL)
        return (0);
    else if (p1 == NULL)
        return (-1);
    else if (p2 == NULL)
        return (1);
    else
        return (p1->data - p2->data);
}

// 3. 串连接
void L_strcat(NODE **s1, NODE *s2)
{
    NODE *p1;
    if (*s1 == NULL)
        *s1 = s2;
    else
    {
        p1 = *s1;
        while (p1->link != NULL)
            p1 = p1->link;
        p1->link = s2;
    }
}

// 4. 求子串
int L_strsub(NODE *s1, int i, int k, NODE **s2)
{
    NODE *p, *q, *r;
    int m = L_strlen(s1);
    if (i < 1 || i > m)
        return (1); // 位置 i 超界
    if (k < 0 || i + k > m + 1)
        return (1); // 子串太长
    if (k == 0)
        (*s2) = NULL;
    else
    {
        p = s1;
        for (m = 1; m < i; m++)
            p = p->link;
        q = (NODE *)malloc(sizeof(NODE)); // 第一个结点
        q->data = p->data;
        (*s2) = q;
        r = q;
        for (m = 1; m < k; m++)
        {
            p = p->link;
            q = (NODE *)malloc(sizeof(NODE));
            q->data = p->data;
            r->link = q;
            r = q;
        }
        r->link = NULL;
    }
    return (0); // 操作成功
}

// 5. 串插入
int L_strins(NODE **s1, int i, NODE *s2)
{
    NODE *p, *q, *r;
    int m;
    r = s2; // 找串 s2 最后的结点，由 r 指出
    if (r != NULL)
        while (r->link != NULL)
            r = r->link;
    if (i == 1)
    {
        if (s2 != NULL) // 在串 s1 的第一个结点前插入
        {
            r->link = (*s1);
            (*s1) = s2;
        }
    }
    else // 找 s 1的插入位置(第i个结点)

    {
        q = (*s1);
        m = 1;
        while (q != NULL && m < i)
        {
            m++;
            p = q;       // p 指向第 i 个结点
            q = q->link; // q 指向 p 的后继结点
        }
        if (m < i || i < 1)
            return (1); // 插入位置 i 超界,失败
        if (s2 != NULL) // 在串 s1 的第i个结点后插入
        {
            p->link = s2;
            r->link = q;
        }
    }
    return (0); // 插入成功
}

// 6. 串删除
int L_strdel(NODE **s, int i, int k)
{
    NODE *p, *q, *r;
    int m;
    if ((*s) == NULL || k < 0)
        return (1); // 空串或删除长度为负
    m = 1;
    q = (*s); // 找删除位置 (第i个结点)
    while (q->link != NULL && m < i)
    {
        m++;
        p = q;       // p 指向第i个结点
        q = q->link; // q 指向 p 的后继结点
    }
    if (m < i || i < 1)
        return (1); // 删除位置超界,删除失败
    m = 0;
    while (q != NULL && m < k) // 删除从 i 起的 k 个结点
    {
        m++;
        r = q;
        q = q->link;
        free(r); // 释放被删除的结点
    }
    if (i == 1)
        (*s) = q; // 删除串的前面部分,修改链头指针
    else
        p->link = q; // 删除串的其它部分,修改链接指针
    return (0);      // 删除成功
}

int main()
{
    char a[] = "123456789", b[] = "abcd";
    int i = 3, n = 4, m;
    NODE *s1, *s2;

    n = sizeof(a) - 1;
    s1 = create_link_list(n, a);
    prn_link(s1);

    n = sizeof(b) - 1;
    s2 = create_link_list(n, b);
    prn_link(s2);

    // m=L_strcmp(s1, s2);
    // L_strcat(&s1, s2);
    // m=L_strsub(s1,2,3, &s2);
    // m=L_strins(&s1,1, s2);
    m = L_strdel(&s1, 1, 8);

    prn_link(s1);
    prn_link(s2);
    printf("%d\n", m);
}
