#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

// 思路：
// 数据结构要记录如下信息：当前是否被锁住、锁住的执行人是谁，子节点有哪些

// class LockingTree {
//     struct info {
//         int  parent    = -100;
//         int  childrenr = -1, childrenl = -1;
//         int  lockuser = -1;
//         bool lockd    = false;
//     };
//     vector< info > infolist;  // 这个数组记录的是每个节点的子节点信息
// public:
//     LockingTree( vector< int >& parent )
//     {
//         infolist.resize( parent.size() );
//         infolist[0].parent=-1;
//         for ( int i = 1; i < parent.size(); i++ ) {
//             if ( infolist[ parent[ i ] ].childrenl == -1 ) {
//                 infolist[ parent[ i ] ].childrenl = i;
//             }
//             else {
//                 infolist[ parent[ i ] ].childrenr = i;
//             }
//             infolist[ i ].parent = parent[ i ];
//         }

//         for(auto num:infolist){
//             cout<<"parent: "<<num.parent<<" children: "<<num.childrenl<<" "<<num.childrenr<<" locked: "<<num.lockd<<" lockuser: "<<num.lockuser<<endl;
//         }
//     }

//     bool lock( int num, int user )
//     {
//         if ( infolist[ num ].lockd == true ) {
//             return false;
//         }
//         else {
//             infolist[ num ].lockd    = true;
//             infolist[ num ].lockuser = user;
//             return true;
//         }
//     }

//     bool unlock( int num, int user )
//     {
//         if ( infolist[ num ].lockd == true && infolist[ num ].lockuser == user ) {
//             infolist[ num ].lockd    = false;
//             infolist[ num ].lockuser = -1;
//             return true;
//         }
//         return false;
//     }

//     bool upgrade( int num, int user )
//     {
//         if ( infolist[ num ].lockd == true ){
//             return false;

//         }
//         // num未被上锁
//         // 子树中至少有一个被上锁
//         queue< int >  que;
//         vector< int > lockednum;

//         if ( infolist[ num ].childrenl != -1 ) {
//             que.push( infolist[ num ].childrenl );
//         }
//         if ( infolist[ num ].childrenr != -1 ) {
//             que.push( infolist[ num ].childrenr );
//         }
//         bool flag = false;

//         while ( !que.empty()  ) {
//             int temp = que.front();
//             if ( infolist[ temp ].lockd ) {
//                 flag = true;
//                 lockednum.push_back( temp );
//             }

//             if ( infolist[ temp ].childrenl != -1 ) {
//                 que.push( infolist[ temp ].childrenl );
//             }
//             if ( infolist[ temp ].childrenr != -1 ) {
//                 que.push( infolist[ temp ].childrenr );
//             }
//             que.pop();
//         }
//         if ( flag ) {
//             infolist[ num ].lockd = true;
//             infolist[ num ].lockuser=user;
//             for ( auto num : lockednum ) {
//                 infolist[ num ].lockd = false;
//             }
//             return true;
//         }
//         return false;
//     }
// };

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */

class LockingTree {
public:
    LockingTree(vector<int>& parent) {
        int n = parent.size();
        this->parent = parent;
        this->lockNodeUser = vector<int>(n, -1);
        this->children = vector<vector<int>>(n);
        for (int i = 0; i < n; i++) {
            int p = parent[i];
            if (p != -1) {
                children[p].emplace_back(i);
            }
        }
    }
    
    bool lock(int num, int user) {
        if (lockNodeUser[num] == -1) {
            lockNodeUser[num] = user;
            return true;
        } 
        return false;
    }
    
    bool unlock(int num, int user) {
        if (lockNodeUser[num] == user) {
            lockNodeUser[num] = -1;
            return true;
        }
        return false;
    }
    
    bool upgrade(int num, int user) {
        bool res = lockNodeUser[num] == -1 \
                   && !hasLockedAncestor(num) \
                   && checkAndUnlockDescendant(num);
        if (res) {
            lockNodeUser[num] = user;
        }
        return res;
    }

    bool hasLockedAncestor(int num) {
        num = parent[num];
        while (num != -1) {
            if (lockNodeUser[num] != -1) {
                return true;
            }
            num = parent[num];
        }
        return false;
    }
        
    bool checkAndUnlockDescendant(int num) {
        bool res = lockNodeUser[num] != -1;
        lockNodeUser[num] = -1;
        for (int child : children[num]) {
            res |= checkAndUnlockDescendant(child);
        }            
        return res;
    }
        
private:
    vector<int> parent;
    vector<int> lockNodeUser;
    vector<vector<int>> children;
};


int main()
{
    vector< int > parent{-1,0,3,1,0};
    LockingTree lockingTree{parent};

    cout<<lockingTree.upgrade( 4,5 )<<endl;     // 返回 true ，因为节点 2 未上锁。
                                  // 节点 2 被用户 2 上锁。
    cout<<lockingTree.upgrade( 3,8 )<<endl;   // 返回 false ，因为用户 3 无法解锁被用户 2 上锁的节点。
    cout<<lockingTree.unlock( 0,7 )<<endl;   // 返回 true ，因为节点 2 之前被用户 2 上锁。
                                  // 节点 2 现在变为未上锁状态。
    cout<<lockingTree.lock( 2,7)<<endl;     // 返回 true ，因为节点 4 未上锁。
                                  // 节点 4 被用户 5 上锁。
    cout<<lockingTree.upgrade( 4,6 )<<endl;  // 返回 true ，因为节点 0 未上锁且至少有一个被上锁的子孙节点（节点 4）。
                                  // 节点 0 被用户 1 上锁，节点 4 变为未上锁。
    // cout<<lockingTree.lock( 0, 1 )<<endl;     // 返回 false ，因为节点 0 已经被上锁了。
}