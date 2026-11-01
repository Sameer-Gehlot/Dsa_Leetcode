
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mini = *min_element(nums.begin(), nums.end());

        int ans = 0;

        for (int num : nums) {
            ans += num - mini;
        }

        return ans;
    }
};
