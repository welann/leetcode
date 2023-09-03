#include<iostream>
#include<vector>
#include<algorithm>
//思路：
//用 距离/速度 的方式得到 时间
//随后按时间进行排序，判断有没有足够时间完成

using namespace std;
class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<float> time(dist.size(),0);
        for(int i=0;i<dist.size();i++){
            time[i]=(float)dist[i]/(float)speed[i];
        }
        sort(time.begin(),time.end());
        int num=0;
        for(int i=0;i<time.size();i++){
            if(time[i]<=i){
                break;
            }
            num++;
        }
        return num;
    }
};

int main(){


    vector<int> dist{3,2,4};
    vector<int> speed{5,3,2};

    Solution ann;
    cout<<ann.eliminateMaximum(dist, speed)<<endl;

    return 0;
}