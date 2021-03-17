#include <stdio.h>
#include <stdlib.h>

// 输出线性表

void prn_list(int a[], int n)
{
    int i;
    for (i = 1; i <= n; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

//“筛”运算

void sift(int a[], int i, int n1)
{
    int t = a[i], j = 2 * i; // j 置为 a[i] 的左孩子的下标
    while (j <= n1)
    {
        if (j < n1 && a[j] < a[j + 1])
            j++; // 若右孩子大，把 j 改为右孩子的下标
        if (t < a[j])
        {
            a[i] = a[j];
            i = j;
            j = 2 * i;
        } // 将 a[j] 调到父结点的位置；修改 i 和 j 的值,以便继续下“筛”
        else
            break;
    }
    a[i] = t;
}

// 堆排序

void heap_sort(int a[], int n)
{
    int i, t;
    for (i = n / 2; i >= 1; i--) // 建立初始堆
        sift(a, i, n);

    for (i = n; i >= 2; i--) // 进行n-1筛选交换,完成堆排序;
    {
        t = a[1]; // 第一个元素与最后一个元素的对调
        a[1] = a[i];
        a[i] = t;
        sift(a, 1, i - 1); // 筛结点 a[1],得到 i-1 个结点的堆
    }
}

int main()
{
    int n, a[] = {0, 41, 25, 18, 64, 45, 37, 33, 80, 61}; // 下标为0 单元不用

    n = sizeof(a) / sizeof(int) - 1;

    printf("堆排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    heap_sort(a, n);
    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
