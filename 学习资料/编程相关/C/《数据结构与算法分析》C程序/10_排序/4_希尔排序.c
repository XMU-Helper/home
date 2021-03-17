#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 希尔排序

void shell_sort(a, n, d, t) // a[]存放待排序的 n 个元素
    int a[],
    d[], n, t; // d[]存放增量，t 为增量个数
{
    int i, j, k, y;
    for (i = 0; i < t; i++)        // 对于每一个增量 d[i]
        for (j = d[i]; j < n; j++) // 插入排序
        {
            y = a[j];
            for (k = j - d[i]; k >= 0 && y < a[k]; k -= d[i])
                a[k + d[i]] = a[k];
            a[k + d[i]] = y;
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
    int d[] = {4, 3, 1}, t;

    n = sizeof(a) / sizeof(int);
    t = sizeof(d) / sizeof(int);

    printf("希尔排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    shell_sort(a, n, d, t);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
