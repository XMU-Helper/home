#include <stdio.h>
#define MAXN 100

// 二分查找
int bin_search(int a[], int n, int v)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (v == a[mid])
            return (mid);
        if (v < a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return (-1);
}

int main()
{
    int a[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int i, m, n, v;
    n = sizeof(a) / sizeof(int);

    printf("二分查找\n线性表为：");
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);

    printf("\n\n输入要查找的值：");
    scanf("%d", &v);
    m = bin_search(a, n, v);

    if (m > 0)
        printf("\n%d 为线性表的第 %d 个元素\n\n", v, m + 1);
    else
        printf("\n%d 没找到\n", v);
}
