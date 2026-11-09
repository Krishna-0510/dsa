class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1 ;
        for(int i = 0 ; i < nums.size() ; i++)
        {
            if(low < 2 || nums[i] != nums[low - 2] )
            {
                nums[low] = nums[i];
                low++;
            }
            
        }
        return low;
    }
};