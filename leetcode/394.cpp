class Solution {
public:
    string decodeString(string s) {
        int now = 0;
        string ans = "";
        stack<pair<int, string>> st;
        for (auto u : s) {
            if (isdigit(u)) {
                now = now * 10 + (u - '0');
            } else if (u == '['){//左括号的时候把...[]中的...和当前重复数字压栈
                st.push({now, ans});
                ans = "";
                now = 0;
            } else if (u == ']') {
                auto [a, b] = st.top();
                st.pop();
                string tmp = "";
                for (int i = 0; i < a; ++i) //..5[..] 内部括号为tmp 
                    tmp += ans;
                ans = b + tmp;
            } else 
                ans += u;
        }
        return ans;
    }
};