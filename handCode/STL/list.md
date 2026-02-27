# list 容器

手写 list 容器

```cpp
#include <bits/stdc++.h>

template <typename T>
struct listNode {
    listNode* m_next;
    listNode* m_prev;
    T m_data;

    // 构造函数
    template <typename... ArgsT>
    listNode(ArgsT... args) : m_next(nullptr), m_prev(nullptr), m_data(std::forward<ArgsT>(args)...) {};
};

template <typename T>
struct listIterator {
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;

    listNode<T>* m_node;

    // 使用 explicit，禁止隐式转换
    explicit listIterator(listNode<T>* x) : m_node(x) {}

    reference operator*() { return m_node -> m_data; }
    pointer operator->() { return std::addressof(m_node -> m_data); }

    // 前置++
    listIterator& operator++() {
        m_node = m_node->m_next;
        return *this;
    }
    // 后置++
    listIterator operator++(int) {
        listIterator tmp = *this;
        m_node = m_node->m_next;
        return tmp;
    }
    // 前置--
    listIterator& operator--() {
        m_node = m_node->m_prev;
        return *this;
    }
    // 后置--
    listIterator operator--(int) {
        listIterator tmp = *this;
        m_node = m_node->m_prev;
        return tmp;
    }

    bool operator==(const listIterator& x) const { return m_node == x.m_node; }
    bool operator!=(const listIterator& x) const { return m_node != x.m_node; }
};

template <typename T>
class List {
public:
    using value_type    = T;
    using iterator      = listIterator<T>;

private:
    // 哑节点
    listNode<T>* m_dummy;

    // 初始化空链表
    void init() {
        m_dummy = new listNode<T>(T());
        m_dummy -> m_next = m_dummy;
        m_dummy -> m_prev = m_dummy;
    }

public:
    // 构造函数
    List() {
        this -> init();
    }

    // 析构函数
    ~List() {
        this -> clear();
        delete m_dummy;
    }

    iterator begin() {
        return iterator(m_dummy -> m_next);
    }

    iterator end() {
        return iterator(m_dummy);
    }

    bool empty() const {
        return m_dummy -> m_next == m_dummy;
    }

    // 在指定位置前插入一个节点
    iterator insert(iterator position, const T& x) {
        listNode<T>* newNode = new listNode<T>(x);
        listNode<T>* positionNode = position.m_node;

        newNode -> m_next = positionNode;
        newNode -> m_prev = positionNode -> m_prev;
        positionNode -> m_prev -> m_next = newNode;
        positionNode -> m_prev = newNode;

        return iterator(newNode);
    }

    // 删除指定位置的节点
    iterator erase(iterator position) {
        listNode<T>* positionNode = position.m_node;
        iterator next(positionNode -> m_next);
        positionNode -> m_prev -> m_next = positionNode -> m_next;
        positionNode -> m_next -> m_prev = positionNode -> m_prev;

        delete positionNode;
        return next;
    }

    void push_back(const T& x) {
        insert(this -> end(), x);
    }

    void push_front(const T& x) {
        insert(this -> begin(), x);
    }

    void pop_back() {
        erase(--(this -> end()));
    }

    void pop_front() {
        erase(this -> begin());
    }

    void clear() {
        while (!this -> empty()) {
            erase(this -> begin());
        }
    }

    // 将其他链表的所有节点移动到指定位置前（改指针，不拷贝）
    void splice(iterator position, List& x) {
        if (x.empty()) return;

        listNode<T>* firstNode = x.m_dummy -> m_next;
        listNode<T>* lastNode = x.m_dummy -> m_prev;
        listNode<T>* positionNode = position.m_node;

        x.m_dummy -> m_next = x.m_dummy;
        x.m_dummy -> m_prev = x.m_dummy;

        firstNode -> m_prev = positionNode -> m_prev;
        lastNode -> m_next = positionNode;
        positionNode -> m_prev -> m_next = firstNode;
        positionNode -> m_prev = lastNode;
    }
};

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    for (auto x : myList) std::cout << x << ' ';
    std::cout << '\n';
    myList.push_front(4);
    for (auto x : myList) std::cout << x << ' ';
    std::cout << '\n';
    myList.pop_back();
    for (auto x : myList) std::cout << x << ' ';
    std::cout << '\n';
    List<int> tmpList;
    tmpList.push_back(11);
    tmpList.push_back(22);

    myList.splice(++myList.begin(), tmpList);
    for (auto x : myList) std::cout << x << ' ';
    return 0;
}
```