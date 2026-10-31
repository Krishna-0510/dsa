class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        // vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        
        int minDiff = INT_MAX;
        int ans = 0;
        int sum = 0;
        for(int i = 0 ; i < nums.size() - 2; i++)
        {       
            int left = i + 1;
            int right = nums.size() - 1;
            
            while(left < right)
            {
                sum =  nums[i] + nums[left] + nums[right];
                int diff = abs(target - sum);
                if(diff < minDiff)
                {
                    minDiff = diff;
                    ans = sum;
                }
                if(sum == target)
                {
                    
                    return sum;
                }
                else if(sum < target)
                {
                    
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }   
        return ans;
    }
};