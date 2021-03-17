#include <stdio.h>
#define MAXSIZE 100

// 顺序存储的线性表的删除

int sq_del(list, n, i) int list[]; // list[] 为存放线性表的数组
int *n;                            // n 指向线性表长度存放位置
int i;                             // i为删除位置
{
    int j;
    if (*n <= 0)
        return (1); // ① 线性表为空不可以删除
    if (i < 1 || i > *n)
        return (2);            // ② i 在不可以删除位置上
    for (j = i; j <= *n; j++)  // ③ 正常删除,注意循环方向
        list[j - 1] = list[j]; // 前移一位置
    (*n)--;                    // 线性表长度减 1
    return (0);                // 删除成功,返回值 0
}

int main()
{
    int m, j, n = 6, i, list[MAXSIZE] = {1, 2, 3, 4, 5, 6};
    // scanf("%d", &n);									// 输入线性表长度 n
    // creat_sq_list (n, list);							// 创建线性表

    printf("顺序存储的线性表的删除\n\n线性表为：");
    for (i = 0; i < n; i++)
        printf("%d  ", list[i]);

    printf("\n\n请输入删除位置: ");
    scanf("%d", &i); // 输入删除位置

    m = sq_del(list, &n, i);

    if (m == 1)
        printf("list 为空不可删除!\n");
    else if (m == 2)
        printf("删除位置 %d 错误!\n", i);
    else
    {
        printf("\n删除成功!\n删除后的线性表为：");
        for (j = 0; j < n; j++)
            printf("%d  ", list[j]); // 输出线性表
        printf("\n");
    }
}
