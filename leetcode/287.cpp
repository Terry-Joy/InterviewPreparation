//二分 O(nlogn）O(1) 不修改原地数组
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int l = 1, n = nums.size(), r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (nums[i] <= mid) {
                    cnt++;
                }
            if (cnt > mid) {
                r = mid;
            } else 
                l = mid + 1;
        }
        return r;
    }
};