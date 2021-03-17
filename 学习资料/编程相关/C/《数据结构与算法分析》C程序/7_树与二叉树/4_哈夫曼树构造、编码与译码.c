#include <stdio.h>
#include <stdlib.h>
#define N 100
char stack[200];
int top = 0;
char ct[N][10];  // 码表XX
                 // N为叶结点数目的最大值
#define MAX 9999 // MAX为无穷大整数
struct node      // 树的结点结构
{
    union
    {
        char data;
        int w;
    } val;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node NODE;

// 哈夫曼树构造
NODE *creat_huffmam_tree(char dat[], int w[], int n)
{
    NODE *T[N], *p; // T[ ]存放森林中树的根结点
    int n1, n2, i, j, v, min1, min2;

    // 以下实现构造算法步骤 ①
    for (i = 0; i < n; i++)
    {
        T[i] = (NODE *)malloc(sizeof(NODE));
        T[i]->val.w = w[i];
        T[i]->lchild = NULL;
        T[i]->rchild = NULL;
    }
    for (i = 0; i < n - 1; i++) // 重复算法步骤 ② 和 ③

    // 以下实现构造算法步骤 ②
    {
        n1 = -1;
        min1 = MAX;
        n2 = -1;
        min2 = MAX;
        for (j = 0; j < n; j++) // 选取两棵结点的权值最小的树
            if (T[j] != NULL)
            {
                v = T[j]->val.w;
                if (v < min1)
                {
                    min2 = min1;
                    n2 = n1;
                    min1 = v;
                    n1 = j;
                }
                else if (v < min2)
                {
                    min2 = v;
                    n2 = j;
                }
            }
        p = (NODE *)malloc(sizeof(NODE));       // 构造一棵新
        p->val.w = T[n1]->val.w + T[n2]->val.w; // 的二叉树
        p->lchild = T[n1];
        p->rchild = T[n2];

        // 以下实现构造算法步骤 ③
        if (T[n1]->lchild == NULL)     // 新树的左子树
            T[n1]->val.data = dat[n1]; // 的根为叶结点
        else
            T[n1]->val.data = '*';     // 否则为分支结点
        if (T[n2]->lchild == NULL)     // 新树的右子树
            T[n2]->val.data = dat[n2]; // 的根为叶结点
        else
            T[n2]->val.data = '*'; // 否则为分支结点
        T[n1] = p;                 // 在森林 T 中,新树代替这两棵树
        T[n2] = NULL;
    }
    p->val.data = '*'; // 最后树的根结点为分支结点
    return (p);        // 返哈夫曼树的根结点的地址
}

// 按嵌套括号表示表示法输出二叉树(哈夫曼树)
void prn_BT(NODE *b)
{
    if (b != NULL)
    {
        printf("%c", b->val.data);
        if (b->lchild != NULL) // b为分支结点,即有左右子树
        {
            printf("(");
            prn_BT(b->lchild);
            printf(",");
            prn_BT(b->rchild);
            printf(")");
        }
    }
}

// 哈夫曼编码码表输出
void prn_code_tab(NODE *b)
{
    int i, k;
    if (b->lchild != NULL) // 分支结点
    {
        stack[top++] = '0';
        prn_code_tab(b->lchild);
        top--;
        stack[top++] = '1';
        prn_code_tab(b->rchild);
        top--;
    }
    else // 叶结点
    {
        printf("\n %c=", b->val.data);
        k = b->val.data - 'a'; //  XX
        for (i = 0; i < top; i++)
        {
            printf("%c", stack[i]);
            ct[k][i] = stack[i]; // XX
        }
    }
}

// 编码
void prn_code(char t[])
{
    int i = 0;
    while (t[i])
        printf("%s", ct[t[i++] - 'a']);
}

// 译码
void encode(NODE *b, char s[])
{
    NODE *p = b;
    int i = 0;
    char c = s[i++];
    while (c != '\0')
        if (p->lchild != NULL) // 是否分支结点
        {
            if (c == '0')
                p = p->lchild;
            else
                p = p->rchild;
            c = s[i++]; // 取下一个编码字符
        }
        else // 到达叶结点
        {
            printf("%c", p->val.data);
            p = b; // 回到根结点
        }
}

int main()
{
    NODE *h;
    char d[N] = {'a', 'b', 'c', 'd'};  // 输入一组结点的键值
    int w[N] = {5, 7, 2, 4};           // 输入一组相应权值
    char c[] = "10110010100110100110"; // 电文
    char t[] = "abcddacd";             // 原文

    h = creat_huffmam_tree(d, w, 4);

    printf("\n 哈夫曼为：");
    prn_BT(h);

    printf("\n 哈夫曼编码码表为：");
    prn_code_tab(h);

    printf("\n 原文 %s 的编码为：", t);
    prn_code(t);

    printf("\n 编码 %s 的原文为：", c);
    encode(h, c);
    putchar('\n');
}
