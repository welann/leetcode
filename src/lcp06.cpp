#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minCount(vector<int>& coins) {
        int ans=0;
        for(auto coin:coins){
            if(coin%2==0){
                ans+=coin/2;
            }else{
                ans+=(coin+1)/2;
            }
        }
        return ans;
    }
};



int main(){
    vector<int> coins{2,3,10};
    Solution sol;
    cout<<sol.minCount(coins);

    return 0;
}








