# 快速排序

```cpp
#include <bits/stdc++.h>
const int N = 1e5 + 3;
int a[N];

int partition(int a[], int l, int r)
{
    int pivot = a[r];
    int i = l, j = r;
    while (i < j)
    {
        while (i < j && a[i] <= pivot) i++;
        while (i < j && a[j] >= pivot) j--;

        if (i < j) std::swap(a[i], a[j]);
        else std::swap(a[i], a[r]);
    }
}

void quickSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = partition(a, l, r);
        quickSort(a, l, mid - 1);
        quickSort(a, mid + 1, r);
    }
}

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    quickSort(a, 1, n);
    for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
    return 0;
}
```