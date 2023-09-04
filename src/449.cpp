#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include<stack>

using namespace std;

// 二叉搜索树，左节点小于根节点，右节点大于根节点
// 序列化：广度优先搜索，遍历所有节点
// 根据数字大小重新构建二叉树

struct TreeNode {
    int       val;
    TreeNode* left;
    TreeNode* right;
    TreeNode( int x ) : val( x ), left( NULL ), right( NULL ) {}
};

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize( TreeNode* root )
    {
        if ( root == nullptr )
            return "";

        string             ans = "";
        queue< TreeNode* > que;
        que.push( root );
        while ( !que.empty() ) {
            ans += to_string( que.front()->val );
            ans += ',';
            if ( que.front()->left != nullptr ) {
                que.push( que.front()->left );
            }
            if ( que.front()->right != nullptr ) {
                que.push( que.front()->right );
            }
            que.pop();
        }
        return ans;
    }
    vector< string > split( const string& str, char dec )
    {
        int              pos   = 0;
        int              start = 0;
        vector< string > res;
        while ( pos < str.size() ) {
            while ( pos < str.size() && str[ pos ] == dec ) {
                pos++;
            }
            start = pos;
            while ( pos < str.size() && str[ pos ] != dec ) {
                pos++;
            }
            if ( start < str.size() ) {
                res.emplace_back( str.substr( start, pos - start ) );
            }
        }
        return res;
    }

    TreeNode* deserialize( string data )
    {
        if ( data.size() == 0 ) {
            return nullptr;
        }
        vector< string > arr = split( data, ',' );
        stack< int >     st;
        for ( auto& str : arr ) {
            st.emplace( stoi( str ) );
        }
        return construct( INT_MIN, INT_MAX, st );
    }

    void postOrder( TreeNode* root, vector< int >& arr )
    {
        if ( root == nullptr ) {
            return;
        }
        postOrder( root->left, arr );
        postOrder( root->right, arr );
        arr.emplace_back( root->val );
    }

    TreeNode* construct( int lower, int upper, stack< int >& st )
    {
        if ( st.size() == 0 || st.top() < lower || st.top() > upper ) {
            return nullptr;
        }
        int val = st.top();
        st.pop();
        TreeNode* root = new TreeNode( val );
        root->right    = construct( val, upper, st );
        root->left     = construct( lower, val, st );
        return root;
    }
};

int main()
{
    TreeNode* root = new TreeNode( 21 );
    TreeNode* a    = new TreeNode( 11 );
    TreeNode* b    = new TreeNode( 31 );
    TreeNode* c    = new TreeNode( 10 );
    TreeNode* d    = new TreeNode( 12 );
    root->left     = a;
    root->right    = b;
    a->left        = c;
    a->right       = d;

    Codec* ser   = new Codec();
    Codec* deser = new Codec();
    string tree  = ser->serialize( root );
    cout << tree << endl;

    TreeNode* ans   = deser->deserialize( tree );
    string    tree2 = ser->serialize( root );
    cout << tree2 << endl;

    return 0;
}
