





class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> tree(n), newTree(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            tree[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        // DFS 1: Find new parents using original tree
        function<void(int)> dfs1 = [&](int u) {
            int c = s[u] - 'a';
            int old = last[c];

            // If matching ancestor exists, change parent
            if (u != 0 && last[c] != -1) {
                newParent[u] = last[c];
            }

            last[c] = u;

            for (int v : tree[u]) {
                dfs1(v);
            }

            // Restore previous ancestor
            last[c] = old;
        };

        dfs1(0);

        // Build modified tree
        for (int i = 1; i < n; i++) {
            newTree[newParent[i]].push_back(i);
        }

        vector<int> answer(n, 1);

        // DFS 2: Calculate subtree sizes
        function<int(int)> dfs2 = [&](int u) {
            for (int v : newTree[u]) {
                answer[u] += dfs2(v);
            }
            return answer[u];
        };

        dfs2(0);

        return answer;
    }
};