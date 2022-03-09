class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int mx = -1e9, mn = 1e9, l = 0, r = -1, n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] < mx) {
                r = i;
            } else {
                mx = nums[i];
            }
            if (nums[n - 1 - i] > mn) {
                l = n - 1 - i;
            } else {
                mn = nums[n - 1 - i];
            }
        } 
        return (r == -1) ? 0 : r - l + 1;
    }
};