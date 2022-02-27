//dfs找环 O(n) O(n)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>vis(numCourses, 0);
        bool flag = true;
        vector<vector<int>> G(numCourses);
        function<void(int)> dfs = [&](int x) {
            vis[x] = 1;
            for (auto v: G[x]) {
                if (!vis[v]) {
                    dfs(v);
                    if (!flag)
                        return;
                } else if (vis[v] == 1) {
                    flag = false;
                    return;
                }
            }
            vis[x] = 2;
        };
        for (auto u : prerequisites) {
            G[u[1]].emplace_back(u[0]);
        }
        for (int i = 0; i < numCourses && flag; ++i) {
            if (!vis[i]) {
                dfs(i); 
            }
        }
        return flag;
    }
};