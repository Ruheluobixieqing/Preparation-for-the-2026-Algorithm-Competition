# A

- 我一开始拿到这题目，以为是必须满足 (1,......,2) 或 (2,......,1)
- 然后头尾删除不管，往内变成必须满足 (3,......,4) 或 (4,......,3)
- 于是按照这个思路写了一份

```cpp
#include <bits/stdc++.h>
#define ll long long
const int N = 1e2 + 3;
 
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(N);
    for (int i = 1 ;i <= n; i++)
    {
        int k;
        std::cin>>k;
        a[i] = k;
    }
    int tag = 1;
    int left = 1,right = n;
    while (left < right)
    {
        if ((a[left] == tag && a[right] == tag + 1)||(a[left] == tag + 1 && a[right] == tag))left++,right--,tag+=2;
        else
        {
            std::cout<<"NO"<<'\n';
            return;
        }
    }
    std::cout<<"YES"<<'\n';
    return;
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

- 交上去发现 pretest 2 就报错了，只是过了题目给的样例
- 于是我开始重新思考这个问题
- 突然间我想到，既然最后一步一定是变成 (1,1,1,...,1,1)，那么前一步就只能是 (1,2,2,...,2,2) 或者 (2,2,2,...,2,1)
- 此时如果不再考虑作为左或右边界的 1，那么现在相当于有了 (2,2,2,...,2)，再往前一步就只能是 (2,3,3,...,3,3) 或 (3,3,3,...,3,2)
- 这个时候，规律就出现了：
- 对于一个给定的数组 a1,a2,a3...an,我需要进行 k = 1,2,3....n-1 的操作；反过来，我需要对数组 (1,1,1,...1) 进行操作，使其能够变为 a1,a2,a3,...an
- 那么在反向操作时，每一次的操作都会导致最外侧的左右其中之一保持原数，剩余数字加 1
- 那么这个时候，忽略该边界，就又可以重复该操作
- 由此，本题可解：
- 令 tag 初始化为 1,
- 检测 1 是否出现在 vector 的左 / 右边界处
- 若是，删除该边界，重复上述操作直至 tag == n，即只剩余 1 个数，此时可以输出 YES
- 若否，直接输出 NO

```cpp
#include <bits/stdc++.h>
#define ll long long
const int N = 1e2 + 3;

void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> num;
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin>>x;
        num.push_back(x);
    }
    int tag = 1;
    while (tag < n)
    {
        int len = num.size();
        if (num[0] == tag) num.erase(num.begin());
        else if (num[len-1] == tag) num.erase(num.end()-1);
        else
        {
            std::cout<<"NO"<<'\n';
            return;
        }
        tag++;
    }
    std::cout<<"YES"<<'\n';
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