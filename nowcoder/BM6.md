# BM6.判断链表中是否有环

使用快慢指针，如果有环，最终一定会相遇

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr) return false;
        ListNode *slow = head, *fast = head;
        do
        {
            if(slow -> next != nullptr) slow = slow -> next;
            else return false;
            if(fast -> next != nullptr && fast -> next -> next != nullptr) fast = fast -> next -> next;
            else return false;
        }while(slow != fast);
        return true;
    }
};
```