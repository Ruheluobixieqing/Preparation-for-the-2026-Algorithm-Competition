#include <bits/stdc++.h>
int K;
std::vector<std::vector<char>> graph;
std::vector<int> Seq;

// 初始加密逆向

// 加密过程：
// 对于一个 n x m 的图
// 先补成一个 Z x Z 的正方形图，补充的位置用 '?' 表示，其中 Z >= std::max(n ,m)
// 取第 n ～ m 行，对于每一行，左右对称翻转参数
// 逆向过程：
//
std::pair<int,int> encryption_reverse(){
    int row = 0, column = 0;

    return std::pair<int, int>(row, column);
}

// 旋转加密逆向
void rotation_reverse(int u, int v, int L, int d, int r){

}

// 翻转加密逆向
void inversion_reverse(int u, int d, int l, int r, int o){

}


int main(){
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    std:: cin >> K;
    graph = std::vector<std::vector<char>>(K + 1, std::vector<char>(K + 1));

    for (int i = 1; i <= K; i ++) for (int j = 1; j <= K; j ++) std::cin >> graph[i][j];

    int k;
    std::cin >> k;
    Seq = std::vector<int>(k);
    for (int i = 0; i < k; i ++) std::cin >> Seq[i];

    int right = k - 1, left = right - 5;

    while (left > 0){
        int op = Seq[left];
        if (op == 1) rotation_reverse(Seq[left + 1], Seq[left + 2], Seq[left + 3], Seq[left + 4], Seq[left + 5]);
        else inversion_reverse(Seq[left + 1], Seq[left + 2], Seq[left + 3], Seq[left + 4], Seq[left + 5]);
        right -= 6, left -= 6;
    }

    std::pair<int, int> data = encryption_reverse();

    std::cout<< data.first << " " << data.second << '\n';
    for (int i = 1; i <= data.first; i++){
        for (int j = 1; j <= data.second; j++) std::cout << graph[i][j];
        std::cout << '\n';
    }

    return 0;
}