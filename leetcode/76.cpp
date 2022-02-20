class Solution {
public:
    string minWindow(string s, string t) {
        int l = 0, r = 0, sum = 0, n = s.size(), ansL = 0, ansR = 0, ans = 1e9;
        unordered_map<char, int> obj, cnt;
        for (auto u: t)
            obj[u]++, sum++;
        cnt[s[0]]++;
        if (obj.find(s[0]) != obj.end())
            sum--;
        while (l <= r && r < n) {
            while (r < n && sum) {
                r++;
                if (r < n && obj.find(s[r]) != obj.end()) {
                    if (cnt[s[r]] < obj[s[r]])
                        sum--;
                    cnt[s[r]]++;
                }
            }
            while (l <= r && !sum) {
                if (ans > r - l + 1) {
                    ans = r - l + 1;
                    ansL = l;
                    ansR = r;
                }
                if (obj.find(s[l]) != obj.end() && obj[s[l]] <= cnt[s[l]]) {
                    if (obj[s[l]] == cnt[s[l]])
                        sum++;
                    cnt[s[l]]--;
                }
                l++;
            }
        }
        if (ans == 1e9)
            return "";
        else
            return s.substr(ansL, ansR - ansL + 1);
    }
};