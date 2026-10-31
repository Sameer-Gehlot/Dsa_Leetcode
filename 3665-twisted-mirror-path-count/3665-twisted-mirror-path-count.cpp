
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {

        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // Stores final destination after mirror chains.
        // -1 means invalid path.

        vector<vector<int>> fromLeft(m, vector<int>(n, -1));
        vector<vector<int>> fromTop(m, vector<int>(n, -1));

        // Encode cell (i, j) as i * n + j.
        // Decode using / n and % n.

        // STEP 1: Precompute mirror destinations.
        // Reverse order ensures dependencies are calculated first.

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (grid[i][j] == 0) continue;

                // Entering mirror from LEFT -> DOWN
                if (i + 1 < m) {

                    if (grid[i + 1][j] == 0) {
                        fromLeft[i][j] = (i + 1) * n + j;
                    }
                    else {
                        fromLeft[i][j] = fromTop[i + 1][j];
                    }
                }

                // Entering mirror from TOP -> RIGHT
                if (j + 1 < n) {

                    if (grid[i][j + 1] == 0) {
                        fromTop[i][j] = i * n + (j + 1);
                    }
                    else {
                        fromTop[i][j] = fromLeft[i][j + 1];
                    }
                }
            }
        }

        // STEP 2: Normal DP on reachable empty cells.

        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                long long ways = dp[i][j];

                // TRY MOVING RIGHT
                if (j + 1 < n) {

                    int dest;

                    if (grid[i][j + 1] == 0) {
                        dest = i * n + (j + 1);
                    }
                    else {
                        dest = fromLeft[i][j + 1];
                    }

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + ways) % MOD;
                    }
                }

                // TRY MOVING DOWN
                if (i + 1 < m) {

                    int dest;

                    if (grid[i + 1][j] == 0) {
                        dest = (i + 1) * n + j;
                    }
                    else {
                        dest = fromTop[i + 1][j];
                    }

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + ways) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
