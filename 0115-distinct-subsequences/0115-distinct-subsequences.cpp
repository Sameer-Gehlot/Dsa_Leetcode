class Solution {
public:
    int numDistinct(string s, string t) {
        int n = t.size();

        vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (char c : s) {
            for (int j = n - 1; j >= 0; j--) {

                if (c == t[j]) {
                    if (dp[j + 1] > INT_MAX - dp[j]) {
                        dp[j + 1] = INT_MAX;
                    } else {
                        dp[j + 1] += dp[j];
                    }
                }
            }
        }

        return dp[n];
    }
};