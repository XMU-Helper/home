#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 插入排序

void insert_sort(int a[], int n)
{
    int i, j, t;
    for (i = 1; i < n; i++)
    {
        t = a[i];
        for (j = i - 1; j >= 0 && t < a[j]; j--)
            a[j + 1] = a[j];
        a[j + 1] = t; // 在 a[j] 后面插入
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
    printf("插入排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    insert_sort(a, n);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
