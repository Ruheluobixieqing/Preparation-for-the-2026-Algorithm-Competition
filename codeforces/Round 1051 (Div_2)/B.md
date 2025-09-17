# B

- 这题需要注意到折扣劵选择的商品可以不是按照输入顺序的，但是没有被囊括过的商品数必须大于等于要用的折扣劵才能使用该劵
- 很显然，当折扣劵的商品选择数为 1 时，可以直接免费取走该商品
- 我们应该希望更贵的商品被免费获取
- 由于每个商品只能被囊括进折扣环节 1 次，然后被免费取走或是必须付款
- 因此可以采取贪心策略
- 打比赛的时候我选择正向排序，后来考虑了一下，反向排序应该更方便一点，因为一定是从 a[0] 开始，不用再通过 a.size() 获取数组长度然后再访问最后一个元素了，本质上没什么区别
- 根据折扣劵需要囊括的商品数，从小到大使用
- 每次使用前先判断剩下数量能不能达到使用条件？
- 若否，ans 逐个加一遍
- 若是，ans 将选中商品中除最便宜的一个外逐个加一遍
- 然后将被涵盖过的商品从 a 数组中删掉就可以了
- 最后，考虑到商品数量很多，折扣劵覆盖不全，还需要把剩余的逐个加一遍

```cpp
#include <bits/stdc++.h>
#define ll long long
const int N = 2e5+3;

void solve()
{
    int n,k;
    std::cin>>n>>k;
    std::vector<int> a(n);
    std::map<int,int> mp;
    for (int i = 0; i < n; i++)
    {
        int num;
        std::cin>>num;
        a.push_back(num);
    }
    for (int i = 0; i < k; i++)
    {
        int num;
        std::cin>>num;
        mp[num]++;
    }
    ll ans = 0;
    std::sort(a.begin(),a.end());
    for (const auto e : mp)
    {
        int time = e.second;
        while (time--)
        {
            if (a.size() >= e.first)
            {
                if (e.first == 1) a.erase(a.end()-1);
                else
                {
                    for (int i = a.size() - 1; i >= a.size() - 1 - e.first + 2; i--) ans += a[i];
                    a.erase(a.end()-e.first,a.end());
                }
            }
        }
    }
    for (const auto e : a) ans += e;
    std::cout<<ans<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int t;
    std::cin>>t;
    while (t--) solve();
    return 0;
}
```