
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        // Step 1: Build adjacency list
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }

        // Step 2: Initialize distance array
        const int INF = 1e9;

        vector<vector<int>> dist(n, vector<int>(k + 1, INF));

        // Step 3: Min heap {cost, node, consecutive count}
        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>
        > pq;

        // Starting node
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        // Step 4: Dijkstra's Algorithm
        while (!pq.empty()) {

            auto [cost, u, count] = pq.top();
            pq.pop();

            // Skip outdated states
            if (cost != dist[u][count]) {
                continue;
            }

            // Destination reached
            if (u == n - 1) {
                return cost;
            }

            // Explore neighbours
            for (auto [v, w] : adj[u]) {

                int newCount;

                if (labels[u] == labels[v]) {
                    newCount = count + 1;
                }
                else {
                    newCount = 1;
                }

                // Check consecutive character constraint
                if (newCount > k) {
                    continue;
                }

                int newCost = cost + w;

                // Relaxation
                if (newCost < dist[v][newCount]) {

                    dist[v][newCount] = newCost;

                    pq.push({
                        newCost,
                        v,
                        newCount
                    });
                }
            }
        }

        // No valid path exists
        return -1;
    }
};
