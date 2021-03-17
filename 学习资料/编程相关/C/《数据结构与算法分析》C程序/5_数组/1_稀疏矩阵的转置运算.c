#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

// 转置的方法一、一般方法
void tanspose(int a[][3], int b[][3])
{
    int m, n, t, p, q, col;
    m = a[0][0];
    n = a[0][1];
    t = a[0][2];
    b[0][0] = n;
    b[0][1] = m;
    b[0][2] = t;
    if (t > 0)
    {
        q = 1;                        // q 为 b 的当前处理位置
        for (col = 0; col < n; col++) // 对于原矩阵中的每一列号
            for (p = 1; p <= t; p++)  // 对 a 进行扫描,从 a 中找出列号为当前列号的三元组
                if (a[p][1] == col)
                {
                    b[q][0] = a[p][1]; // 行列号对调存入 b 中
                    b[q][1] = a[p][0];
                    b[q][2] = a[p][2];
                    q++; // q 指向 b 的下一个处理位置
                }
    }
}

//  转置的方法二、快速转置
void fast_transpose(int a[][3], int b[][3])
{
    int m, n, t, i, j;
    int num[MAXN]; // num[ ] 存放各行非零元素的个数
    int pot[MAXN]; // pot[ ] 存放每一行对应的指针组
    m = a[0][0];
    n = a[0][1];
    t = a[0][2];
    b[0][0] = n;
    b[0][1] = m;
    b[0][2] = t;
    if (t > 0)
    {
        for (i = 1; i <= n; i++)
            num[i] = 0; // 初始化
        for (i = 1; i <= t; i++)
            num[a[i][1]]++; // 统计转置矩阵各行非零元素的个数
        pot[1] = 1;         // 计算每一行元素在 b 中的起始位置
        for (i = 2; i <= n; i++)
            pot[i] = pot[i - 1] + num[i - 1];
        for (i = 1; i <= t; i++) // 对 a 进行扫描
        {
            j = pot[a[i][1]];  // 取 a[i][1] 行在 b 中的当前的位置
            b[j][0] = a[i][1]; // 把三元组装入 b 当前存储位置
            b[j][1] = a[i][0];
            b[j][2] = a[i][2];
            pot[a[i][1]]++; // 指向 b 的下一个存储位置
        }
    }
}

// 输出三元组
void prn_a(int a[][3])
{
    int i, t;
    t = a[0][2];
    for (i = 0; i <= t; i++)
        printf("(%d) %2d,%2d,%3d \n", i, a[i][0], a[i][1], a[i][2]);
}

int main()
{
    int a[MAXN][3] = {7, 8, 8, 1, 2, 24, 2, 4, -35, 2, 7, 81, 3, 1, 8, 4, 4, 15, 5, 2, -57, 5, 6, 62, 6, 4, 96};
    int b[MAXN][3];

    printf("\n原三元组:\n");
    prn_a(a);

    // tanspose (a,b);
    fast_transpose(a, b);

    printf("\n转置后三元组:\n");
    prn_a(b);
}
