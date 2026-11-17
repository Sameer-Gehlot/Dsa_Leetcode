
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // Precompute minimum changes for every substring.
        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                // Try every proper divisor of len.
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    // Check all d groups.
                    for (int r = 0; r < d; r++) {
                        int left = i + r;
                        int right = i + r + 
                                    ((len - 1 - r) / d) * d;

                        while (left < right) {
                            if (s[left] != s[right]) {
                                changes++;
                            }

                            left += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // DP: dp[t][i] = minimum changes to partition
        // first i characters into exactly t substrings.
        vector<vector<int>> dp(
            k + 1, vector<int>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int t = 1; t <= k; t++) {
            for (int i = 2 * t; i <= n; i++) {

                // Last substring starts at j.
                for (int j = 2 * (t - 1); j <= i - 2; j++) {

                    if (dp[t - 1][j] == INF) continue;

                    dp[t][i] = min(
                        dp[t][i],
                        dp[t - 1][j] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
