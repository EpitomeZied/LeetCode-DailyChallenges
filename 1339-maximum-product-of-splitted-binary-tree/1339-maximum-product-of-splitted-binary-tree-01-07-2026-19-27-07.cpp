/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#define ll long long 
class Solution {
public:
    const int MOD = 1e9 + 7;
    ll totalSum = 0, ans = 0;
    ll dfs(TreeNode* root) {
        if (!root) return 0;
        ll left = dfs(root->left);
        ll right = dfs(root->right);
        ll sub = root->val + left + right;
        ans = max(ans, sub * (totalSum - sub));
        return sub;
    }
    int maxProduct(TreeNode* root) {
        totalSum = dfs(root);   
        dfs(root);
        return ans % MOD;
    }
};
