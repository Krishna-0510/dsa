class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int less_than_target = 0;
        int count_target = 0;
        
        for (int num : nums) {
            if (num < target) {
                less_than_target++;
            } else if (num == target) {
                count_target++;
            }
        }
        
        vector<int> result;
        // The target values will occupy indices starting from 'less_than_target'
        for (int i = 0; i < count_target; i++) {
            result.push_back(less_than_target + i);
        }
        
        return result;
    }
};
