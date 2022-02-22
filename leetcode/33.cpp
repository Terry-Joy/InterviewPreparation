class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] >= nums[l]) {
                if (target >= nums[l] && target <= nums[mid]) {
                    r = mid;
                } else 
                    l = mid + 1;
            } else {
                if (nums[mid + 1] <= target && target <= nums[r]) {
                    l = mid + 1;
                } else 
                    r = mid;
            }
        }
        return (l == r && nums[r] == target) ? r : -1;
    }
};