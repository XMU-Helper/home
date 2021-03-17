#include <stdio.h>
#define MAXN 100

// 顺序存储的线性表的查找
int seq_search_s(int a[], int n, int v)
{
    int i;
    for (i = 0; i < n && a[i] != v; i++)
        ; // 空循环
    if (i < n)
        return (i);
    return (-1);
}

int main()
{
    int a[] = {1, 2, 5, 3, 4, 6, 7, 8};
    int i, m, n, v;
    n = sizeof(a) / sizeof(int);

    printf("顺序存储的线性表的查找\n线性表为：");
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);

    printf("\n\n输入要查找的值：");
    scanf("%d", &v);
    m = seq_search_s(a, n, v);

    if (m > 0)
        printf("\n%d 为线性表的第 %d 个元素\n\n", v, m + 1);
    else
        printf("\n%d 没找到\n", v);
}
