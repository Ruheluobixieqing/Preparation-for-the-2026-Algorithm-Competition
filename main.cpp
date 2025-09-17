#include <bits/stdc++.h>
#define ll long long
const int N = 2e5+3;
struct edge
{
    int u,v,x,y;
};

bool cmp(const edge& a, const edge& b)
{
    int abs_a = abs(a.y - a.x);
    int abs_b = abs(b.y - b.x);
    
    if (abs_a != abs_b)
        return abs_a > abs_b;
    
    int mx_a = std::max(a.x, a.y);
    int mx_b = std::max(b.x, b.y);
    return mx_a > mx_b;
}

void solve()
{
    int n;
    std::cin>>n;
    std::vector<edge> v;
    for (int i = 1; i < n;i++)
    {
        edge e;
        std::cin>>e.u>>e.v>>e.x>>e.y;
        v.push_back(e);
    }
    std::sort(v.begin(), v.end(), cmp);
    
    // 记录节点间的相对位置关系：pos[i][j] = true 表示 i < j
    std::map<std::pair<int,int>, bool> pos;
    ll ans = 0;
    
    for (const auto& e : v) {
        int u = e.u, v_node = e.v, x = e.x, y = e.y;
        
        // 确定哪个值更大
        bool x_larger = (x >= y);
        int larger_val = x_larger ? x : y;
        int smaller_val = x_larger ? y : x;
        
        // 取较大值需要的相对位置条件
        bool need_u_less_v = x_larger; // 取x需要u<v，取y需要u>v
        
        // 检查是否已经有这对节点的相对位置记录
        bool has_order = false;
        bool current_u_less_v = false;
        
        if (pos.count({std::min(u, v_node), std::max(u, v_node)})) {
            has_order = true;
            if (u < v_node) {
                current_u_less_v = pos[{u, v_node}];
            } else {
                current_u_less_v = !pos[{v_node, u}];
            }
        }
        
        // 判断能否取较大值
        if (!has_order) {
            // 没有先前的约束，可以取较大值并设定相对位置
            ans += larger_val;
            if (u < v_node) {
                pos[{u, v_node}] = need_u_less_v;
            } else {
                pos[{v_node, u}] = !need_u_less_v;
            }
        } else {
            // 已有相对位置约束，检查是否矛盾
            if (current_u_less_v == need_u_less_v) {
                // 不矛盾，可以取较大值
                ans += larger_val;
            } else
            {
                // 矛盾，只能取较小值
                ans += smaller_val;
            }
        }
    }
    
    // 根据确定的相对位置生成排序序列
    std::set<int> all_nodes;
    for (const auto& e : v) {
        all_nodes.insert(e.u);
        all_nodes.insert(e.v);
    }
    
    // 构建有向图和入度数组
    std::map<int, std::vector<int>> graph;
    std::map<int, int> in_degree;
    
    // 初始化
    for (int node : all_nodes) {
        graph[node] = std::vector<int>();
        in_degree[node] = 0;
    }
    
    // 根据相对位置构建有向边
    for (const auto& p : pos) {
        int u = p.first.first;
        int v = p.first.second;
        bool u_less_v = p.second;
        
        // 注意：u 总是小于 v（因为我们用的是 min, max 存储）
        // u_less_v = true 表示实际顺序是 u < v
        // u_less_v = false 表示实际顺序是 u > v，即 v < u
        if (u_less_v) {
            // u < v，添加边 u -> v
            graph[u].push_back(v);
            in_degree[v]++;
        } else {
            // v < u，添加边 v -> u  
            graph[v].push_back(u);
            in_degree[u]++;
        }
    }
    
    // 拓扑排序
    std::queue<int> q;
    std::vector<int> result;
    
    // 将入度为0的节点入队
    for (const auto& p : in_degree) {
        if (p.second == 0) {
            q.push(p.first);
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        // 遍历u的所有邻接节点
        for (int v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // 输出结果
    // std::cout << ans << "\n";
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << result[i];
    }
    std::cout << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int t;
    std::cin>>t;
    while (t--) solve();
    return 0;
}