class Solution {
  public:
    string longestPalindrome(string s) {
        int len = s.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = 0; i < len; ++i)
            dp[i][i] = 1;
        int mx = 0, ansL, ansR;
        for (int j = 1; j < len; ++j) {
            for (int i = 0; i < j; ++i) {
                if (s[i] == s[j]) {
                    if (i + 1 <= j - 1) {
                        dp[i][j] = dp[i + 1][j - 1];
                    } else
                        dp[i][j] = 1;
                } else
                    dp[i][j] = 0;
                if (dp[i][j] && j - i + 1 > mx) {
                    mx = j - i + 1;
                    ansL = i;
                    ansR = j;
                }
            }
        }
        return s.substr(ansL, ansR - ansL + 1);
    }
};