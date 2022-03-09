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
//递归O(n) O(n)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        function<void(TreeNode*)> dfs = [&](TreeNode* x) {
            if (!x)
                return;
            dfs(x->left);
            ans.emplace_back(x->val);
            dfs(x->right);
        };
        dfs(root);
        return ans;
    }
};

//迭代 O(n) O(n)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root)
            return ans;
        stack<TreeNode*> tmp;
        while (!tmp.empty() || root) {
            if (root) {
                tmp.push(root);
                root = root->left;
            } else {
                auto it = tmp.top();
                tmp.pop();
                ans.emplace_back(it->val);
                root = it->right;
            }
        }
        return ans;
    }
};