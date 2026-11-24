
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            int prod = 1, g = 0, l = 1;

            for (int j = i; j < n; j++) {
                prod *= nums[j];
                g = gcd(g, nums[j]);
                l = lcm(l, nums[j]);

                if (prod > 25200)
                    break;

                if (prod == g * l)
                    ans = max(ans, j - i + 1);
            }
        }

        return ans;
    }
};
