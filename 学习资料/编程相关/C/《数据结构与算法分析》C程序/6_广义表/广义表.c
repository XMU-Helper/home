#include <stdlib.h>
#include <stdio.h>
typedef struct node
{
    int tag;
    union
    {
        struct node *sublist;
        char data;
    } dd;
    struct node *link;
} NODE;

void prn_GL(NODE *p)
{
    if (p == NULL)
        return;
    if (p->tag == 1) // 为表结点
    {
        printf("("); // 输出 '('
        if (p->dd.sublist == NULL)
            printf(""); //输出空子表
        else
            prn_GL(p->dd.sublist); // 递归输出子表
    }
    else
        printf("%c", p->dd.data); // 原子结点,输出元素值
    if (p->tag == 1)
        printf(")"); // 为表结点,输出')'
    if (p->link != NULL)
    {
        printf(",");
        prn_GL(p->link);
    }
}

NODE *copy_GL(NODE *p)
{
    NODE *q;
    if (p == NULL)
        return (NULL);                // 输出空子表
    q = (NODE *)malloc(sizeof(NODE)); // 产生新结点
    q->tag = p->tag;
    if (p->tag)                                 // 当前结点为表结点
        q->dd.sublist = copy_GL(p->dd.sublist); // 递归复制子表
    else
        q->dd.data = p->dd.data; // 复制元素结点
    q->link = copy_GL(p->link);  // 递归复制后继表的内容
    return (q);                  // 返回备份后链表的指针
}

NODE *creat_GL(char **s)
{
    NODE *h;
    char ch = *(*s); // 取一个扫描字符
    (*s)++;
    while (ch == ' ')
    {
        ch = *(*s);
        (*s)++;
    }

    if (ch != '\0') // 串未结束

    {
        if (ch == ')')
            return NULL;
        h = (NODE *)malloc(sizeof(NODE)); // 产生新结点
        if (ch == '(')                    // 递归构造子表并链到表头结点
        {
            h->tag = 1;
            h->dd.sublist = creat_GL(s);
        }
        else // 新结点作为原子结点
        {
            h->tag = 0;
            h->dd.data = ch;
        }
    }
    else
        h = NULL; // 串结束,子表为空
    ch = *(*s);   // 取下一个扫描字符
    (*s)++;
    while (ch == ' ')
    {
        ch = *(*s);
        (*s)++;
    }

    if (h != NULL)                 // 串未结束
        if (ch == ',')             // 当前字符为 ',' /
            h->link = creat_GL(s); // 递归构造后续子表
        else                       // 串结束
            h->link = NULL;        // 处理表的最后一个元素
    return (h);                    // 返回广义表位置指针
}

int main()
{
    NODE *hd, *hc;
    char *d = "((a,(b,  c)  ),(        ),(a))";
    char *a = "(    ) ";
    hd = creat_GL(&d);
    prn_GL(hd);
    putchar('\n');
    // hc=copy_GL(hd);
    // prn_GL(hc); putchar('\n');
}