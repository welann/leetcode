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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//思路
//暴力递归所有的节点，DFS
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        queue<TreeNode*> que;
        if(!root) return 0;
        que.push(root);
        int ans=0;
        while(!que.empty()){
            int current=0;

            auto node=que.front();
            // cout<<"current node: "<<node->val<<endl;
            // cout<<"ans: "<<ans<<endl;

            dfs(node,targetSum,ans);
            // ans+=rootSum(node,targetSum);
            // cout<<endl;

            if(node->left!=NULL){
                que.push(node->left);
            }
            if(node->right!=NULL){
                que.push(node->right);
            }            
            que.pop();
        }
        return ans;
    }
    void dfs(TreeNode* node,int target,int& ans){

        if(!node) return ;

        if(node->val==target){
            ans++;
            // return ;
        }

        dfs(node->left, target-node->val, ans);
        dfs(node->right, target-node->val, ans);
    }
    int rootSum(TreeNode* root, long targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        if (root->val == targetSum) {
            ret++;
        } 

        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }

};
int main(){
    //[1,-2,-3,1,3,-2,null,-1]
    TreeNode* root=new TreeNode(1);
    TreeNode* node1=new TreeNode(-2);
    TreeNode* node2=new TreeNode(-3);
    TreeNode* node3=new TreeNode(1);
    TreeNode* node4=new TreeNode(3);
    TreeNode* node5=new TreeNode(-2);
    TreeNode* node6=new TreeNode(-1);
    // TreeNode* node7=new TreeNode(2);
    // TreeNode* node8=new TreeNode(5);
    // TreeNode* node9=new TreeNode(1);

    root->left=node1;
    root->right=node2;
    node1->left=node3;
    node1->right=node4;
    node2->left=node5;

    node3->left=node6;
    // node3->right=node7;
    // node5->left=node8;
    // node5->right=node9;

    Solution sol;
    cout<<"ans: "<<sol.pathSum(root, -1);

    return 0;
}