class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
       for(int i = 0; i < nums.size(); i++)
        {
            int need = target - nums[i];

            for(int j = 0; j < nums.size(); j++)
            {
                if(i != j && nums[j] == need)
                {
                    return {i, j};
                }
            }
        }
        // Return an empty vector if no solution is found
        return {};
    }
};