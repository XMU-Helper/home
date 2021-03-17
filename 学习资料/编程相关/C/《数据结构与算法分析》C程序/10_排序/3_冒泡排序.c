#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 冒泡排序

void bubble_sort(int a[], int n) // a[]存放待排序的 n个元素
{
    int i, k, t;
    n--;
    while (n > 0)
    {
        k = 0;
        for (i = 0; i < n; i++)
            if (a[i] > a[i + 1]) // k 保存最后交换的位置
            {
                t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
                k = i;
            }
        n = k; // n 保存无序区的最大下标
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
    printf("冒泡排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    bubble_sort(a, n);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
