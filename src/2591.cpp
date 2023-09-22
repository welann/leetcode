#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
//思路：先按照8和1 进行分配
//此时应该获得最多的8
//然后再分配剩下的东西（因为此时条件限制不会产生亏欠
//

//思路倒了，应该先分配最多的1
    int distMoney(int money, int children) {
        if (money < children) {
            return -1;
        }
        money -= children;
        int cnt = min(money / 7, children);
        money -= cnt * 7;
        children -= cnt;
        if ((children == 0 && money > 0) || (children == 1 && money == 3)) {
            cnt--;
        }
        return cnt;
    }
};

int main(){
    Solution sol;
    cout<<sol.distMoney(199, 4);

    return 0;
}