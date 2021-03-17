#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 选择排序

void select_sort(a, n) int a[], n; // a[] 存放待排序的 n 个元素
{
    int i, j, k, t;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++) // 选择一个最小的元素 a[k]
            if (a[k] > a[j])
                k = j;
        t = a[i];
        a[i] = a[k];
        a[k] = t; // a[k]与a[i]交换位置
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
    printf("选择排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    select_sort(a, n);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
