#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

// 快速排序
void quick_sort(a, s, e) int a[]; // a[]存放待排序元素
int s, e;                         // s 和 e 分别为待排序元素的起始和结束位置
{
    int i, j, t;
    if (s < e)
    {
        i = s;
        j = e;
        t = a[s];
        while (i != j)
        {
            while (i < j && a[j] > t)
                j--;
            if (i < j)
                a[i++] = a[j];
            while (i < j && a[i] <= t)
                i++;
            if (i < j)
                a[j--] = a[i];
        }
        a[i] = t;
        quick_sort(a, s, i - 1); // 递归排序右边子序列
        quick_sort(a, i + 1, e); // 递归排序左边子序列
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
    printf("快速排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    quick_sort(a, 0, n - 1);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
