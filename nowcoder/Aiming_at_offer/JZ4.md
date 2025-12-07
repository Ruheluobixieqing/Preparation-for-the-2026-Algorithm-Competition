# JZ4.二维数组中的查找

```cpp
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param target int整型 
     * @param array int整型vector<vector<>> 
     * @return bool布尔型
     */
    bool Find(int target, vector<vector<int> >& array) {
        int n = array.size();
        int m = array[0].size();
        int x = n - 1, y = 0;
        while(x >= 0 && y < m){
            if(array[x][y] == target) return true;
            if(array[x][y] < target) y++;
            else x --;
        }
        return false;
    }
};
```