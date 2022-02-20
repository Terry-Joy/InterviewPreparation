class Solution {
  public:
    vector<int> searchRange(vector<int> &nums, int target) {
        auto it = lower_bound(nums.begin(), nums.end(), target);
        if (it == nums.end())
            return {-1, -1};
        int pos = it - nums.begin();
        if (nums[pos] != target)
            return {-1, -1};
        int it2 = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
        it2--;
        return {pos, it2};
    }
};