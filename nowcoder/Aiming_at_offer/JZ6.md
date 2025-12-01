# JZ6.从尾到头打印链表

这题思路非常多

1.可以在遍历链表的时候用栈存储元素，然后再逐个弹出，就是倒序了
```cpp
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        std::vector<int> arr;
        ListNode* p = head;
        std::stack<int> st;
        while(p != nullptr)
        {
            st.push(p -> val);
            p = p -> next;
        }
        while(!st.empty())
        {
            arr.push_back(st.top());
            st.pop();
        }
        return arr;
    }
};
```

2.可以在遍历链表的时候直接加入数组，最后直接反转数组即可
```cpp
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        std::vector<int> arr;
        ListNode* p = head;
        while(p != nullptr)
        {
            arr.push_back(p -> val);
            p = p -> next;
        }
        std::reverse(arr.begin(), arr.end());
        return arr;
    }
};
```