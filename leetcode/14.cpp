class Solution {
  public:
    string longestCommonPrefix(vector<string> &strs) {
        int len = 0, cnt = 0, n = strs.size();
        for (int i = 0; i < strs.size(); ++i) {
            len += strs[i].size();
        }
        vector<vector<int>> ch(len + 5, vector<int>(26, 0));
        vector<int> sum(len + 5, 0);
        auto insert = [&](const string &s) {
            int p = 0;
            for (int i = 0; i < s.size(); ++i) {
                int c = s[i] - 'a';
                if (!ch[p][c])
                    ch[p][c] = ++cnt;
                p = ch[p][c];
                sum[p]++;
            }
        };
        string ans;
        for (auto u : strs)
            insert(u);
        function<void(int, int)> dfs = [&](int x, int fa) {
            int ps = -1;
            for (int i = 0; i < 26; ++i) {
                if (ch[x][i] && sum[ch[x][i]] == n) {
                    ps = i;
                    ans += ps + 'a';
                    dfs(ch[x][ps], x);
                }
            }
        };
        dfs(0, -1);
        return ans;
    }
};