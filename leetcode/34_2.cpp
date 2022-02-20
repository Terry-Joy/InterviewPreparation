class Solution {
  public:
    vector<int> searchRange(vector<int> &nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= target)
                r = mid;
            else
                l = mid + 1;
        }
        if (r == nums.size() || nums[r] != target)
            return {-1, -1};
        int r2 = r;
        l = 0, r = nums.size();
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] > target)
                r = mid;
            else
                l = mid + 1;
        }
        r--;
        return {r2, r};
    }
};