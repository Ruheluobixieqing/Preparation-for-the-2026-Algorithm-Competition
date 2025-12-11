#include <bits/stdc++.h>
const int N = 1e3+4;

int main(){
  std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
  int n;
  std::cin>>n;
  std::vector<int> v(n+1);
  std::vector<int> dp(n+1,1);
  std::vector<int> ans(n+1,1);
  int _ans = 1;
  for(int i = 1; i <= n; i++) std::cin >> v[i];
  for(int i = 1; i <= n; i++){
    for(int j = 1; j < i; j++){
      if(v[i] > v[j] && dp[j] + 1 > dp[i]){
        dp[i] = dp[j] + 1;
        ans[i] = ans[j];
      }
      if (v[i] > v[j] && dp[j] + 1 == dp[i])
      {
        ans[i] += ans[j];
      }
    }
    if (_ans < dp[i]) _ans = dp[i];
  }
  int cnt = 0;
  for (const auto &e: ans) if (e == _ans) cnt++;
  std::cout << cnt << '\n';
  return 0;
}