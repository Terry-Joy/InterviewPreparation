//单调队列 O(n)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> st;
        vector<int> ans;        
        for (int i = 0; i < nums.size(); ++i) {
            while (!st.empty() && nums[i] >= nums[st.back()]) {
                st.pop_back();
            }
            st.push_back(i);
            while (st.size() >= 2 && st.back() - st.front() >= k) {
                st.pop_front();
            }
            if (i >= k - 1) 
                ans.emplace_back(nums[st.front()]);
        }
        return ans;
    }
};