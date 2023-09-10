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

/*
class Solution {
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    vector<int> visited;
    // 用数组来模拟栈，下标 0 为栈底，n-1 为栈顶
    vector<int> result;
    // 判断有向图中是否有环
    bool valid = true;

public:
    void dfs(int u) {
        // 将节点标记为「搜索中」
        visited[u] = 1;
        // 搜索其相邻节点
        // 只要发现有环，立刻停止搜索
        for (int v: edges[u]) {
            // 如果「未搜索」那么搜索相邻节点
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            // 如果「搜索中」说明找到了环
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        // 将节点标记为「已完成」
        visited[u] = 2;
        // 将节点入栈
        result.push_back(u);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        if (!valid) {
            return {};
        }
        // 如果没有环，那么就有拓扑排序
        // 注意下标 0 为栈底，因此需要将数组反序输出
        reverse(result.begin(), result.end());
        return result;
    }
};

*/