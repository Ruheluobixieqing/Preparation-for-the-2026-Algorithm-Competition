# 基数排序

```cpp
#include <bits/stdc++.h>
const int N = 2e6+3;

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (auto &e: v) std::cin >> e;
    int cnt = 0, mx = *std::max_element(v.begin(), v.end());
    while (mx) cnt++, mx /= 10;
    std::vector<std::vector<int>> A(10, std::vector<int>());
    for (int T = 0, p = 1; T < cnt; T++, p *= 10)
    {
        for (const auto &e: v)
        {
            int c = e / p % 10;
            A[c].push_back(e);
        }
        std::vector<int>().swap(v);
        for (int j = 0; j < 10; j++)
        {
            for (const auto &e: A[j]) v.push_back(e);
            std::vector<int>().swap(A[j]);
        }
    }
    for (const auto &e: v) std::cout << e << ' ';

    return 0;
}
```