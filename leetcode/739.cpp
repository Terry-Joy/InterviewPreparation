//单调栈 O(n) O(n)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> st;
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!st.empty() && temperatures[i] > temperatures[st.back()]) {
                temperatures[st.back()] = i - st.back();
                st.pop_back();
            }
            st.emplace_back(i);
        }
        while (!st.empty()) {
            temperatures[st.back()] = 0;
            st.pop_back();
        }
        return temperatures;
    }
};