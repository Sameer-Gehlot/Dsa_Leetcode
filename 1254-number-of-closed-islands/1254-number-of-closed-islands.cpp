
class Solution {
public:
    bool dfs(vector<vector<int>>& grid, int i, int j) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Out of bounds means this island is not closed
        if (i < 0 || j < 0 || i >= rows || j >= cols) {
            return false;
        }

        // Water or already visited
        if (grid[i][j] == 1) {
            return true;
        }

        // Mark land as visited
        grid[i][j] = 1;

        // Explore all four directions
        bool up = dfs(grid, i - 1, j);
        bool down = dfs(grid, i + 1, j);
        bool left = dfs(grid, i, j - 1);
        bool right = dfs(grid, i, j + 1);

        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    if (dfs(grid, i, j)) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};
