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
class Solution {
public:
    int rob(TreeNode* root) {
        unordered_map<TreeNode*, int> dp[2];
        dp[0][nullptr] = dp[1][nullptr] = 0;
        function<void(TreeNode*)> dfs = [&](TreeNode *x) {
            if (!x)
                return;
            dfs(x->left);
            dfs(x->right);
            dp[0][x] = max(dp[0][x->left], dp[1][x->left]) + max(dp[0][x->right], dp[1][x->right]);
            dp[1][x] = dp[0][x->left] + dp[0][x->right] + x->val;
        };
        dfs(root);
        return max(dp[0][root], dp[1][root]);
    }
};