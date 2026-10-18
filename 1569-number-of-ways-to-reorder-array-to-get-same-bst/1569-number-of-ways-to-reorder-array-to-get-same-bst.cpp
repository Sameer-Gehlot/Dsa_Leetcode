
class Solution {
private:
    static constexpr long long MOD = 1000000007LL;
    vector<vector<long long>> comb;

    long long countWays(vector<int>& nums) {
        int n = nums.size();

        // Zero or one node has exactly one possible ordering.
        if (n <= 2) {
            return 1;
        }

        int root = nums[0];

        vector<int> left;
        vector<int> right;

        // Partition according to BST rules.
        for (int i = 1; i < n; i++) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        long long leftWays = countWays(left);
        long long rightWays = countWays(right);

        // Choose positions occupied by left-subtree elements.
        long long interleavings =
            comb[n - 1][left.size()];

        long long ways = interleavings * leftWays % MOD;
        ways = ways * rightWays % MOD;

        return ways;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // Precompute combinations using Pascal's triangle.
        comb.assign(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            comb[i][0] = 1;
            comb[i][i] = 1;

            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] +
                     comb[i - 1][j]) % MOD;
            }
        }

        // Includes the original ordering.
        long long totalWays = countWays(nums);

        // Exclude the original array.
        return (totalWays - 1 + MOD) % MOD;
    }
};
