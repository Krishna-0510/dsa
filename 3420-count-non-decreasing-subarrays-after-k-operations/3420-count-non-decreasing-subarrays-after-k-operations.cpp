#include <vector>
#include <deque>
#include <utility>

using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long current_cost = 0;
        
   
        deque<pair<int, int>> dq;
        int r = n - 1;

        for (int l = n - 1; l >= 0; --l) {
            int count = 1;
            
           
            while (!dq.empty() && dq.front().first <= nums[l]) {
                auto [val, cnt] = dq.front();
                dq.pop_front();
                current_cost += 1LL * (nums[l] - val) * cnt;
                count += cnt;
            }
            dq.push_front({nums[l], count});

            
            while (current_cost > k) {
                auto& [val, cnt] = dq.back();
                current_cost -= (val - nums[r]);
                cnt--;
                if (cnt == 0) {
                    dq.pop_back();
                }
                r--;
            }

            
            ans += (r - l + 1);
        }

        return ans;
    }
};
