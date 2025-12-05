# JZ9.用两个栈实现队列

```cpp
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        while(stack1.size() > 1)
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        int num = stack1.top();
        stack1.pop();
        while(stack2.size())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return num;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```