#include <bits/stdc++.h>
#define ll long long
#define inf LONG_LONG_MAX
const int N = 2e5+5;
int a[N];

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    ll n,k;
    std::cin>>n>>k;
    std::map<ll,ll> ltr,rtl;
    for (int i = 1; i <= n; i ++)
    {
        std::cin>>a[i];
        if (!ltr[a[i]]) ltr[a[i]] = i;
        rtl[a[i]] = n - i + 1;
    }
    ll ans = inf;
    // 从左往右依次拿
    for (int i = 1; i <= n; i ++)
    {
        if (ltr[a[i]] > n/2) break;
        if (ltr.find(k-a[i]) != ltr.end() && k - a[i] != a[i])
        {
            ll time = std::max(ltr[a[i]],ltr[k-a[i]]);
            ans = std::min(ans,time);
        }
    }

    // 从右往左依次拿
    for (int i = n ; i >= 1; i--)
    {
        if (rtl[a[i]] > n/2) break;
        if (rtl.find(k-a[i]) != rtl.end() && k - a[i] != a[i])
        {
            ll time = std::max(rtl[a[i]],rtl[k-a[i]]);
            ans = std::min(ans,time);
        }
    }

    // 左右同时拿
    for (int i = 1; i <= n; i ++)
    {
        if (ltr[a[i]] > n/2) break;
        if (ltr.find(k-a[i]) != ltr.end() && k - a[i] != a[i])
        {
            ll time1 = std::max(ltr[a[i]],rtl[k-a[i]]);
            ll time2 = std::max(ltr[k-a[i]],rtl[a[i]]);
            ans = std::min(ans,std::min(time1,time2));
        }
    }
    if (ans != inf) std::cout<<ans<<'\n';
    else std::cout<<-1<<'\n';
    return 0;
}