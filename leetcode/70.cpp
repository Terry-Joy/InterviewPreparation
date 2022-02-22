//O(n) O(1)
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 3)
            return n;
        int fi = 2, se = 3, ans = 0;
        for (int i = 4; i <= n; ++i) {
            ans = fi + se;
            fi = se;
            se = ans;
        }
        return ans;
    }
};