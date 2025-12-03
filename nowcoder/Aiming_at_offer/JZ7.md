# JZ7.重建二叉树

这题在之前上数据结构课的时候，我印象还是比较深的，我记得老师说过，如果要重建一个二叉树，必须给出中序遍历结果，
然后再从前序和后序中挑一个给出，否则将无法重建树。如果只是在纸上画出来倒是没什么问题，但是让我去写一下代码，
现在反而有点懵逼了，也算是一个警醒了吧。

具体的思路如下：

题目给出的函数是 reConstructBinaryTree，传入两个参数：前序数组和中序数组
如果我们只考虑用这两个数组构建找到当前的根结点并区分哪些是左子结点和哪些是右子节点是非常容易的

首先，前序遍历的第一个值必定是根结点

然后我们需要在中序遍历中找到该结点的位置，假设为 i 

此时，中序数组中 i 左侧的为左子节点，右侧的为右子节点

左区间 [ vinOrder.begin(),vinOrder.begin() + i )，右区间 [vinOrder.begin() + i + 1, vinOrder.end() )

显然，左侧长度可知，为 i，那么就可以确定前序遍历中，[ preOrder.begin() + 1, preOrder.begin() + 1 + i ) 为左侧前序序列， [ preOrder.being() + 1 + i, preOrder.end() ) 为右前序序列

然后重新递归调用 reConstructBinaryTree 函数即可

```cpp
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param preOrder int整型vector 
     * @param vinOrder int整型vector 
     * @return TreeNode类
     */
    TreeNode* reConstructBinaryTree(vector<int>& preOrder, vector<int>& vinOrder) {
        int n = preOrder.size();
        int m = vinOrder.size();

        if(n == 0 || m == 0) return nullptr;

        // 构建根结点
        TreeNode* root = new TreeNode(preOrder[0]);
        for (int i = 0; i < vinOrder.size(); i++)
        {
            // 找到中序遍历中的前序第一个元素，确定子结点的根
            if(vinOrder[i] == preOrder[0])
            {
                // 左子树的前序遍历
                std::vector<int> left_preOrder(preOrder.begin() + 1, preOrder.begin() + 1 + i);
                // 左子树的中序遍历
                std::vector<int> left_vinOrder(vinOrder.begin(), vinOrder.begin() + i);
                root -> left = reConstructBinaryTree(left_preOrder, left_vinOrder);
                // 右子树同理
                std::vector<int> right_preOrder(preOrder.begin() + i + 1, preOrder.end());
                std::vector<int> right_vinOrder(vinOrder.begin() + i + 1, vinOrder.end());
                root -> right = reConstructBinaryTree(right_preOrder, right_vinOrder);
                break;
            }
        }
        return root;
    }
};
```