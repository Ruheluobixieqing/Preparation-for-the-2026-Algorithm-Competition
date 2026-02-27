# vector 容器

手写 vector 容器

```cpp
#include <bits/stdc++.h>

/* Vector 容器
 * 作为容器，vector 需要提供迭代器 iterator,.begin(),.end()
 * allocator 参数告诉 vector 如何分配、释放内存
 * vector 是一个连续的容器，其中的元素都是相邻的，可以通过 .data() 获取第一个元素的指针，通过 .size() 获取数据长度，通过 .capacity() 获取已经分配的空间
 */

template<typename ValueT>
class Vector {
public:
    using value_type                      = ValueT;
    using reference                       = ValueT&;
    using const_reference                 = const ValueT&;

    using iterator                        = ValueT*;
    using const_iterator                  = const ValueT*;

    using size_type                       = size_t;
    using difference_type                 = ptrdiff_t;

private:
    ValueT* m_data;
    size_t m_size;
    size_t m_capacity;

public:
    // 默认构造函数
    Vector() noexcept{
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // 析构函数
    ~Vector() {
        // vector 的内存是 vector 自己管理的，现在只销毁元素而不能直接销毁内存，因此不能使用 delete，必须显示调用每一个元素的析构函数
        this -> _delete_and_release();
    }

    // 复制构造函数（深拷贝）
    Vector(const Vector& vec) {
        this -> m_data = static_cast<ValueT*>(::operator new(vec.m_capacity * sizeof(ValueT)));

        this -> m_size = 0;
        this -> m_capacity = vec.m_capacity;

        // 考虑异常安全
        try {
            // 不能直接用 this -> m_data[k] = vec.m_data[k]
            // 此时 m_data 指向的是未初始化的原始内存，其中没有已经构造好的 ValueT 对象，直接使用 m_data[k] 访问的是未构造对象
            // 因此需要在指定地址构造新对象，而不是直接赋值
            for (size_t k = 0; k < vec.m_size; k++) {
                new(&this -> m_data[k]) ValueT(vec.m_data[k]);
                this -> m_size += 1;
            }
        }
        catch (...) {
            // 如果构造时发生了异常抛出，需要析构已经构造的元素，并释放内存
            for (size_t k = 0; k < this -> m_size; k ++) this -> m_data[k].~ValueT();
            ::operator delete(this -> m_data);
            throw;
        }
    }

    // 移动构造函数
    Vector(Vector&& vec) noexcept {
        this -> m_data = vec.m_data;
        this -> m_size = vec.m_size;
        this -> m_capacity = vec.m_capacity;

        vec.m_data = nullptr;
        vec.m_size = 0;
        vec.m_capacity = 0;
    }

    // 重载操作符
    Vector& operator = (const Vector& vec) {
        /* 例如 vec1 = vec2
         * 如果 vec2.size() <= vec1.size()，那么不会改变 vec1 的 capacity
         * 如果 vec2.size() > vec1.size()，那么会重新给 vec1 分配 vec2.size() 的大小，而不是会基于 vec1 原来的大小进行扩展
         * 如果赋值成功，那么 vec1 的首地址也会改变
         */

        // 自赋值检查
        if (this == &vec) return *this;

        if (vec.m_size <= this -> capacity()) {
            // 直接赋值
            for (size_t k = 0; k < vec.m_size; k ++) this -> m_data[k] = vec.m_data[k];
            // 销毁多余的数据
            for (size_t k = vec.m_size; k < this -> m_size; k ++) this -> m_data[k].~ValueT();
            return *this;
        }
        else {
            // 重新分配内存
            ValueT* new_data = static_cast<ValueT*>(::operator new(vec.m_size * sizeof(ValueT)));

            size_t new_size = 0;

            try {
                for (size_t k = 0; k < vec.m_size; k++) {
                    new(&new_data[k]) ValueT(vec.m_data[k]);
                    new_size += 1;
                }

                this -> _delete_and_release();

                this -> m_data = new_data;
                this -> m_capacity = vec.m_size;
                this -> m_size = new_size;

                return *this;
            }
            catch (...) {
                for (size_t k = 0; k < new_size; k ++) new_data[k].~ValueT();
                ::operator delete(new_data);
                throw;
            }
        }
    }

private:
    void _delete_and_release() noexcept {
        this -> clear();
        ::operator delete(this -> m_data);
        this -> m_data = nullptr;
    }

public:
    // 实现 iterators
    iterator begin() noexcept {
        return this -> m_data;
    }

    const_iterator begin() const noexcept {
        return this -> m_data;
    }

    iterator end() noexcept {
        return this -> m_data + this -> m_size;
    }

    const_iterator end() const noexcept {
        return this -> m_data + this -> m_size;
    }

    // accessor
    value_type* data() noexcept {
        return this -> m_data;
    }

    value_type* data() const noexcept {
        return this -> m_data;
    }

    size_type size() noexcept {
        return this -> m_size;
    }

    size_type capacity() noexcept {
        return this -> m_capacity;
    }

    bool empty() const noexcept {
        return this -> m_size == 0;
    }

    // modifier
    void clear() noexcept {
        for (size_t k = 0; k < this -> m_size; k++) this -> m_data[k].~ValueT();
        this -> m_size = 0;
    }

    void pop_back() noexcept {
        assert(!this -> empty());
        size_t k = this -> m_size - 1;
        this -> m_data[k].~ValueT();
        this -> m_size -= 1;
    }

    void push_back(const ValueT& value) {
        this -> emplace_back(value);
    }

    void push_back(ValueT&& value) {
        this -> emplace_back(std::move(value));
    }

    template<typename ... ArgsT> reference emplace_back(ArgsT&&... args) {
        // 如果还有内存可以使用
        if (this -> m_size < this -> m_capacity) {
            // 计算下一个元素应该放的位置的下标
            size_t k = this -> m_size;
            ::new(&this -> m_data[k]) ValueT(std::forward<ArgsT>(args)...);
            this -> m_size += 1;
            return this -> m_data[k];
        }

        // 需要重新分配内存
        size_t new_capacity = this -> m_capacity;
        if (this -> m_capacity > 0) new_capacity <<= 1;
        else new_capacity += 1;

        //std::cout << "allocate mem:" << this ->

        size_t new_size = 0;

        auto new_data = static_cast<ValueT*>(::operator new(new_capacity * sizeof(ValueT)));

        // 考虑异常安全
        try {
            // 不能直接用 this -> m_data[k] = vec.m_data[k]
            // 此时 m_data 指向的是未初始化的原始内存，其中没有已经构造好的 ValueT 对象，直接使用 m_data[k] 访问的是未构造对象
            // 因此需要在指定地址构造新对象，而不是直接赋值
            for (size_t k = 0; k < this -> m_size; k++) {
                new(&new_data[k]) ValueT(std::move(this -> m_data[k]));
                new_size += 1;
            }

            new(&new_data[new_size]) ValueT(std::forward<ArgsT>(args)...);
            new_size += 1;
        }
        catch (...) {
            // 如果构造时发生了异常抛出，需要析构已经构造的元素，并释放内存
            for (size_t k = 0; k < new_size; k ++) new_data[k].~ValueT();
            ::operator delete(new_data);
            throw;
        }

        // 清除旧数据
        this -> _delete_and_release();

        this -> m_data = new_data;
        this -> m_size = new_size;
        this -> m_capacity = new_capacity;
        return this -> m_data[new_size];
    }
};

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    Vector<int>a;
    std::cout << &a << '\n';
    a.push_back(1);
    a.push_back(2);
    std::cout<<a.capacity()<<'\n';
    Vector<int>b;
    b.push_back(3);
    b.push_back(4);
    b.push_back(10);
    std::cout<< b.size() << '\n';
    a = b;
    std::cout<< a.capacity() << '\n';
    std::cout<< b.capacity() << '\n';
    a.push_back(0);
    std::cout<< a.capacity() << '\n';
    a.push_back(10);
    std::cout<< a.capacity() << '\n';
    return 0;
}
```