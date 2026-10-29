#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
   
    class BIT {
        int size;
        vector<int> tree;
    public:
        BIT(int n) : size(n), tree(n + 2, 0) {}
        
        void add(int i, int val) {
            for (++i; i <= size + 1; i += i & -i) {
                tree[i] ^= val;
            }
        }
        
        int query(int i) {
            int sum = 0;
            for (++i; i > 0; i -= i & -i) {
                sum ^= tree[i];
            }
            return sum;
        }
    };

    vector<vector<int>> adj;
    vector<int> inTime, outTime;
    vector<int> depth;
    vector<vector<int>> up; 
    int timer = 0;
    int LOG;

    void dfs(int u, int p, int d) {
        inTime[u] = timer++;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
        outTime[u] = timer - 1;
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        adj.assign(n, vector<int>());
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        if (LOG == 0) LOG = 1;

        inTime.resize(n);
        outTime.resize(n);
        depth.resize(n);
        up.assign(n, vector<int>(LOG, 0));
        timer = 0;

        dfs(0, 0, 0);

        BIT bit(n);
       
        for (int i = 0; i < n; ++i) {
            int mask = 1 << (s[i] - 'a');
            bit.add(inTime[i], mask);
            bit.add(outTime[i] + 1, mask);
        }

        vector<bool> ans;
        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                if (s[u] == c) continue;
                
                int old_mask = 1 << (s[u] - 'a');
                int new_mask = 1 << (c - 'a');
                int diff = old_mask ^ new_mask;
                
                
                bit.add(inTime[u], diff);
                bit.add(outTime[u] + 1, diff);
                s[u] = c;
            } else {
                int u, v;
                ss >> u >> v;
                int lca = get_lca(u, v);
                
               
                int mask_u = bit.query(inTime[u]);
                int mask_v = bit.query(inTime[v]);
                int lca_char_mask = 1 << (s[lca] - 'a');
                
                int final_path_mask = mask_u ^ mask_v ^ lca_char_mask;
                
                
                ans.push_back((final_path_mask & (final_path_mask - 1)) == 0);
            }
        }
        return ans;
    }
};
