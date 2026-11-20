#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> dp;
        int max_len = 0;
        
        for (int x : nums) {
            
            dp[x + 1] = dp[x] + 1;
            dp[x] = dp[x - 1] + 1;
            
            
            max_len = max({max_len, dp[x], dp[x + 1]});
        }
        
        return max_len;
    }
};
