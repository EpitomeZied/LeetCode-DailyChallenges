/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    unordered_map<TreeNode*, int> memo;

    int height(TreeNode* node) {
        if (!node)
            return 0;

        auto it = memo.find(node);
        if (it != memo.end())
            return it->second;

        int h = 1 + max(height(node->left), height(node->right));
        memo[node] = h;
        return h;
    }

    bool dfs(TreeNode* node) {
        if (!node)
            return true;

        int lh = height(node->left);
        int rh = height(node->right);

        if (abs(lh - rh) > 1)
            return false;

        return dfs(node->left) && dfs(node->right);
    }

    bool isBalanced(TreeNode* root) {
        memo.clear();
        return dfs(root);
    }
};
