class Solution {
public:
    int rob(vector<int>& nums) {
        int pre0 = 0, pre1 = nums[0], now0 = 0, now1 = 0, mx = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            now0 = max(pre0, pre1);
            now1 = pre0 + nums[i];
            swap(pre0, now0);
            swap(pre1, now1);
        }
        return max(pre0, pre1);
    }
};