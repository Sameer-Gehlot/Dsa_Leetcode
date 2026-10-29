
class Solution {
    int LOG, n;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, initialMask;
    vector<int> bitTree;
    string s;
    int timer = 0;

    // Fenwick Tree: XOR point updates
    // and prefix XOR queries.
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bitTree[idx] ^= val;
        }
    }

    int getPrefix(int idx) {
        int ans = 0;
        for (; idx > 0; idx -= idx & -idx) {
            ans ^= bitTree[idx];
        }
        return ans;
    }

    // XOR update on inclusive range [l, r].
    void rangeXor(int l, int r, int val) {
        add(l, val);
        if (r + 1 <= n) {
            add(r + 1, val);
        }
    }

    int charMask(char c) {
        return 1 << (c - 'a');
    }

    int currentPrefix(int u) {
        return initialMask[u] ^ getPrefix(tin[u]);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[j][u];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        this->s = s;
        timer = 0;

        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n, 0));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        initialMask.assign(n, 0);
        bitTree.assign(n + 1, 0);

        // Iterative DFS. A node is processed on entry;
        // reverse order calculates subtree sizes.
        vector<int> parent(n, -1), order;
        vector<int> st = {0};

        parent[0] = 0;
        initialMask[0] = charMask(s[0]);

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            tin[u] = ++timer;
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                initialMask[v] =
                    initialMask[u] ^ charMask(s[v]);

                up[0][v] = u;

                for (int j = 1; j < LOG; j++) {
                    up[j][v] = up[j - 1][up[j - 1][v]];
                }

                st.push_back(v);
            }
        }

        up[0][0] = 0;
        for (int j = 1; j < LOG; j++) {
            up[j][0] = 0;
        }

        vector<int> subtreeSize(n, 1);

        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            subtreeSize[parent[u]] += subtreeSize[u];
        }

        for (int u = 0; u < n; u++) {
            tout[u] = tin[u] + subtreeSize[u] - 1;
        }

        vector<bool> answer;

        for (const string& q : queries) {
            if (q[0] == 'u') {
                // "update u c"
                int u = 0;
                int i = 7;

                while (i < (int)q.size() && q[i] == ' ') i++;
                while (i < (int)q.size() &&
                       q[i] >= '0' && q[i] <= '9') {
                    u = u * 10 + (q[i] - '0');
                    i++;
                }

                while (i < (int)q.size() && q[i] == ' ') i++;
                char c = q[i];

                int delta = charMask(s[u]) ^ charMask(c);

                if (delta != 0) {
                    rangeXor(tin[u], tout[u], delta);
                    s[u] = c;
                }
            } else {
                // "query u v"
                int u = 0, v = 0;
                int i = 6;

                while (i < (int)q.size() && q[i] == ' ') i++;
                while (i < (int)q.size() &&
                       q[i] >= '0' && q[i] <= '9') {
                    u = u * 10 + (q[i] - '0');
                    i++;
                }

                while (i < (int)q.size() && q[i] == ' ') i++;
                while (i < (int)q.size() &&
                       q[i] >= '0' && q[i] <= '9') {
                    v = v * 10 + (q[i] - '0');
                    i++;
                }

                int w = lca(u, v);

                int mask = currentPrefix(u)
                         ^ currentPrefix(v)
                         ^ charMask(s[w]);

                answer.push_back(
                    mask == 0 || (mask & (mask - 1)) == 0
                );
            }
        }

        return answer;
    }
};
