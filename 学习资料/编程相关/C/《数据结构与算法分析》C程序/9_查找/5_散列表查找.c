#include <stdio.h>
#define M 10 // M 为散列表大小

// 散列表函数计算
int h(int v)
{
    return (v % M);
}

// 散列表查找
int hash_search(int v, int t[])
{
    int addr, i;
    addr = h(v); // 计算 hash 函数
    // 按循环探测地址序列进行查找
    for (i = 0; i < M && t[(addr + i) % M] != 0; i++)
    {
        if (t[(addr + i) % M] == v)
            return ((addr + i) % M); // 查找成功
    }
    return (-1); // 找到个空位置或用完探测地址序列，则查找失败
}

// 以第二章图12(a)的散列表为例
int main()
{
    int a[] = {18, 10, 2, 3, 63, 75, 94, 25, 48, 35}; //  第二章 线性表 图12(a)的散列表

    int i, v = 18;

    printf("散列表查找\n\n散列表为：");
    for (i = 0; i < M; i++)
        printf("%d  ", a[i]);

    printf("\n\n输入要查找的值：");
    scanf("%d", &v);
    i = hash_search(v, a);

    if (i > 0)
        printf("\n%d 为散列表的第 %d 个元素\n\n", v, i + 1);
    else
        printf("\n%d 没找到\n\n", v);
}
