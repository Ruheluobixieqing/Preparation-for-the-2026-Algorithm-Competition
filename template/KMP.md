# KMP 算法（模式串匹配）

```cpp
#include <bits/stdc++.h>

// 构造模式串 p 的 next 表
int* buildNext(std::string p)
{
    int m = p.size();
    int j = 0;            // 主串指针
    int* N = new int[m];  // next 表
    int t = N[0] = -1;    // 模式串指针
    while (j < m - 1)
    {
        if (t < 0 || p[j] == p[t])
        {
            // t < 0 表示从下一位开始重新判断能否匹配
            // p[j] == p[t] 表示当前可以匹配
            j++, t++;
            N[j] = t;
        }
        else
        {
            // 此时 t >=0 && p[j] != p[t]
            // 此时 N[t] 记录的是上一个能够匹配的位置
            t = N[t];
        }
    }
    return N;
}

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::string s = "abcabcabcab";
    std::string p = "abcaba";
    int* next = buildNext(p);
    int i = 0, j = 0;
    int n = p.size();
    int m = s.size();
    while (j < n && i < m)
    {
        if (j < 0 || s[i] == p[j])
        {
            // j < 0 表示从下一位从头开始重新匹配
            // s[i] == s[j] 表示匹配成功
            i++, j++;
        }
        // 否则跳转至下一个可能匹配的位置
        else j = next[j];
    }
    delete[] next;
    if (j == n) std::cout<< i - j << '\n';
    else std::cout << -1;
    return 0;
}
```