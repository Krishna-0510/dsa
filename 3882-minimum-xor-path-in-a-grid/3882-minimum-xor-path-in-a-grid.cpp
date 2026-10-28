#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Find the maximum value in the grid to estimate the upper bound for XOR values
        int max_val = 0;
        for (const auto& row : grid) {
            for (int val : row) {
                max_val = std::max(max_val, val);
            }
        }
        
        // Find the next highest power of 2 for the XOR boundary limit
        int max_xor_limit = 1;
        while (max_xor_limit <= max_val) {
            max_xor_limit <<= 1;
        }
        // Double it to safely account for combinations of XOR additions
        max_xor_limit <<= 1; 
        if (max_xor_limit < 256) max_xor_limit = 256; // Secure a safe minimum size

        // dp[i][j][k] indicates if an XOR sum of 'k' is possible at cell (i, j)
        std::vector<std::vector<std::vector<bool>>> dp(m, std::vector<std::vector<bool>>(n, std::vector<bool>(max_xor_limit, false)));
        
        // Base case: starting at the top-left cell
        dp[0][0][grid[0][0]] = true;
        
        // Iterate through each cell in the grid
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < max_xor_limit; ++k) {
                    if (!dp[i][j][k]) continue;
                    
                    // Move Down
                    if (i + 1 < m) {
                        dp[i + 1][j][k ^ grid[i + 1][j]] = true;
                    }
                    
                    // Move Right
                    if (j + 1 < n) {
                        dp[i][j + 1][k ^ grid[i][j + 1]] = true;
                    }
                }
            }
        }
        
        // Find the smallest XOR value that is marked true at the bottom-right cell
        for (int k = 0; k < max_xor_limit; ++k) {
            if (dp[m - 1][n - 1][k]) {
                return k;
            }
        }
        
        return 0;
    }
};
