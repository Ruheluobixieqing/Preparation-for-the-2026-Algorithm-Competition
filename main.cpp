#include <bits/stdc++.h>
#define ll long long
const int N = 2e5+4;
int a[N];

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v(n+1), prefix(n+1), prefix_xor(n+1);
    for (int i = 1; i <=n; i ++)
    {
        std::cin >> v[i];
        prefix[i] = prefix[i-1] + v[i];
        prefix_xor[i] = prefix_xor[i-1] ^ v[i];
    }

    ll ans = 0;
    for (int i = 1, j = 1; i <= n && j <= n; )
    {
        if ((prefix_xor[j] ^ prefix_xor[i - 1]) == (prefix[j] - prefix[i - 1]))
        {
            ans += j - i + 1;
            j ++;
        }
        else i++;
    }

    std::cout << ans << '\n';
    return 0;
}