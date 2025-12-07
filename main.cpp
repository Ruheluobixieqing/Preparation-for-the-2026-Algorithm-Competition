#include <bits/stdc++.h>

std::string int_to_binary_string(int num, int n) {
    std::string result;
    for (int i = n - 1; i >= 0; --i) {
        result += (num & (1 << i)) ? '1' : '0';
    }
    return result;
}

int main() {
    int num = 156;
    int n = 8;
    std::string binary = int_to_binary_string(num, n);
    std::cout << binary << std::endl;  // 输出：00000101
    return 0;
}