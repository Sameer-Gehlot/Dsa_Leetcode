class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // pal[l][r] = true if s[l...r] is a palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        // Build palindrome table
        for (int len = 1; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;

                if (len <= 2) {
                    pal[l][r] = (s[l] == s[r]);
                } else {
                    pal[l][r] = (s[l] == s[r] && pal[l + 1][r - 1]);
                }
            }
        }

        // dp[i] = maximum number of valid palindromes
        // using the first i characters
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't use character i-1
            dp[i] = dp[i - 1];

            // Try every substring ending at i-1
            for (int l = 0; l < i; l++) {
                int len = i - l;

                if (len >= k && pal[l][i - 1]) {
                    dp[i] = max(dp[i], dp[l] + 1);
                }
            }
        }

        return dp[n];
    }
};