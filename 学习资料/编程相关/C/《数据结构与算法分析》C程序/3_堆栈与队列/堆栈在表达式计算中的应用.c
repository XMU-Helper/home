#include <stdio.h>
#define MAXN 100

// 后缀表达式求的值
int compvale(pos_exp, p_x) char pos_exp[]; // 存放后缀的表达式
float *p_x;                                // 指向存放结果的变量
{
    float stack[MAXN], x; // 定义栈
    char c;
    int top, t = 0;   // 表达式扫描位置(下标)初始化
    top = -1;         // 栈初始化，用第一种表示法
    c = pos_exp[t++]; // 取第一个扫描字符
    while (c != '\0') // 循环直到表达式结束
    {
        if (c >= '0' && c <= '9')   // 判定若为数字字符
            stack[++top] = c - '0'; // 数字字符转成数值并进栈
        else                        // 否则为运算符
            switch (c)              //  出栈            把出栈的数加到栈顶
            {
            case '+':
                x = stack[top--];
                stack[top] += x;
                break;
            case '-':
                x = stack[top--];
                stack[top] -= x;
                break;
            case '*':
                x = stack[top--];
                stack[top] *= x;
                break;
            case '/':
                if (stack[top] != 0) // 除数非 0,做除法运算
                {
                    x = stack[top--];
                    stack[top] /= x;
                    break;
                }
                else
                    return (2); // 除数为 0 出错,返回值 2
            default:
                return (1); // 非四则运算符错! 返回 1
            }
        c = pos_exp[t++]; // 取下一个扫描字符
    }
    *p_x = stack[top]; // 结果送 p_x 所指的变量中
    return (0);        // 操作成功，返回值 0
}

// 求当前扫描字符 c 的进栈前优先级别
int icp(char c)
{
    switch (c)
    {
    case '*':
    case '/':
        return (2);
    case '+':
    case '-':
        return (1);
    }
}

// 求栈顶字符 c 的栈中优先级别
int isp(char c)
{
    switch (c)
    {
    case '*':
    case '/':
        return (2);
    case '+':
    case '-':
        return (1);
    case '(':
        return (0);
    case '#':
        return (-1);
    }
}

// 把中缀表达式转换成后缀表达式
int mid_to_pos(mid_exp, pos_exp) char mid_exp[]; // mid_exp 指向中缀表达式 (字符串)
char pos_exp[];                                  // pos_exp 指向后缀表达式 (字符串)
{
    char stack[MAXN], c;
    int top = 0, i = 0, j = 0;
    stack[0] = '#';   // 栈底放 '#'
    c = mid_exp[0];   //  取第一个扫描字符
    while (c != '\0') // 当前扫描字符 c 非结束符
    {
        if (c >= '0' && c <= '9') // 判别数字字符
            pos_exp[j++] = c;     // ① 将数字字符输出
        else
            switch (c)
            {
            case '(':
                stack[++top] = c;
                break; // ② c 为 '('
            case '+':  // ③ c 为四则运算符
            case '-':
            case '*':
            case '/':
                while (icp(c) <= isp(stack[top]))
                    pos_exp[j++] = stack[top--];
                stack[++top] = c;
                break;
            case ')':
                while (stack[top] != '(') // ④ c 为 ')'
                    pos_exp[j++] = stack[top--];
                top--;
                break;
            default:
                return (1); // 表达式有错,返回值 1
            }
        c = mid_exp[++i];
    }               // end while
    while (top > 0) // ⑤ c 为 '\0'
        pos_exp[j++] = stack[top--];
    pos_exp[j] = '\0'; // 设置后缀表达式串结束标志
    return (0);        // 操作成功，返回值 0
}

int main()
{
    char m_exp[MAXN], p_exp[MAXN]; // 分别存放中缀和后缀表达式
    float r;
    int i = -1, n;
    printf("请输入表达式串：");
    gets(m_exp);
    n = mid_to_pos(m_exp, p_exp); // 转换成后缀表达式
    if (n == 0)                   // 判别转换是否成功
    {
        printf("后缀表达式为：%s\n", p_exp); // 转换成功
        n = compvale(p_exp, &r);             // 求后缀表达式的值
        if (n == 0)
            printf("表达式的值=%.1f \n", r); // 求值成功
        else if (n == 2)
            printf("除数为零! \n"); // 求值失败
        else
            printf("表达式有错 ! \n");
    }
    else
        printf("表达式输入有错! \n"); // 转换失败
}
