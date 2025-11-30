#include <bits/stdc++.h>
const int N = 2e6+3;
int a[N],pre[N];

int getRoot(int x)
{
    return pre[x] = (pre[x] == x ? x : getRoot(pre[x]));
}

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= 2e6; i++) pre[i] = i;

    for (int i = 1; i <= n; i++)
    {
        std::cout << getRoot(a[i]) << ' ';

        int x = getRoot(a[i]);
        pre[getRoot(x)] = getRoot(x + 1);
    }
    return 0;
}