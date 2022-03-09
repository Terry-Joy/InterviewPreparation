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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root)
            return ans;
        vector<int> tmp;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                auto it = q.front();
                q.pop();
                tmp.emplace_back(it->val);
                if (it->left) {
                    q.push(it->left);
                }
                if (it->right) {
                    q.push(it->right);
                }
            }
            ans.emplace_back(tmp);
            tmp.clear();
        }
        return ans;
    }
};