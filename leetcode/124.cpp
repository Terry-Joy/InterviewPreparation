//dfs O(n) O(n)
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
    int maxPathSum(TreeNode* root) {
        int ans = -1e9;
        function<int(TreeNode*)> dfs = [&](TreeNode *root) {
            if (!root)
                return 0;
            int left = max(dfs(root->left), 0);
            int right = max(dfs(root->right), 0);
            ans = max(ans, left + right + root->val);
            return max(left, right) + root->val;
        };
        dfs(root);
        return ans;
    }
};