//双指针 O(n^2) O(1)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() <= 2) 
            return ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; ++i) {
            if (nums[i] > 0 || (i && nums[i] == nums[i - 1]))
                continue;
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum > 0) {
                    int tmp = nums[k];
                    while (nums[k] == tmp && j < k) {
                        k--;
                    }
                } else if (sum < 0) {
                    int tmp = nums[j];
                    while (nums[j] == tmp && j < k) {
                        j++;
                    }
                } else {
                    vector<int> tmp = {nums[i], nums[j], nums[k]};
                    ans.emplace_back(tmp);
                    int tmp1 = nums[j], tmp2 = nums[k];
                    while (tmp1 == nums[j] && j < k)
                        j++;
                    while (tmp2 == nums[k] && j < k)
                        k--;                        
                }
            }
        }
        return ans;
    }
};