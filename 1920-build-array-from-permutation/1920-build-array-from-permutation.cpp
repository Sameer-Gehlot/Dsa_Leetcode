class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        vector <int> Ans;

        for(int i = 0; i < nums.size(); i++){
            int temp = nums[nums[i]];
            Ans.push_back(temp);
        }

        return Ans;
    }
};