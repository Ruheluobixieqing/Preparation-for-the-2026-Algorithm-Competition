#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    long long delta = 0;
    int sign = 1;               // 当前真实值 = sign * x + delta，x 初值为 0
    for (int i = 0; i < n; ++i) {
        long long red  = delta - sign * a[i];
        long long blue = b[i] - delta;
        if (red > blue) {       // 选红更优
            delta = red;
        } else {                // 选蓝更优
            delta = blue;
            sign = -sign;       // 翻转符号
        }
    }
    cout << delta << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}