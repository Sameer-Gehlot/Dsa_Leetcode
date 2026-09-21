class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at the
        // previous position whose product % k == r
        vector<long long> dp(k, 0);

        for (int x : nums) {
            vector<long long> newDp(k, 0);

            int val = x % k;

            // Start a new subarray with only x
            newDp[val]++;

            // Extend all previous subarrays by x
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int newRemainder = (r * val) % k;

                    newDp[newRemainder] += dp[r];
                }
            }

            // All subarrays ending here contribute
            // to the final answer
            for (int r = 0; r < k; r++) {
                ans[r] += newDp[r];
            }

            dp = newDp;
        }

        return ans;
    }
};