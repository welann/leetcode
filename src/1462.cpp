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
#include <unordered_map>
#include <vector>

using namespace std;
// 思路

//用拓扑排序
//排序玩了之后判断先后关系就行了
vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> g(numCourses);
        vector<int> indgree(numCourses, 0);
        vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses, false));
        for (auto& p : prerequisites) {
            ++indgree[p[1]];
            g[p[0]].push_back(p[1]);
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indgree[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto& ne : g[cur]) {
                isPre[cur][ne] = true;
                for (int i = 0; i < numCourses; ++i) {
                    isPre[i][ne] = isPre[i][ne] | isPre[i][cur];
                }
                --indgree[ne];
                if (indgree[ne] == 0) {
                    q.push(ne);
                }
            }
        }
        vector<bool> res;
        for (auto& query : queries) {
            res.push_back(isPre[query[0]][query[1]]);
        }
        return res;
    }

//以下思路超时
// 如果前置条件为空的话，返回一个n大小的false数组
// 建立一个邻接表，随后对每一个查询都进行广度优先搜索，查看对应的课程是否为前置条件

// 超时了，可以优化一下
// bfs的时候就把已经算出来的先后关系放在一个新的邻接表中
// g[a][b]==1的话那么b是a的必修
// 可以在原本的  graph 上直接修改了

class Solution {
public:
    vector< bool > checkIfPrerequisite( int numCourses, vector< vector< int > >& prerequisites, vector< vector< int > >& queries )
    {
        vector< bool > ans;
        if ( prerequisites.empty() ) {
            for ( auto query : queries ) {
                ans.push_back( false );
            }
            return ans;
        }

        vector< vector< int > > graph( numCourses, vector< int >( numCourses, 0 ) );
        for ( int i = 0; i < prerequisites.size(); i++ ) {
            // prerequisites[i] = [ai, bi] 表示如果你想选 bi 课程，你 必须 先选 ai 课程
            graph[ prerequisites[ i ][ 1 ] ][ prerequisites[ i ][ 0 ] ] = 1;
        }

        for ( auto grap : graph ) {
            for ( auto g : grap ) {
                cout << g << " ";
            }
            cout << endl;
        }

        for ( auto query : queries ) {
            ans.push_back( bfs( query[ 1 ], query[ 0 ], graph ) );
        }

        return ans;
    }

    bool bfs( int a, int b, vector< vector< int > >& graph )
    {
        if ( graph[ a ][ b ] == 1 )
            return true;
        queue< int > que;

        // vector< vector< int > > visited( graph.size(), vector< int >( graph.size(), 0 ) );
        vector< int > visited( graph.size(), 0 );
        visited[ a ] = 1;

        for ( int i = 0; i < graph[ a ].size(); i++ ) {
            if ( graph[ a ][ i ] == 1 && visited[ i ] == 0 ) {

                graph[ a ][ i ] = 1;
                visited[ i ]    = 1;
                que.push( i );
            }
        }

        while ( !que.empty() ) {
            int temp = que.front();
            for ( int i = 0; i < graph[ temp ].size(); i++ ) {
                if ( graph[ temp ][ i ] == 1 && visited[ i ] == 0) {
                    if ( i == b ) {
                        return true;
                    }
                    else {
                        if ( visited[ i ] == 0 ) {
                            que.push( i );
                        }
                    }
                }
            }
            que.pop();
        }
        return false;
    }
};
int main()
{
    int                     numCourses    = 5;
    vector< vector< int > > prerequisites = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } };
    vector< vector< int > > queries       = { { 0, 4 }, { 4, 0 }, { 1, 3 }, { 3, 0 } };
    Solution                sol;
    auto                    temp = sol.checkIfPrerequisite( numCourses, prerequisites, queries );
    for ( auto tem : temp ) {
        cout << tem << " ";
    }
    return 0;
}