class Solution {
  public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        dp[0][0] = 1;
        auto match = [&](int i, int j) {
            if (!i)
                return 0;
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
                return 1;
            return 0;
        };
        for (int i = 0; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2]; // i==0的时候处理掉了<=2的a*情况
                    if (match(i, j - 1))
                        dp[i][j] |= dp[i - 1][j];
                } else {
                    if (match(i, j))
                        dp[i][j] |= dp[i - 1][j - 1];
                }
            }
        }
        return dp[n][m];
    }
};