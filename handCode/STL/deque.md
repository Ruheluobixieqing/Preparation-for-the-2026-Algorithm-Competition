# deque 容器

```cpp
#include <bits/stdc++.h>

template <typename T, size_t BufSize = 512>
class Deque {
public:
    using value_type         = T;
    using pointer            = T*;
    using reference          = T&;
    using size_type          = size_t;

    // 迭代器（核心！支持随机访问）
    struct iterator {
        T** m_node;      // 指向中控器的某个指针（指向哪个块）
        T*  m_cur;       // 指向块内的当前元素
        T*  m_first;     // 块的起始
        T*  m_last;      // 块的结束（哨兵）

        // 构造函数
        iterator() : m_node(nullptr), m_cur(nullptr), m_first(nullptr), m_last(nullptr) {}

        iterator(T** node, T* cur): m_node(node), m_cur(cur), m_first(*node), m_last(*node + BufSize) {}

        // 解引用
        reference operator*() const {
            return *m_cur;
        }

        pointer operator->() const {
            return m_cur;
        }

        // 前置 ++
        iterator& operator++() {
            ++m_cur;
            if (m_cur == m_last) {
                // 说明是当前块的最后一个位置
                m_node++;
                m_first = *m_node;
                m_last = *m_node + BufSize;
                m_cur = m_first;
            }
            return *this;
        }

        // 后置 ++
        iterator operator++(int) {
            iterator tmp = *this;
            // 调用前置 ++ 移动
            ++(*this);
            return tmp;
        }

        // 前置 --
        iterator& operator--() {
            if (m_cur == m_first) {
                // 说明是当前块的第一个位置
                --m_node;
                m_first = *m_node;
                m_last = *m_node + BufSize;
                m_cur = m_last - 1;
            }
            else --m_cur;
            return *this;
        }

        // 后置 --
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // 随机访问
        iterator& operator+=(size_type n) {
            size_type offset = n + (m_cur - m_first);
            if (offset >=0 && offset < BufSize) {
                // 说明还在同一块内
                m_cur += n;
            }
            else {
                // 先计算在哪个块，这里需要注意负数向零取整的问题，因此还要额外 - 1
                size_type blockOffset = offset > 0 ? offset / BufSize : - ((- offset - 1) / BufSize) - 1;
                m_node += blockOffset;
                m_first = *m_node;
                m_last = *m_node + BufSize;
                m_cur = m_first + (offset - blockOffset * BufSize);
            }
            return *this;
        }

        iterator operator+(size_type n) const {
            iterator tmp = *this;
            tmp += n;
            return tmp;
        }

        size_type operator-(const iterator& x) const {
            return (m_node - x.m_node) * BufSize + (m_cur - m_first) - (x.m_cur - x.m_first);
        }

        bool operator==(const iterator& x) const {
            return m_cur == x.m_cur;
        }

        bool operator!=(const iterator& x) const {
            return m_cur != x.m_cur;
        }

        bool operator<(const iterator& x) const {
            return (m_node < x.m_node) || (m_node == x.m_node && m_cur < x.m_cur);
        }

        bool operator>(const iterator& x) const {
            return (m_node > x.m_node) || (m_node == x.m_node && m_cur > x.m_cur);
        }

        bool operator<=(const iterator& x) const {
            return (m_node < x.m_node) || (m_node == x.m_node && m_cur <= x.m_cur);
        }

        bool operator>=(const iterator& x) const {
            return (m_node > x.m_node) || (m_node == x.m_node && m_cur >= x.m_cur);
        }
    };

private:
    // 中控器，存储指向各块的指针
    T** m_map;                   // 指针数组
    size_type m_mapSize;         // 中控器容量
    size_type m_numElements;     // 元素总数

    iterator m_start;
    iterator m_finish;

    // 分配新块
    T* allocate_new_block() {
        return new T[BufSize];
    }

    // 释放块
    void delete_block(T* p) {
        delete [] p;
    }

    // 初始化 Deque
    void init() {
        m_mapSize = 8;
        m_map = new T*[m_mapSize]();        // 零化初始

        // 中间开始，两端预留空间
        T** start_node = m_map + ( m_mapSize >> 1 );
        *start_node = allocate_new_block();

        m_start = iterator(start_node, *start_node + ( BufSize >> 1 ));
        m_finish = m_start;
        m_numElements = 0;
    }

    // 中控器扩容
    void reallocate_map(size_type needNodes, bool addAtFront) {
        size_type oldNumNodes = m_finish.m_node - m_start.m_node + 1;
        size_type newNumNodes = oldNumNodes + needNodes;

        T** new_start;
        if (m_mapSize > 2 * newNumNodes) {
            new_start = m_map + ((m_mapSize - newNumNodes) >> 1)
                      + (addAtFront ? needNodes : 0);
            if (new_start < m_start.m_node) {
                std::copy(m_start.m_node, m_finish.m_node + 1, new_start);
            } else {
                std::copy_backward(m_start.m_node, m_finish.m_node + 1,
                                  new_start + oldNumNodes);
            }
        } else {
            size_type newMapSize = m_mapSize + std::max(m_mapSize, needNodes) + 2;
            T** newMap = new T*[newMapSize]();
            new_start = newMap + ((newMapSize - newNumNodes) >> 1)
                      + (addAtFront ? needNodes : 0);
            std::copy(m_start.m_node, m_finish.m_node + 1, new_start);
            delete[] m_map;
            m_map = newMap;
            m_mapSize = newMapSize;
        }

        // 统一更新迭代器（关键！）
        m_start.m_node = new_start;
        m_finish.m_node = new_start + oldNumNodes - 1;

        // 保持块内指针有效
        m_start.m_first = *m_start.m_node;
        m_start.m_last = m_start.m_first + BufSize;
        m_finish.m_first = *m_finish.m_node;
        m_finish.m_last = m_finish.m_first + BufSize;

        if (addAtFront) {
            for (size_type i = 0; i < needNodes; ++i) {
                *(--m_start.m_node) = allocate_new_block();
            }
            m_start.m_first = *m_start.m_node;
            m_start.m_last = m_start.m_first + BufSize;
            m_start.m_cur = m_start.m_last - 1;
        }
    }

public:
    // 构造函数
    Deque() {
        init();
    }

    ~Deque() {
        clear();
        for (T** current = m_start.m_node; current <= m_finish.m_node; current ++) {
            delete_block(*current);
        }
        delete [] m_map;
    }

    iterator begin() {
        return m_start;
    }

    iterator end() {
        return m_finish;
    }

    size_type size() const {
        return m_numElements;
    }

    bool empty() const {
        return m_numElements == 0;
    }

    // 随机访问
    reference operator[](size_type n) {
        return *(m_start + n);
    }

    reference front() {
        return *m_start;
    }

    reference back() {
        return *(m_finish - 1);
    }

    void clear() {
        // 销毁所有元素，但保留块结构
        while (!empty()) pop_back();
    }

    void pop_back() {
        if (m_finish.m_cur != m_finish.m_first) {
            --m_finish.m_cur;
        } else {
            // 释放空块
            delete_block(*m_finish.m_node);
            --m_finish.m_node;
            m_finish.m_first = *m_finish.m_node;
            m_finish.m_last = m_finish.m_first + BufSize;
            m_finish.m_cur = m_finish.m_last - 1;
        }
        --m_numElements;
    }

    void pop_front() {
        if (m_start.m_cur != m_start.m_last - 1) {
            ++m_start.m_cur;
        } else {
            delete_block(*m_start.m_node);
            ++m_start.m_node;
            m_start.m_first = *m_start.m_node;
            m_start.m_last = m_start.m_first + BufSize;
            m_start.m_cur = m_start.m_first;
        }
        --m_numElements;
    }

    void push_back(const T& x) {
        if (m_finish.m_cur != m_finish.m_last - 1) {
            // 说明当前块仍有空间
            *m_finish.m_cur = x;
            ++ m_finish.m_cur;
        }
        else {
            // 需要使用新块
            if (m_finish.m_node + 1 == m_map + m_mapSize) reallocate_map(1, false);

            *(++m_finish.m_node) = allocate_new_block();
            **m_finish.m_node = x;
            m_finish.m_first = *m_finish.m_node;
            m_finish.m_cur = m_finish.m_first + 1;
            m_finish.m_last = m_finish.m_first + BufSize;
        }
        ++m_numElements;
    }

    void push_front(const T& x) {
        if (m_start.m_cur != m_start.m_first) {
            // 当前块前面还有空间
            *--m_start.m_cur = x;
        } else {
            // 需要新块
            if (m_start.m_node == m_map) reallocate_map(1, true);
            *(--m_start.m_node) = allocate_new_block();
            m_start.m_first = *m_start.m_node;
            m_start.m_last = m_start.m_first + BufSize;
            m_start.m_cur = m_start.m_last - 1;
            *m_start.m_cur = x;
        }
        ++m_numElements;
    }
};

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    Deque<int> dq;

    // 测试头尾插入
    dq.push_back(1);   // [1]
    dq.push_front(0);  // [0, 1]
    dq.push_back(2);   // [0, 1, 2]
    dq.push_front(-1); // [-1, 0, 1, 2]

    std::cout << "Size: " << dq.size() << "\n";  // 4

    // 测试随机访问
    std::cout << "dq[0]=" << dq[0] << ", dq[2]=" << dq[2] << "\n";  // -1, 1

    // 测试迭代器遍历
    std::cout << "遍历: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";  // -1 0 1 2

    // 测试头尾删除
    dq.pop_front();  // [0, 1, 2]
    dq.pop_back();   // [0, 1]

    std::cout << "After pop: ";
    for (size_t i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }
    std::cout << "\n";  // 0 1
    return 0;
}
```