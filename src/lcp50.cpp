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
#include <vector>

using namespace std;

class Solution {
public:
    int giveGem( vector< int >& gem, vector< vector< int > >& operations )
    {
        for ( int i = 0; i < operations.size(); i++ ) {
            int a=operations[ i ][ 0 ],b=operations[ i ][ 1 ];
            gem[ b ] += gem[ a ] / 2;
            gem[ a ] -= gem[ a ]/2;

            for ( int j = 0; j < gem.size(); j++ ) {
                cout << gem[ j ] << " ";
            }
            cout << endl;
        }
        int maxgem=-1000;
        int mingem=1000;
        // sort( gem.begin(), gem.end(), []( int a, int b ) { return a > b; } );
        for(int i=0;i<gem.size();i++){
            if(maxgem<gem[i]) maxgem=gem[i];
            if(mingem>gem[i]) mingem=gem[i];
        }
        return maxgem-mingem;
    }
};

int main()
{
    vector< int >           gem{ 100,0,50,100};
    vector< vector< int > > operations{ { 0, 2 }, { 0, 1 }, { 3, 0 }, { 3, 0 } };
    Solution                sol;
    cout << sol.giveGem( gem, operations );

    return 0;
}