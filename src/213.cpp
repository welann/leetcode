#include<bits/stdc++.h>

using namespace std;

// 1 2 3 4 5 6 7 8 9
//思路
//这道题和前面一个很像
//由于第一个和最后一个不能一起选，可以分成两个问题
//1. 选第一个，然后遍历到倒数第二个
//2. 选最后一个，然后从第二个开始遍历

class Solution {
public:

    int robRange(vector<int>& nums, int start, int end) {
        int first = nums[start], second = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++) {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        return second;
    }

    int rob(vector<int>& nums) {
        int length = nums.size();
        if (length == 1) {
            return nums[0];
        } else if (length == 2) {
            return max(nums[0], nums[1]);
        }
        return max(robRange(nums, 0, length - 2), robRange(nums, 1, length - 1));

    }
};

int main(){

}













