#include <stdio.h>
#include <stdlib.h>

struct node
{
    int coef;
    int exp;
    struct node *link;
};
typedef struct node NODE;

NODE *ah, *bh, *ch;

// 追加项
NODE *attach(NODE *pc, int c, int e)
{
    NODE *t;
    t = (NODE *)malloc(sizeof(NODE));
    t->coef = c;
    t->exp = e;
    pc->link = t;
    return (t);
}

//  一元多项式加法
NODE *poly_add_l(NODE *ah, NODE *bh)
{
    NODE *pa, *pb, *ch, *pc;
    ch = (NODE *)malloc(sizeof(NODE)); // 附加结点为 C 的第一个结点
    pc = ch;                           // 取附加结点作为 C 的当前的最后结点
    pa = ah;                           // 取 A 的第一个结点作为 A 的当前处理元素
    pb = bh;
    while (pa != NULL && pb != NULL) // 其中一链表处理完毕
    {
        if (pa->exp == pb->exp) // 若指数值相等
        {
            if (pa->coef + pb->coef != 0)
                pc = attach(pc, pa->coef + pb->coef, pa->exp);
            pa = pa->link;
            pb = pb->link;
        }
        else if (pa->exp > pb->exp) // 若 A 当前指数大于 B
        {
            pc = attach(pc, pa->coef, pa->exp);
            pa = pa->link;
        }
        else // 若 A 当前指数大于 B
        {
            pc = attach(pc, pb->coef, pb->exp);
            pb = pb->link;
        }
    }
    if (pb != NULL)
        pa = pb;       // pa 置为剩余部分的起始位置
    while (pa != NULL) // 把剩余部分依次复制到 C 中
    {
        pc = attach(pc, pa->coef, pa->exp);
        pa = pa->link;
    }
    pc->link = NULL; // 置 C 的最后结点的指针域为空
    pc = ch;
    ch = ch->link; // 删除附加结点
    free(pc);      // 释放附加结点所占的空间
    return (ch);   // 最后返回 C 对应链表的头指针
}

// 创建链表
NODE *create_link_list(int a[][2], int n) // n≥0为线性表长度
{
    int i;
    NODE *head, *p, *q;
    if (n <= 0)
        return (NULL);
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for (i = 1; i < n; i++) // 先处理 n-1个结点
    {
        p->coef = a[i - 1][0];
        p->exp = a[i - 1][1]; // scanf("%d", &p->data);  	// 输入表元素的内容
        q = (NODE *)malloc(sizeof(NODE));
        p->link = q; // 链入下一个结点
        p = q;       // p 指向表最后结点
    }
    p->coef = a[i - 1][0];
    p->exp = a[i - 1][1]; // scanf (" %d",&(p->data));	// 输入最后元素的数据
    p->link = NULL;       // 置最后结点指针为空
    return (head);        // 返回建成链表头指针
}

// 输出链表
void print_link(NODE *head)
{
    NODE *p = head;
    printf(" ( ");
    while (p != NULL) // 寻找插入的位置
    {
        printf("(%d,%d) ", p->coef, p->exp);
        p = p->link;
    }
    printf(")\n");
}

int main()
{
    int a[][2] = {4, 80, 7, 60, 9, 5, 5, 0}, b[][2] = {2, 80, -7, 60, 3, 12};
    NODE *ah, *bh, *ch;

    ah = create_link_list(a, 4);
    printf("\n多项式 A:");
    print_link(ah);

    bh = create_link_list(b, 3);
    printf("\n多项式 B:");
    print_link(bh);

    ch = poly_add_l(ah, bh);

    printf("\n多项式相加结果A+B:");
    print_link(ch);
}
