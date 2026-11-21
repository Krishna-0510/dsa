class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> last_seen(26, -1);

        auto dfs = [&](auto& self, int u) -> void {
            int c = s[u] - 'a';
            int prev_ancestor = last_seen[c];
            
           
            int actual_parent = (prev_ancestor != -1) ? prev_ancestor : parent[u];
            last_seen[c] = u;

            for (int v : adj[u]) {
                self(self, v);
            }
            last_seen[c] = prev_ancestor;

            
            if (u != 0) {
                ans[actual_parent] += ans[u];
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};
