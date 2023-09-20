#include<bits/stdc++.h>

using namespace std;

//思路，不会
//要算的是：偷走的最大金额 需要越小越好
//


class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int lower = *min_element(nums.begin(), nums.end());
        int upper = *max_element(nums.begin(), nums.end());
        while (lower <= upper) {
            int middle = (lower + upper) / 2;
            int count = 0;
            bool visited = false;//这里是用来判断相邻的房间不能偷
            //这里是计算在middle为上界的情况下，一轮能不能找到至少 k 个符合条件的房间
            for (int x : nums) {
                if (x <= middle && !visited) {
                    count++;
                    visited = true;
                } else {
                    visited = false;
                }
            }
            //判断是否有k个符合条件的房间
            //不符合的话说明此时的middle小了，需要增加
            //否则就说明此时的middle大了，需要减少
            //就这样二分求解，直到找到一个恰好的解
            if (count >= k) {
                upper = middle - 1;
            } else {
                lower = middle + 1;
            }
        }
        return lower;
    }
};



int main(){



    return 0;
}