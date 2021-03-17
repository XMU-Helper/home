#include <string.h>
#include <stdio.h>

#define MAXN 100 // MAXN 为正文T 或 (字符串)  的最大长度
#define MAXM 20  // MAXM 为模式 P 的最大长度

// 1. 求串长度
int S_strlen(char s[])
{
    int i;
    for (i = 0; s[i]; i++)
        ;
    return (i); // 返回串长度
}

// 2. 串比较
int S_strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}

// 3. 串连接
int S_strcat(char s1[], char s2[])
{
    int i, j, k;
    i = strlen(s1);
    j = strlen(s2);
    if (i + j >= MAXN)
        return (1);         // 空间不够,连接失败!
    for (k = 0; k < j; k++) // s2 (包括结束符'\0') 加到s1后面
        s1[i + k] = s2[k];
    return (0); // 连接成功
}

// 4. 求子串
int S_strsub(char s1[], int i, int k, char s2[])
{
    int m = strlen(s1);
    if (i < 1 || i > m)
        return (1); // 位置 i 超界,失败
    if (k < 0 || i + k > m + 1)
        return (1); // 子串太长, 失败
    for (m = 0; m < k; m++)
        s2[m] = s1[i + m - 1];
    s2[m] = '\0';
    return (0); // 操作成功
}

// 5. 串插入
int S_strins(char s1[], int i, char s2[])
{
    int m = strlen(s1), n = strlen(s2), k;
    if (i < 1 || i > m + 1 || m + n >= MAXN)
        return (1); // 位置 i 超界或空间不够，插入失败
    for (k = m; k >= i - 1; k--)
        s1[k + n] = s1[k]; // 移出 n 个位置，'\0' 一起移动
    for (k = 0; k < n; k++)
        s1[i + k - 1] = s2[k];
    return (0); // 插入成功
}

// 6. 串删除
int S_strdel(char s[], int i, int k)
{
    int m, j;
    m = S_strlen(s);
    if (i < 1 || i > m)
        return (1); // 位置 i 超界, 删除失败
    if (i + k > m)
        s[i - 1] = '\0'; // 删除串的尾部 k 个字符
    else                 // 删除串的中间 k 个字符
        for (j = 0; j <= m - i - k + 1; j++)
            s[i + j - 1] = s[i + k + j - 1];
    return (0); // 删除成功
}

// 7. 模式匹配
int S_index(char t[], char p[])
{
    int n, m, i, j;
    n = strlen(t); //求正文 T 的当前的长度
    m = strlen(p); //求模式 P 的当前的长度
    for (i = 0; i <= n - m; i++)
    {
        for (j = 0; j < m && t[i + j] == p[j]; j++)
            ; // 空循环,模式 P 与 Ti 比较
        if (j == m)
            return (i + 1); // 匹配成功,返回位置
    }
    return (0); // 匹配失败,返回 0
}

int main()
{
    char a[MAXN] = "123456789", b[MAXN] = "456";
    int i = 3, m;

    // m=S_strcmp(a, b);;
    // m=S_strcat(a, b );
    // m=S_strsub(a,9,2, b);

    // m=S_strins(a,11, b);

    // m=S_strdel(a,9,3);
    m = S_index(a, b);

    printf("a=%s,b=%s\n", a, b);
    printf("%d\n", m);
}
