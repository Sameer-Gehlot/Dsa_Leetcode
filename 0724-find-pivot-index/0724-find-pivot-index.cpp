class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int leftsum = 0;
        int totalsum = accumulate(nums.begin(),nums.end(),0);

        for(int i = 0; i < nums.size(); i++){
            if( leftsum == totalsum-leftsum-nums[i] ){
                return i;
            }
            leftsum += nums[i];
        }

       
            return -1;
        }
};