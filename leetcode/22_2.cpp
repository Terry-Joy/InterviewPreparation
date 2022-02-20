//
class Solution {
  public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        function<void(int, int, string)> dfs = [&](int l, int r, string s) {
            if (l == n && r == n) {
                ans.emplace_back(s);
                return;
            }
            if (l == r) // only (
                dfs(l + 1, r, s + '(');
            else if (l > r) {
                if (l != n)
                    dfs(l + 1, r, s + '(');
                dfs(l, r + 1, s + ')');
            }
        };
        dfs(0, 0, "");
        return ans;
    }
};