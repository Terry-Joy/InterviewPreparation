class Solution {
  public:
    vector<string> generateParenthesis(int n) {
        vector<string> tmp, ans;
        function<void(int, string)> dfs = [&](int num, string s) {
            if (num == 2 * n) {
                tmp.emplace_back(s);
                return;
            }
            dfs(num + 1, s + '(');
            dfs(num + 1, s + ')');
        };
        dfs(0, "");
        auto ok = [&](const string &x) {
            vector<char> st;
            bool f = 1;
            for (int i = 0; i < x.size(); ++i) {
                if (st.empty() || x[i] == '(')
                    st.emplace_back(x[i]);
                else {
                    if (st.back() != '(') {
                        f = 0;
                        break;
                    } else
                        st.pop_back();
                }
            }
            if (st.size())
                f = 0;
            return f;
        };
        for (auto u : tmp) {
            if (ok(u)) {
                ans.emplace_back(u);
            }
        }
        return ans;
    }
};