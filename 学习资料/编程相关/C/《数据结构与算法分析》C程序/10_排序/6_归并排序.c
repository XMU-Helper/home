#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 归并排序

void merge(int a[], int b[], int s, int m, int t) // 二路归并
{
    int i, j, k;
    i = s;
    j = m + 1;
    k = s;
    while (i <= m && j <= t)
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    while (i <= m)
        b[k++] = a[i++];
    while (j <= t)
        b[k++] = a[j++];
}

void mpass(int a[], int b[], int n, int r) // 一趟归并程序
{
    int i = 0, j;
    while (i + 2 * r <= n)
    {
        merge(a, b, i, i + r - 1, i + 2 * r - 1);
        i += 2 * r;
    }
    if (i + r < n)
        merge(a, b, i, i + r - 1, n - 1); // r ＜ 剩下的元素个数 ＜ 2r
    else
        for (j = i; j < n; j++)
            b[j] = a[j]; // 剩下的元素个数 ≤ r
}

void merge_sort(int a[], int n) // 归并排序
{
    int b[MAXN];
    int r = 1;
    while (r < n)
    {
        mpass(a, b, n, r);
        r *= 2;
        mpass(b, a, n, r);
        r *= 2;
    }
}

// 输出线性表

void prn_list(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

int main()
{
    int n, a[] = {41, 25, 18, 64, 45, 37, 33, 80, 61};

    n = sizeof(a) / sizeof(int);
    printf("归并排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    merge_sort(a, n);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
