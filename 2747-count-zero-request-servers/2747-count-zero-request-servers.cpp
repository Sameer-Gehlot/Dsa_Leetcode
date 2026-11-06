
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        // Sort logs by timestamp
        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        int m = queries.size();

        // Store query and original index
        vector<pair<int, int>> sortedQueries;

        for (int i = 0; i < m; i++) {
            sortedQueries.push_back({queries[i], i});
        }

        sort(sortedQueries.begin(), sortedQueries.end());

        vector<int> freq(n + 1, 0);
        vector<int> ans(m);

        int left = 0;
        int right = 0;
        int activeServers = 0;

        for (auto& [q, idx] : sortedQueries) {

            // Add logs with time <= q
            while (right < logs.size() && logs[right][1] <= q) {

                int id = logs[right][0];

                if (freq[id] == 0) {
                    activeServers++;
                }

                freq[id]++;
                right++;
            }

            // Remove logs with time < q - x
            while (left < right && logs[left][1] < q - x) {

                int id = logs[left][0];

                freq[id]--;

                if (freq[id] == 0) {
                    activeServers--;
                }

                left++;
            }

            // Count servers with zero requests
            ans[idx] = n - activeServers;
        }

        return ans;
    }
};
