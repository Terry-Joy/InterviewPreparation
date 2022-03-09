//O(n) O(1)
class Solution {
public:
    int numTrees(int n) {
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            ans = (long long) ans * 2 * (2 * i + 1) / (i + 2);
        }
        return ans;
    }
};