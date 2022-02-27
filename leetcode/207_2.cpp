//topsort O(n) O(n)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> G(numCourses);
        vector<int> deg(numCourses, 0);
        queue<int> q;
        bool flag = true;
        for (auto u : prerequisites) {
            G[u[1]].emplace_back(u[0]);
            deg[u[0]]++;
        }
        for (int i = 0; i < numCourses; ++i) {
            if (!deg[i]) {
                q.push(i); 
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto &v : G[x]) {
                if (--deg[v] == 0) {
                    q.push(v);
                }
            }
        }
        for (int i = 0; i < numCourses; ++i) {
            if (deg[i])
                flag = false;
        }
        return flag;
    }
};