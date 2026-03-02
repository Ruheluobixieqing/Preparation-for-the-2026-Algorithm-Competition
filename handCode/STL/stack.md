# stack 容器

```cpp
#include <bits/stdc++.h>

// 底层容器一般是 deque
template <typename T, typename Container = std::deque<T>>
class Stack {
public:
    // 类型定义
    using value_type                  = T;
    using container_type              = Container;
    using size_type                   = typename Container::size_type;
    using reference                   = typename Container::reference;
    using const_reference             = typename Container::const_reference;

    // 构造函数
    Stack(): c() {}
    explicit Stack(const Container& cont): c(cont) {}
    explicit Stack(Container&& cont): c(std::move(cont)) {}

    // 拷贝构造函数
    Stack(const Stack& other): c(other.c) {}

    // 移动构造函数
    Stack(Stack&& other): c(std::move(other.c)) {}

    // 析构函数
    ~Stack() = default;

    Stack& operator=(const Stack& other) {
        c = other.c;
        return *this;
    }

    Stack& operator=(Stack&& other) {
        c = std::move(other.c);
        return *this;
    }

    // 访问栈顶元素
    reference top() {
        if (empty()) {
            throw std::out_of_range("stack::top: stack is empty");
        }
        return c.back();
    }

    const reference top() const {
        if (empty()) {
            throw std::out_of_range("stack::top: stack is empty");
        }
        return c.back();
    }

    // 检查容器是否为空
    [[nodiscard]] bool empty() const noexcept{
        return c.empty();
    }

    // 返回元素个数
    size_type size() const noexcept {
        return c.size();
    }

    void push(const value_type& value) {
        c.push_back(value);
    }

    void push(value_type&& value) {
        c.push_back(std::move(value));
    }

    // 完美转发的 emplace
    template <typename... Args>
    void emplate(Args... args) {
        return c.push_back(std::forward<Args>(args)...);
    }

    // 弹栈
    // C++ 20 的 pop() 可以返回栈顶值
    void pop() {
        if (empty()) {
            throw std::out_of_range("stack::pop: stack is empty");
        }
        c.pop_back();
    }

    void swap(Stack& other) noexcept (noexcept(std::swap(c, other.c))){
        using std::swap;
        swap(c, other.c);
    }

    // 比较运算符
    friend bool operator==(const Stack& lhs, const Stack& rhs) {
        return lhs.c == rhs.c;
    }

    friend bool operator!=(const Stack& lhs, const Stack& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Stack& lhs, const Stack& rhs) {
        return lhs.c < rhs.c;
    }

    friend bool operator<=(const Stack& lhs, const Stack& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const Stack& lhs, const Stack& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Stack& lhs, const Stack& rhs) {
        return !(lhs < rhs);
    }

private:

// 底层容器，protected，以支持后续继承扩展
protected:
    Container c;

};

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    // 1. 基本操作测试
    std::cout << "=== 基本操作 ===" << std::endl;
    Stack<int> s;

    s.push(10);
    s.push(20);

    std::cout << "栈顶: " << s.top() << std::endl;  // 30
    std::cout << "大小: " << s.size() << std::endl; // 3

    s.pop();
    std::cout << "弹栈后栈顶: " << s.top() << std::endl; // 20

    // 2. 使用不同底层容器
    std::cout << "\n=== 使用 vector 作为底层容器 ===" << std::endl;
    Stack<double, std::vector<double>> s_vec;
    s_vec.push(3.14);
    s_vec.push(2.71);
    std::cout << "vector-stack 栈顶: " << s_vec.top() << std::endl;

    // 3. 使用 list 作为底层容器
    std::cout << "\n=== 使用 list 作为底层容器 ===" << std::endl;
    Stack<std::string, std::list<std::string>> s_list;
    s_list.push("Hello");
    s_list.push("World");
    std::cout << "list-stack 栈顶: " << s_list.top() << std::endl;

    // 4. 拷贝和移动
    std::cout << "\n=== 拷贝和移动 ===" << std::endl;
    auto s2 = s;  // 拷贝
    std::cout << "拷贝后s2栈顶: " << s2.top() << std::endl;

    auto s3 = std::move(s2);  // 移动
    std::cout << "移动后s3栈顶: " << s3.top() << std::endl;
    std::cout << "s2是否为空: " << s2.empty() << std::endl;

    // 5. 比较操作
    std::cout << "\n=== 比较操作 ===" << std::endl;
    Stack<int> a, b;
    a.push(1); a.push(2);
    b.push(1); b.push(2);
    std::cout << "a == b: " << (a == b) << std::endl;
    b.push(3);
    std::cout << "a < b: " << (a < b) << std::endl;

    // 6. 异常处理测试
    std::cout << "\n=== 异常处理 ===" << std::endl;
    Stack<int> empty_stack;
    try {
        empty_stack.pop();  // 应该抛出异常
    } catch (const std::out_of_range& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    // 7. swap
    std::cout << "\n=== swap ===" << std::endl;
    Stack<int> x, y;
    x.push(100);
    y.push(200);
    swap(x, y);  // 使用ADL
    std::cout << "swap后 x.top(): " << x.top() << ", y.top(): " << y.top() << std::endl;

    return 0;
}
```