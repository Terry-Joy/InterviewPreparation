//dp O(n) O(n)
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = 2;
                    if(i - 2 >= 0)
                        dp[i] += dp[i - 2];
                } else {
                    if (i - 1 - dp[i - 1] >= 0 && s[i - 1 - dp[i - 1]] == '(') {
                        dp[i] = dp[i - 1] + 2;
                        if (i - 2 - dp[i - 1] >= 0)
                            dp[i] += dp[i - 2 - dp[i - 1]];
                    }
                }
            } else continue;
        }
        int ans = 0;
        for (auto u: dp)
            ans = max(ans, u);
        return ans;
    }
};