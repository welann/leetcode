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
// 王后可以行走的路线：直线和对角线
// 首先可以知道最多有 8 个王后可以攻击到国王，且只有一个国王
// 那么从国王的位置进行遍历：水平方向和竖直方向以及两个对角线方向。
// 直至到达边界或者找到一个王后的存在
class Solution {
public:
    vector< vector< int > > queensAttacktheKing( vector< vector< int > >& queens, vector< int >& king )
    {
        int                     kingx = king[ 0 ];
        int                     kingy = king[ 1 ];
        vector< vector< int > > checkerboard( 8, vector< int >( 8, 0 ) );
        vector< vector< int > > ans;
        for ( int i = 0; i < queens.size(); i++ ) {
            checkerboard[ queens[ i ][ 0 ] ][ queens[ i ][ 1 ] ] = 1;
        }

        // 水平方向
        for ( int i = kingy; i >= 0; i-- ) {
            if ( checkerboard[ kingx ][ i ] == 1 ) {
                ans.push_back( { kingx, i } );
                break;
            }
        }
        for ( int i = kingy; i < 8; i++ ) {
            if ( checkerboard[ kingx ][ i ] == 1 ) {
                ans.push_back( { kingx, i } );
                break;
            }
        }
        // 竖直方向
        for ( int i = kingx; i >= 0; i-- ) {
            if ( checkerboard[ i ][ kingy ] == 1 ) {
                ans.push_back( { i, kingy } );
                break;
            }
        }
        for ( int i = kingx; i < 8; i++ ) {
            if ( checkerboard[ i ][ kingy ] == 1 ) {
                ans.push_back( { i, kingy } );
                break;
            }
        }
        // 对角线：从上到下
        for ( int i = 0; i < 8 && kingx - i >= 0 && kingy - i >= 0; i++ ) {
            if ( checkerboard[ kingx - i ][ kingy - i ] == 1 ) {
                ans.push_back( { kingx - i, kingy - i } );
                break;
            }
        }
        for ( int i = 0; i < 8 && kingx + i < 8 && kingy + i < 8; i++ ) {
            if ( checkerboard[ kingx + i ][ kingy + i ] == 1 ) {
                ans.push_back( { kingx + i, kingy + i } );
                break;
            }
        }

        // 对角线：从下到上
        for ( int i = 0; i < 8 && kingx - i >= 0 && kingy + i < 8; i++ ) {
            if ( checkerboard[ kingx - i ][ kingy + i ] == 1 ) {
                ans.push_back( { kingx - i, kingy + i } );
                break;
            }
        }
        for ( int i = 0; i < 8 && kingx + i < 8 && kingy - i >= 0; i++ ) {
            if ( checkerboard[ kingx + i ][ kingy - i ] == 1 ) {
                ans.push_back( { kingx + i, kingy - i } );
                break;
            }
        }

        return ans;
    }
};

int main()
{
    // vector< vector< int > > queens={{0,1},{1,0},{4,0},{0,4},{3,3},{2,4}};
    // vector< vector< int > > queens = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 4 }, { 3, 5 }, { 4, 4 }, { 4, 5 } };
    vector< vector< int > > queens={{4,7},{1,3},{6,6},{3,0},{0,2},{0,7},{6,2},{3,7},{5,1},{2,5},{0,3},{7,2},{4,0},{1,2},{3,3},{5,5},{4,4},{6,3},{1,5},{5,0},{0,4},{6,4},{5,4},{3,2},{0,0},{4,5},{0,5},{2,3},{1,0},{6,5},{5,3},{0,1},{7,0},{4,6},{5,7},{7,4},{2,0},{4,3},{3,4}};

    vector< int >           king   = { 2, 4 };
    Solution sol;
    auto     tmp = sol.queensAttacktheKing( queens, king );
    for ( auto i : tmp ) {
        cout << i[ 0 ] << " " << i[ 1 ] << endl;
    }

    return 0;
}