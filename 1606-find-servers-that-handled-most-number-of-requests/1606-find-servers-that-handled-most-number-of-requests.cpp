
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        int n = arrival.size();

        // Available servers
        set<int> available;

        for(int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finishTime, serverId}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        // Number of requests handled by each server
        vector<int> count(k, 0);

        for(int i = 0; i < n; i++) {

            int time = arrival[i];

            // Release all servers that have completed processing
            while(!busy.empty() && busy.top().first <= time) {

                int server = busy.top().second;

                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request
            if(available.empty()) {
                continue;
            }

            // Preferred server
            int start = i % k;

            // Find next available server
            auto it = available.lower_bound(start);

            // Wrap around if necessary
            if(it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Remove server from available set
            available.erase(it);

            // Update request count
            count[server]++;

            // Calculate completion time
            long long finishTime = (long long)time + load[i];

            // Mark server as busy
            busy.push({finishTime, server});
        }

        // Find maximum requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for(int i = 0; i < k; i++) {
            if(count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
