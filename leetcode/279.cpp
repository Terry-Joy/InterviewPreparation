//dp O(nsqrt(n)) O(n)
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int j = 1;
            while (j * j <= i) {
                if (dp[i])
                    dp[i] = min(dp[i], dp[i - j * j] + 1);
                else
                    dp[i] = dp[i - j * j] + 1;
                ++j;
            }
        }
        return dp[n];
    }
};


//O(sqrt(n)) O(1)
class Solution {
public:
    int numSquares(int n) {
        auto isSqr = [&](int x) {
            int sqr = sqrt(x);
            return sqr * sqr == x;
        };
        auto isFour = [&](int x) {
            while (x % 4 == 0)
                x /= 4;
            return x % 8 == 7;
        };
        if (isFour(n))
            return 4;
        if (isSqr(n))
            return 1;
        else {
            for (int i = 1; i * i < n; ++i) {
                if (isSqr(n - i * i))
                    return 2;
            }
        }
        return 3;
    }
};