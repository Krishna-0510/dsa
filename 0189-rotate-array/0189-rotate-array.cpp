class Solution {
public:
    void reverse(vector<int>& nums, int left ,int right)
    {
        // int left = 0;
        // int right = nums.size() - 1;
        while(left < right)
        {
            int temp = nums[left];
            nums[left]  = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;

        reverse(nums , 0 ,n - 1);
        reverse(nums, 0 , k - 1);
        reverse(nums, k , n - 1);
    }
};