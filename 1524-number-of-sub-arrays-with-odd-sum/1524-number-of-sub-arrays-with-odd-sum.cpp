class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        long long total_odd_subarrays = 0;
        int current_sum = 0;
        
       
        int even_count = 1;
        int odd_count = 0;
        
        for (int num : arr) {
            current_sum += num;
            
            if (current_sum % 2 != 0) {
               
                total_odd_subarrays = (total_odd_subarrays + even_count) % MOD;
                odd_count++;
            } else {
                
                total_odd_subarrays = (total_odd_subarrays + odd_count) % MOD;
                even_count++;
            }
        }
        
        return total_odd_subarrays;
    }
};
