//排序双指针 O(nlogn) O(1)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        if (!intervals.size())
            return ans;
        sort(intervals.begin(), intervals.end(), [&](vector<int> & x, vector<int> &y){
            if (x[0] == y[0])
                return x[1] < y[1];
            return x[0] < y[0];
        });
        int r = intervals[0][1], now = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] > r) {
                vector<int> tmp = {intervals[now][0], r};
                r = intervals[i][1];
                ans.emplace_back(tmp);
                now = i;
            } else {
                r = max(r, intervals[i][1]);
            }
        }
        vector<int> tmp = {intervals[now][0], max(r, intervals[now][1])};
        ans.emplace_back(tmp);
        return ans;
    }
};