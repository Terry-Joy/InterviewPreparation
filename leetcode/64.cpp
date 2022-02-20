//O(n) O(m)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid[0].size(), n = grid.size();
        vector<int> dp(m, 1e9);
        dp[0] = grid[0][0];
        for (int i = 1; i < m; ++i)
            dp[i] = dp[i - 1] + grid[0][i];
        for (int i = 1; i < n; ++i) {
            dp[0] = dp[0] + grid[i][0];
            for (int j = 1; j < m; ++j) {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1];
    }
}; 