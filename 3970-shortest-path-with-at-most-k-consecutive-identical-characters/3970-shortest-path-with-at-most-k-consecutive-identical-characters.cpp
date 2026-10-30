#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        
        k = min(k, n);

      
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }
        
        int INF = 1e9;
        
        vector<int> dist(n * (k + 1), INF);
        
   
        priority_queue<tuple<int, int, int>, 
                       vector<tuple<int, int, int>>, 
                       greater<tuple<int, int, int>>> pq;
        
      
        dist[0 * (k + 1) + 1] = 0;
        pq.push({0, 0, 1});
        
        while (!pq.empty()) {
            auto [d, u, streak] = pq.top();
            pq.pop();
            
            if (u == n - 1) {
                return d;
            }
            
            if (d > dist[u * (k + 1) + streak]) {
                continue;
            }
            
            char curr_char = labels[u];
            
            for (const auto& neighbor : graph[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                
                
                int next_streak = (labels[v] == curr_char) ? (streak + 1) : 1;
                
                if (next_streak <= k) {
                    int idx = v * (k + 1) + next_streak;
                    if (d + w < dist[idx]) {
                        dist[idx] = d + w;
                        pq.push({d + w, v, next_streak});
                    }
                }
            }
        }
        
        return -1;
    }
};
