#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector< int > filterRestaurants( vector< vector< int > >& restaurants, int veganFriendly, int maxPrice, int maxDistance )
    {
        vector< int >           ans;
        vector< vector< int > > temp;
        for ( auto& restaurant : restaurants ) {
            if ( veganFriendly == 1 && restaurant[ 2 ] != 1 ) {
                continue;
            }
            if ( restaurant[ 3 ] <= maxPrice && restaurant[ 4 ] <= maxDistance ) {
                temp.push_back( restaurant );
            }
        }
        // 找到错误了（大概
        //判断出了问题
        sort( temp.begin(), temp.end(), [ & ]( vector< int > a, vector< int > b ) {
            // for ( auto tep : temp ) {
            //     cout << tep[ 0 ] << " ";
            // }
            cout << endl;
            //原始版判断
            //( a[ 1 ] >= b[ 1 ] ) ? true : ( a[ 0 ] < b[ 0 ] ); }
            cout << "aid: " << a[ 0 ] << " bid: " << b[ 0 ] << endl;
            cout << "a: " << a[ 1 ] << " b: " << b[ 1 ] << endl;
            // cout << "ans:" << ( a[ 1 ] >= b[ 1 ] ) << endl;
            // cout << "( a[ 0 ] < b[ 0 ] ): " << ( a[ 0 ] < b[ 0 ] ) << endl;
            if ( a[ 1 ] > b[ 1 ] ) {
                cout << "1" << endl;
                return true;
            }
            if ( (a[ 1 ] == b[ 1 ])&&(a[ 0 ] > b[ 0 ] )) {
                cout << "2" << endl;
                return true;
            }

            cout << "3" << endl;
            return false;
        } );

        for ( auto tem : temp ) {

            ans.push_back( tem[ 0 ] );
        }
        return ans;
    }
};

int main()
{
    // vector< vector< int > > restaurants{ { 1, 4, 1, 40, 10 }, { 2, 8, 0, 50, 5 }, { 3, 8, 1, 30, 4 }, { 4, 10, 0, 10, 3 }, { 5, 1, 1, 15, 1 } };
    vector< vector< int > > restaurants{ { 49707, 71779, 1, 90061, 70036 }, { 63505, 69799, 0, 8562, 95089 }, { 5296, 11100, 0, 22243, 21831 } };
    Solution sol;
    // auto     ans = sol.filterRestaurants( restaurants, 0, 50, 10 );
    auto                    ans = sol.filterRestaurants( restaurants, 0, 35129, 99499);
    for ( auto i : ans ) {
        cout << i << " ";
    }

    return 0;
}