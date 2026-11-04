#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        

        vector<long long> window_cost(n - x + 1, 0);
        
        priority_queue<int> left_max; 
        priority_queue<int, vector<int>, greater<int>> right_min; 
        
        unordered_map<int, int> lazy_left, lazy_right;
        int left_size = 0, right_size = 0;
        long long left_sum = 0, right_sum = 0;

        auto balance = [&]() {
            if (left_size > right_size + 1) {
                while (!left_max.empty() && lazy_left[left_max.top()] > 0) {
                    lazy_left[left_max.top()]--;
                    left_max.pop();
                }
                int val = left_max.top(); left_max.pop();
                left_sum -= val; left_size--;
                right_min.push(val);
                right_sum += val; right_size++;
            } else if (left_size < right_size) {
                while (!right_min.empty() && lazy_right[right_min.top()] > 0) {
                    lazy_right[right_min.top()]--;
                    right_min.pop();
                }
                int val = right_min.top(); right_min.pop();
                right_sum -= val; right_size--;
                left_max.push(val);
                left_sum += val; left_size++;
            }
        };

        auto add_num = [&](int val) {
            if (left_max.empty() || val <= left_max.top()) {
                left_max.push(val);
                left_sum += val;
                left_size++;
            } else {
                right_min.push(val);
                right_sum += val;
                right_size++;
            }
            balance();
        };

        auto remove_num = [&](int val) {
            if (!left_max.empty() && val <= left_max.top()) {
                lazy_left[val]++;
                left_sum -= val;
                left_size--;
            } else {
                lazy_right[val]++;
                right_sum -= val;
                right_size--;
            }
            balance();
        };

      
        for (int i = 0; i < x; ++i) {
            add_num(nums[i]);
        }
        
        auto get_median = [&]() {
            while (!left_max.empty() && lazy_left[left_max.top()] > 0) {
                lazy_left[left_max.top()]--;
                left_max.pop();
            }
            return left_max.top();
        };

        long long med = get_median();
        window_cost[0] = (med * left_size - left_sum) + (right_sum - med * right_size);

       
        for (int i = x; i < n; ++i) {
            remove_num(nums[i - x]);
            add_num(nums[i]);
            med = get_median();
            window_cost[i - x + 1] = (med * left_size - left_sum) + (right_sum - med * right_size);
        }

      
        int m = window_cost.size();
        const long long INF = 1e16;
        vector<vector<long long>> dp(m + 1, vector<long long>(k + 1, INF));
        
       
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 0;
        }

        for (int j = 1; j <= k; ++j) {
            for (int i = m - 1; i >= 0; --i) {
                
                dp[i][j] = dp[i + 1][j];
                
               
                if (i + x <= m) {
                    dp[i][j] = min(dp[i][j], window_cost[i] + dp[i + x][j - 1]);
                } else if (j == 1) { 
                    dp[i][j] = min(dp[i][j], window_cost[i]);
                }
            }
        }

        return dp[0][k];
    }
};
