class Solution {
  public:
    bool isValid(string s) {
        vector<char> st;
        bool f = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                st.emplace_back(s[i]);
            else {
                if (s[i] == ')') {
                    if (st.empty() || st.back() != '(') {
                        f = 0;
                        break;
                    } else {
                        st.pop_back();
                    }
                } else if (s[i] == ']') {
                    if (st.empty() || st.back() != '[') {
                        f = 0;
                        break;
                    } else {
                        st.pop_back();
                    }
                } else if (s[i] == '}') {
                    if (st.empty() || st.back() != '{') {
                        f = 0;
                        break;
                    } else {
                        st.pop_back();
                    }
                }
            }
        }
        if (st.size())
            f = 0;
        return f;
    }
};