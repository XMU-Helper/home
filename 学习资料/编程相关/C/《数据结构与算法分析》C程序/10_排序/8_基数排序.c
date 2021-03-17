#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

#define MAX_R 10 // 基数的最大取值
#define MAX_D 8  // 关键字位数的最大取值
struct node
{
    char data[MAX_D]; // 关键字定义为字符串
    struct node *link;
};
typedef struct node NODE;

// 基数排序

// 十进制整数 n 转为 r 进制字符串s[]，返回串长度
int int_to_str(int n, int r, char s[])
{
    int i = 0, d, m;
    do
    {
        m = n / r;
        d = n % r;
        s[i++] = '0' + d;
        n = m;
    } while (n != 0);

    n = i;
    for (; i < MAX_D; i++)
        s[i] = '0';
    return (n);
}

// 长度为d 的字符串s[] 转为r 进制数
int str_to_int(int d, int r, char s[])
{
    int i, n = 0;
    for (i = d - 1; i >= 0; i--)
        n = n * r + s[i] - '0';
    return (n);
}

// 顺序结构转为链接结构并且整型转为字符串
NODE *create_link_list(int a[], int n, int r, int *d)
{
    int i, d1 = 0;
    NODE *head, *p, *q;
    *d = 0;
    if (n <= 0)
        return (NULL);
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for (i = 0; i < n - 1; i++) // 先处理 n-1个结点
    {
        d1 = int_to_str(a[i], r, p->data);
        *d = *d > d1 ? *d : d1;
        q = (NODE *)malloc(sizeof(NODE));
        p->link = q; // 链入下一个结点
        p = q;       // p 指向表最后结点
    }
    d1 = int_to_str(a[i], r, p->data);
    *d = *d > d1 ? *d : d1;
    p->link = NULL; // 置最后结点指针为空
    return (head);  // 返回建成链表头指针
}

// 实现 LSD 排序
void radix_sord(int a[], int n, int r)
{
    NODE *head[MAX_R], *tail[MAX_R]; // 首尾指针
    NODE *p;
    int i, j, k, d;

    p = create_link_list(a, n, r, &d);
    for (i = 0; i < d; i++) // 对于从低到高的每一位
    {
        for (j = 0; j < r; j++)
            head[j] = NULL; // 初始化首指针
        while (p != NULL)   // 对于链表中每个结点
        {
            k = p->data[i] - '0'; // 找第 k 个队列
            if (head[k] == NULL)
                head[k] = p; // 进行分配
            else
                tail[k]->link = p;
            tail[k] = p;
            p = p->link; // 取下个待排序的元素
        }

        p = NULL;
        for (j = r - 1; j >= 0; j--) // 对于每一个队列
            if (head[j] != NULL)     // 进行收集
            {
                tail[j]->link = p;
                p = head[j];
            }
    }
    i = 0;
    while (p)
    {
        a[i++] = str_to_int(d, r, p->data);
        p = p->link;
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
    int n, a[] = {41, 35, 18, 65, 45, 38, 33, 80, 61, 75, 71, 15};

    n = sizeof(a) / sizeof(int);

    printf("基数排序!!\n\n排序前线性表为: ");
    prn_list(a, n);

    radix_sord(a, n, 10);

    printf("\n排序后线性表为: ");
    prn_list(a, n);
    printf("\n");
}
