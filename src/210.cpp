#include <algorithm>
#include <array>
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
#include <type_traits>
#include <vector>

using namespace std;
// 思路 拓扑排序
// 先建立邻接表
// 从第一个数出发，寻找到入度为0的那个数，加入到答案中
// 将邻接表里所有前置条件为这个数的对应位置调整为0
// 重复上述步骤
class Solution {
public:
    vector< int > findOrder( int numCourses, vector< vector< int > >& prerequisites )
    {
        vector< int > ans;
        vector< int > visited( numCourses, 0 );

        if(prerequisites.size()==0){
            for(int i=0;i<numCourses;i++){
                ans.push_back(i);
            }
            return ans;
        }


        vector< vector< int > > graph( numCourses, vector< int >( numCourses, 0 ) );
        for ( auto request : prerequisites ) {
            graph[ request[ 0 ] ][ request[ 1 ] ] = 1;
        }

        for ( auto values : graph ) {
            for ( auto value : values ) {
                cout << value <<" ";
            }
            cout<<endl;
        }

        for(int i=0;i<numCourses;i++){
            for(int j=i;j<numCourses;j++){
                //这里不对，应该用深度优先搜索
                if(graph[i][j]==graph[j][i]&&graph[i][j]==1){
                    return {};
                }
            }
        }


        

        
        for ( int j = 0; j < numCourses; j++ ) {
            for ( int i = 0; i < numCourses; i++ ) {
                if ( visited[ i ] == 0 && search( i, graph ) == true ) {
                    ans.push_back( i );
                    visited[ i ] = 1;
                     deletecourse(i, graph);
                }
            }
           
        }

        return ans;
    }

    inline bool search( int course, vector< vector< int > >& graph )
    {
        for ( auto value : graph[ course ] ) {
            if ( value == 1 ) {
                return false;
            }
        }
        return true;
    }

    void deletecourse( int course, vector< vector< int > >& graph )
    {
        for ( int i = 0; i < graph.size(); i++ ) {
            if ( graph[ i ][ course ] == 1 ) {
                graph[ i ][ course ] = 0;
            }
        }
    }
};

int main(){
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{0,1},{0,2},{1,3},{3,0}};
    Solution slo;
    auto ans=slo.findOrder(numCourses, prerequisites);
    cout<<"ans size: "<<ans.size()<<endl;
    for(auto i :ans){
        cout<<i<<" ";
    }
    return 0;
}