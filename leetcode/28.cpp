class Solution {
  public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (!m)
            return 0;
        vector<int> nxt(m, 0), f(n, 0);
        nxt[0] = -1;
        for (int i = 1, j = -1; i < m; ++i) {
            while (j != -1 && needle[i] != needle[j + 1])
                j = nxt[j];
            if (needle[i] == needle[j + 1])
                j++;
            nxt[i] = j;
        }
        for (int i = 0, j = -1; i < n; ++i) {
            while (j != -1 && (j == m - 1 || haystack[i] != needle[j + 1]))
                j = nxt[j];
            if (haystack[i] == needle[j + 1])
                j++;
            f[i] = j;
        }
        for (int i = 0; i < n; ++i) {
            if (f[i] == m - 1) {
                return i - m + 1;
            }
        }
        return -1;
    }
};