class Solution {
  public:
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        vector<string> ans;
        vector<char> mp[10];
        for (int i = 15; i <= 18; ++i)
            mp[7].push_back(i + 'a');
        for (int i = 19; i <= 21; ++i)
            mp[8].push_back(i + 'a');
        for (int i = 22; i <= 25; ++i)
            mp[9].push_back(i + 'a');
        function<void(int, string)> dfs = [&](int num, string s) {
            if (num == digits.size()) {
                ans.push_back(s);
                return;
            }
            int c = digits[num] - '0' - 2;
            if (digits[num] >= '2' && digits[num] <= '6')
                for (int i = 3 * c; i <= 3 * c + 2; ++i) {
                    dfs(num + 1, s + (char(i + 'a')));
                }
            else
                for (auto u : mp[digits[num] - '0'])
                    dfs(num + 1, s + u);
        };
        dfs(0, "");
        return ans;
    }
};