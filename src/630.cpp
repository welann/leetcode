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

// 思路
// 按照最后期限进行排队。此时越靠前的越需要尽早完成
// 贪心算法，使用优先队列，当新加入的课程需要的时间比队列中最长的时间短的时候，替换掉

class Solution {
public:
    int scheduleCourse( vector< vector< int > >& courses )
    {
        sort( courses.begin(), courses.end(), []( vector< int > a, vector< int > b ) {
            return a[ 1 ] < b[ 1 ];
        } );

        priority_queue< int > pq;       // 最大堆
        int                   day = 0;  // 已消耗时间
        for ( auto& course : courses ) {
            int duration = course[ 0 ], last_day = course[ 1 ];
            if ( day + duration <= last_day ) {  // 没有超过 last_day，直接学习
                day += duration;
                pq.push( duration );
            }
            else if ( !pq.empty() && duration < pq.top() ) {  // 该课程的时间比之前的最长时间要短
                // 反悔，撤销之前 duration 最长的课程，改为学习该课程
                // 节省出来的时间，能在后面上完更多的课程
                day -= pq.top() - duration;
                pq.pop();
                pq.push( duration );
            }
        }
        return pq.size();
    }
};

int main()
{
    vector< vector< int > > courses{ { 100, 200 }, { 200, 1300 }, { 1000, 1250 }, { 2000, 3200 } };
    Solution                sol;
    cout << sol.scheduleCourse( courses );

    return 0;
}