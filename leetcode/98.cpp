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
//中序递归遍历 O(n) O(n)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> ans;
        bool flag = true;
        function<void(TreeNode*)> dfs = [&](TreeNode *x) {
            if (!x)return;
            dfs(x->left);
            if (ans.size() >= 1 && x->val <= ans.back()) {
                flag = false;
            } 
            ans.emplace_back(x->val);
            dfs(x->right);
        };
        dfs(root);
        return flag;
    }
};

//中序迭代遍历 
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> ans;
        vector<TreeNode*> st;
        while (st.size() >= 1 || root) {
            if (root) {
                st.emplace_back(root);
                root = root->left;
            } else {
                auto it = st.back();
                st.pop_back();
                ans.emplace_back(it->val);
                root = it->right;
            }
        }        
        for (int i = 1; i < ans.size(); ++i) {
            if (ans[i] <= ans[i - 1]) {
                return false;
            }
        }
        return true;
    }
};