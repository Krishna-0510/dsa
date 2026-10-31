#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;

       
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        
        vector<vector<int>> nxt_right(m, vector<int>(n, -1));
        vector<vector<int>> nxt_down(m, vector<int>(n, -1));

        for (int r = m - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (grid[r][c] == 0) {
                    int pos = r * n + c;
                    nxt_right[r][c] = pos;
                    nxt_down[r][c] = pos;
                } else {
                   
                    if (r + 1 < m) {
                        nxt_right[r][c] = nxt_down[r + 1][c];
                    }
                   
                    if (c + 1 < n) {
                        nxt_down[r][c] = nxt_right[r][c + 1];
                    }
                }
            }
        }

    
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
     
        if (grid[m - 1][n - 1] == 0) {
            dp[m - 1][n - 1] = 1;
        }

        for (int r = m - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (grid[r][c] == 1 || (r == m - 1 && c == n - 1)) {
                    continue;
                }

                long long total_paths = 0;

                
                if (c + 1 < n) {
                    int dest = nxt_right[r][c + 1];
                    if (dest != -1) {
                        total_paths += dp[dest / n][dest % n];
                    }
                }

               
                if (r + 1 < m) {
                    int dest = nxt_down[r + 1][c];
                    if (dest != -1) {
                        total_paths += dp[dest / n][dest % n];
                    }
                }

                dp[r][c] = total_paths % MOD;
            }
        }

        return dp[0][0];
    }
};
