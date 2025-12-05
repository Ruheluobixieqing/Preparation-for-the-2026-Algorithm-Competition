# JZ8.二叉树的下一个结点

作为二叉树中的一个结点，它可能具有：左儿子、右儿子、父结点

因为本题要找中序遍历的下一个结点，那么其是否具有左儿子并不影响结果

首先考虑其是否具有右儿子，如果有，那么找到右子树的最左结点即可

如果其不具有右儿子，那么就要考虑其为其父结点的左儿子还是右儿子

若该结点为其父结点的左儿子，那么其父结点就是下一个要遍历到的结点（因为该结点因为没有右儿子了）

若该结点为其父结点的右儿子，那么就需要向上寻找，将该结点替换为父节点并继续向上寻找新的父节点，直到找到左儿子为该结点的父节点，返回父节点即可

若最终没有找到，返回空

```cpp
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if(pNode == nullptr) return nullptr;
        if(pNode -> right == nullptr) 
        {
            if(pNode -> next == nullptr) return nullptr;
            TreeLinkNode *fatherNode = pNode -> next;
            while(fatherNode && fatherNode -> right == pNode)
            {
                pNode = fatherNode;
                fatherNode = fatherNode -> next;
            }
            return fatherNode;
        }
        else
        {
            pNode = pNode -> right;
            while(pNode -> left) pNode = pNode -> left;
            return pNode;
        }
    }
};
```