#include <stdio.h>
#define MAXSIZE 100

// 顺序存储的线性表的插入

int sq_ins(list, n, i, x) int list[], *n; // list[] 存放线性表，n 指向长度存放位置
int i, x;                                 // i 为插入位置, x 为插入值
{
    int j;
    if (i < 1 || i > *n + 1)
        return (1); // ① 插入的位置 i 错！
    if (*n == MAXSIZE)
        return (2);              // ② 1ist 数组已没有存储单元
    for (j = *n; j > i - 1; j--) // ③ 正常插入,注意循环方向
        list[j] = list[j - 1];   // 后移一位置使第 i 位置留空
    list[i - 1] = x;
    (*n)++;     // 线性表长度+1
    return (0); // 插入成功,返回值 0
}

int main()
{
    int m, j, i, x, n = 7;
    int list[MAXSIZE] = {1, 3, 5, 7, 9, 11, 15};

    // scanf("%d", &n);	// 输入线性表长度 n
    // creat_sq_list (n, list);	// 创建线性表

    printf("顺序存储的线性表的插入\n\n线性表为：");
    for (i = 0; i < n; i++)
        printf("%d  ", list[i]);

    printf("\n\n请输入 (插入位置，插入元素):");
    scanf("%d,%d", &i, &x); // 输入插入位置和插入元素

    m = sq_ins(list, &n, i, x);

    if (m == 1)
        printf("插入位置 %d 错误!\n", i);
    else if (m == 2)
        printf("list 数组存储单元不够!\n");
    else
    {
        printf("\n插入成功!\n插入后的线性表为：");
        for (j = 0; j < n; j++)
            printf("%d  ", list[j]); // 输出线性表
    }
    printf("\n");
}
