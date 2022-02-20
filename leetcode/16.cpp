class Solution {
  public:
    int threeSumClosest(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int ans = nums[0] + nums[1] + nums[2], n = nums.size();
        int mx = abs(ans - target);
        for (int i = 0; i < n; ++i) {
            int l = i + 1, r = n - 1;
            while (l < r) {
                auto f = [&](int i, int j, int k) {
                    return abs(nums[i] + nums[j] + nums[k] - target);
                };
                auto sum = [&](int i, int j, int k) {
                    return nums[i] + nums[j] + nums[k];
                };
                if (f(i, l, r) < mx) {
                    mx = f(i, l, r);
                    ans = sum(i, l, r);
                }
                int s = sum(i, l, r);
                if (s < target)
                    l++;
                else if (s > target)
                    r--;
                else
                    return target;
            }
        }
        return ans;
    }
};