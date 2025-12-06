```cpp
#include<bits/stdc++.h>

void solve()
{
    std::string s;
    int n, k;
    std::cin >> n >> k;
    std::cin >> s;
    int ans = 0;
    int j = 1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            int j = 1;
            for (; j <= k && i + j < n && s[i+j] == '0'; j++) s[i+j] = '1';
            i = i + j - 1;
        }
    }
    // for (const auto &e: s) std::cout <<e;
    // std::cout << '\n';
    for (int i = 0; i < n; i++) if (s[i] == '0') ans ++;
    std::cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) solve();
    return 0;
}
```