//贪心 O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int r = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (r >= i)
                r = max(r, i + nums[i]);
            else 
                return false;
            if (r >= nums.size() - 1)
                return true;
        }
        return false;
    }
};