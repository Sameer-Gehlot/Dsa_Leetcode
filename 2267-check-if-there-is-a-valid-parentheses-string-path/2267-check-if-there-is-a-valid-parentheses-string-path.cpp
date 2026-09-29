class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Total length of the path
        int len = m + n - 1;

        // A valid parentheses string must have even length
        if (len % 2 == 1)
            return false;

        // dp[i][j] = possible balances at cell (i, j)
        vector<vector<bitset<201>>> dp(
            m, vector<bitset<201>>(n)
        );

        // Starting cell must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                int delta = (grid[i][j] == '(' ? 1 : -1);

                // Come from top
                if (i > 0) {
                    for (int balance = 0; balance <= 200; balance++) {
                        if (!dp[i - 1][j][balance])
                            continue;

                        int newBalance = balance + delta;

                        if (newBalance >= 0 && newBalance <= 200)
                            dp[i][j][newBalance] = 1;
                    }
                }

                // Come from left
                if (j > 0) {
                    for (int balance = 0; balance <= 200; balance++) {
                        if (!dp[i][j - 1][balance])
                            continue;

                        int newBalance = balance + delta;

                        if (newBalance >= 0 && newBalance <= 200)
                            dp[i][j][newBalance] = 1;
                    }
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};