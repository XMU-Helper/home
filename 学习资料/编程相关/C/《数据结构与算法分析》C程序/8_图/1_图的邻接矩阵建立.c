#include <stdio.h>
#include <stdlib.h>
#define MAX 100       // 最大顶点数
#define INFINITE 9999 // 用 9999 表示 ∞

// 生成邻接矩阵
void creat_adjmatrix(int A[][MAX], char V[], int n, int e, int t)
{
    int i, j, k, w;
    printf("顶点数 n=%d, 边数 e=%d \n", n, e);
    for (i = 1; i <= n; i++) // 输入 n 个顶点信息
    {
        printf("输入第%d顶点信息(单个字符):", i);
        scanf("%c", &V[i]);
        getchar();
    }                        // 假设顶点信息只为一个字符
    for (i = 1; i <= n; i++) // 初始化邻接矩阵
        for (j = 1; j <= n; j++)
            if (t > 2)
                A[i][j] = INFINITE; // 带权图初始化
            else
                A[i][j] = 0;

    for (k = 1; k <= e; k++) // 输入 e 条边
    {
        printf("第%d条边(起点,终点): ", k);
        scanf("%d,%d", &i, &j);

        if ((i > n) || (j > n))
        {
            printf("顶点编号错误!");
            exit(0);
        }
        if (t > 2) // t=2,t=3 带权图
        {
            printf("输入权值：");
            scanf("%d", &w);
            A[i][j] = w;
            if (t == 3)
                A[j][i] = w; // t=3 带权无向图
        }
        else // t=1,t=2 不是带权图
        {
            A[i][j] = 1;
            if (t == 1)
                A[j][i] = 1;
        } // t=1 为无向图
    }
}

// 输出邻接矩阵
void prn_adjmatrix(int a[][MAX], int n)
{
    int i, j;
    printf("\n邻接矩阵为：\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            if (a[i][j] == INFINITE)
                printf("  ∞");
            else
                printf("%4d", a[i][j]);
        printf("\n");
    }
}

int main()
{
    char v[MAX];     // 顶点信息设为字符型
    int a[MAX][MAX]; // 邻接矩阵
    int n = 6, e = 7;
    // creat_adjmatrix(a,v,n,7,1);
    // creat_adjmatrix(a,v,n,9,2);
    creat_adjmatrix(a, v, n, e, 1);
    prn_adjmatrix(a, n);
}