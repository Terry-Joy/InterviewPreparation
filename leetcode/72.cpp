//O(nm) O(nm)
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= n; ++i)
            dp[i][0] = i;
        for (int i = 0; i <= m; ++i)
            dp[0][i] = i;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1])  
                    dp[i][j] = dp[i - 1][j - 1];
                else 
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
        return dp[n][m];
    }
};

//O(nm) O(m)
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> dp(m + 1, 0);
        for (int i = 0; i <= m; ++i)
            dp[i] = i; //dp[0][i]
        for (int i = 1; i <= n; ++i) {
            int pre = dp[0];//dp[i - 1][j - 1]
            dp[0] = i; //dp[i][0]
            for (int j = 1; j <= m; ++j) {
                int now = dp[j];//dp[i - 1][j]
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = pre;
                } else {
                    dp[j] = min(pre, min(dp[j - 1], now)) + 1;
                }
                pre = now;
            }
        }
        return dp[m];
    }
};