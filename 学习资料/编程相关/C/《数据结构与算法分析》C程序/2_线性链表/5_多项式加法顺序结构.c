#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

typedef struct
{
    int coef;
    int exp;
} TERM;

// 追加项
int append(TERM poly[], int free, int c, int e)
{
    if (free >= MAXN)
        return (1);
    poly[free].coef = c;
    poly[free].exp = e;
    return (0);
}

//  一元多项式加法
int poly_add_s(poly, ah, at, bh, bt, ch_p, ct_p)
    TERM poly[];
int ah, at, bh, bt, *ch_p, *ct_p;
{
    int a_p;   // a_p 为 A 当前处理元素的位置
    int a_exp; // a_exp 为 A 当前处理元素的指数
    int b_p;   // b_p 为 B 的当前处理元素的位置
    int b_exp; //  b_exp 为 B 当前处理元素的指数
    int c_coef, free = bt + 1;
    a_p = ah;                      // 取 A 的第一个元素作为 A 当前处理元素
    b_p = bh;                      // 取 B 的第一个元素作为 B 当前处理元素
    *ch_p = free;                  // C 的第一个元素位置
    while (a_p <= at && b_p <= bt) // 重复直到其中一个表处理完毕
    {
        a_exp = poly[a_p].exp;
        b_exp = poly[b_p].exp;
        if (a_exp == b_exp) // 若指数值相等
        {
            c_coef = poly[a_p].coef + poly[b_p].coef;
            if (c_coef)
                if (append(poly, free++, c_coef, a_exp))
                    return (1);
            a_p++;
            b_p++;
        }
        else if (a_exp > b_exp) // 若 A 当前指数值大于 B
        {
            if (append(poly, free++, poly[a_p++].coef, a_exp))
                return (1);
        }
        else //  B 当前指数值大于 A
        {
            if (append(poly, free++, poly[b_p++].coef, b_exp))
                return (1);
        }
    }

    while (a_p <= at) // 把 A 剩余部分依次追加到 C 中
    {
        if (append(poly, free++, poly[a_p++].coef, poly[a_p].exp))
            return (1);
    }
    while (b_p <= bt) // 把 B 剩余部分依次追加到 C 中
    {
        if (append(poly, free++, poly[b_p++].coef, poly[b_p].exp))
            return (1);
    }
    *ct_p = free - 1; //  C 的最后一个元素位置
    return (0);
}

// 输出多项式
void prn(TERM poly[], int h, int t)
{
    int i;
    printf(" ( ");
    for (i = h; i <= t; i++)
        printf("(%d,%d) ", poly[i].coef, poly[i].exp);
    printf(")\n");
}

int main()
{
    TERM poly[MAXN] = {4, 80, 7, 60, 9, 5, 5, 0, 2, 80, -7, 60, 3, 12};
    int ah = 0, at = 3, bh = 4, bt = 6, ch, ct;

    printf("\n多项式 A:");
    prn(poly, ah, at);

    printf("\n多项式 B:");
    prn(poly, bh, bt);

    poly_add_s(poly, ah, at, bh, bt, &ch, &ct);

    printf("\n多项式相加结果A+B:");
    prn(poly, ch, ct);
}
