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
#include <utility>
#include <vector>

using namespace std;
// 思路
// 编码所有8种（其中4可以对称过来）可行的移动方案
// 对每个格子遍历，如果遍历到的各自与当前所处的格子数值之间差距超过1，则不可完成

//这里有个文字游戏：必须从左上角出发，所以遇到不是从左上角出发的直接判定为失败就行
class Solution {
public:
    bool checkValidGrid( vector< vector< int > >& grid )
    {
        if(grid[0][0]!=0) return false;
        vector< pair< int, int > > nextchoice{ { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 }, { -1, -2 }, { -2, -1 }, { -2, 1 }, { -1, 2 } };
        int                        n = grid.size();

        pair< int, int > startpoint {0,0};

        for ( int i = 0; i < n * n - 1; i++ ) {
            for ( int j = 0; j < 8; j++ ) {
                if ( startpoint.first + nextchoice[ j ].first < 0 || startpoint.second + nextchoice[ j ].second < 0 || startpoint.first + nextchoice[ j ].first >= n
                     || startpoint.second + nextchoice[ j ].second >= n ) {
                    continue;
                }
                int newx = startpoint.first + nextchoice[ j ].first, newy = startpoint.second + nextchoice[ j ].second;

                cout << "x: " << startpoint.first << " y: " << startpoint.second << " value: " << grid[ startpoint.first ][ startpoint.second ] << endl;
                cout << "newx: " << newx << " newy: " << newy << " value: " << grid[ newx ][ newy ] << endl;

                if ( grid[ newx ][ newy ] - grid[ startpoint.first ][ startpoint.second ] != 1 ) {

                    continue;
                }
                else {
                    startpoint.first  = newx;
                    startpoint.second = newy;
                    break;
                }
            }
        }
        cout << " value: " << grid[ startpoint.first ][ startpoint.second ] << endl;
        if ( grid[ startpoint.first ][ startpoint.second ] == n * n - 1 ) {
            return true;
        }
        else {
            return false;
        }
    }

    // pair< int, int > findstart( vector< vector< int > >& grid )
    // {
    //     int n = grid.size();
    //     for ( int i = 0; i < n; i++ ) {
    //         for ( int j = 0; j < n; j++ ) {
    //             if ( grid[ i ][ j ] == 0 ) {
    //                 return { i, j };
    //             }
    //         }
    //     }
    //     return { 0, 0 };
    // }
};

int main()
{
    // vector< vector< int > > grid = { { 0, 3, 6 }, { 5, 8, 1 }, { 2, 7, 4 } };
    // vector< vector< int > > grid = { { 0, 11, 16, 5, 20 }, { 17, 4, 19, 10, 15 }, { 12, 1, 8, 21, 6 }, { 3, 18, 23, 14, 9 }, { 24, 13, 2, 7, 22 } };
    vector< vector< int > > grid={
    {24,11,22,17,4},
    {21,16,5,12,9},
    {6,23,10,3,18},
    {15,20,1,8,13},
    {0,7,14,19,2}};
    Solution                sol;
    cout << sol.checkValidGrid( grid );
    return 0;
}