#include <stdio.h>
typedef struct
{
    int start; // 块的起始位置
    int len;   // 块中结点数(长度)
    int key;   // 索引表项结构
} IDX;

// 分块查找
int blk_search(int a[], IDX idx[], int v, int m)
{
    int low = 0, high = m - 1, mid, i, h;
    while (low <= high) // 二分查找索引表
    {
        mid = (low + high) / 2;
        if (v < idx[mid].key)
            high = mid - 1;
        else if (v > idx[mid].key)
            low = mid + 1;
        else
        {
            low = mid;
            break;
        }
    }

    if (low >= m)
        return (-1);      // v 超出索引表最大值
    i = idx[low].start;   // 确定块的起始位置
    h = i + idx[low].len; // 确定块的结束位置

    while (i < h && a[i] != v)
        i++; // 顺序查找指定的块内
    if (a[i] != v)
        i = -1;
    return (i);
}

// 以课件中的分块有序表为例
int main()
{
    int i, n, v, m = 3;
    int a[] = {5, 30, 15, 24, 35, 48, 39, 38, 50, 60, 70, 65}; // 线性表
    IDX idx[] = {{0, 5, 35}, {5, 3, 48}, {8, 4, 70}};          // 索引表

    n = sizeof(a) / sizeof(int);

    printf("分块查找\n\n线性表为：");
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);
    printf("\n\n索引表：\n起始位置  块中结点数  索引值");

    for (i = 0; i < m; i++)
        printf("\n%4d%12d%10d", idx[i].start, idx[i].len, idx[i].key);

    printf("\n\n输入要查找的值：");
    scanf("%d", &v);
    i = blk_search(a, idx, v, m);

    if (i > 0)
        printf("\n%d 为线性表的第 %d 个元素\n\n", v, i + 1);
    else
        printf("\n%d 没找到\n\n", v);
}
