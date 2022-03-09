//bfs O(nm) O(nm)
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool> (m, false));
        auto check = [&](int i, int j) {
            return i >= 0 && i < n && j >= 0 && j < m && !vis[i][j] && grid[i][j] == '1';
        };
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!vis[i][j] && grid[i][j] == '1') {
                    ans++;
                    vis[i][j] = true;
                    queue<pair<int, int> > q;
                    q.push({i, j});
                    while (!q.empty()) {
                        auto [u, v] = q.front();
                        q.pop();
                        if (check(u, v + 1)) {
                            q.push({u, v + 1});
                            vis[u][v + 1] = true;
                        } 
                        if (check(u + 1, v)) {
                            q.push({u + 1, v});
                            vis[u + 1][v] = true;
                        }
                        if (check(u - 1, v)) {
                            q.push({u - 1, v});
                            vis[u - 1][v] = true;
                        } 
                        if (check(u, v - 1)) {
                            q.push({u, v - 1});
                            vis[u][v - 1] = true;
                        }
                    }
                }
            }
        }
        return ans;
    }
};