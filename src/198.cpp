#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
// 思路：
// 动态规划
// 递推式：
// weath = max(weath+nums[i-1],weath+numw[i-2])
class Solution {
public:
    int rob( vector< int >& nums )
    {
        vector< int > memo( nums.size(), -1 );

        function< int( int ) > dfs = [ & ]( int i ) -> int {
            if ( i < 0 )
                return 0;  // 递归边界（没有房子）
            if ( memo[ i ] != -1 )
                return memo[ i ];  // 之前计算过
            return memo[ i ] = max( dfs( i - 1 ), dfs( i - 2 ) + nums[ i ] );
        };

        return dfs( nums.size() - 1 );
    }
    // int dfs(vector<int>&nums,int select){
    //     if(select<0){
    //         return 0;
    //     }
    //     return max(dfs(nums,select-2)+nums[select],dfs(nums,select-1));
    // }
};

int main()
{
    Solution      sol;
    vector< int > nums{ 2, 7, 9, 3, 1 };
    cout << sol.rob( nums );
    return 0;
}