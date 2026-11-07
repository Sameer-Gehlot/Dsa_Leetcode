
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // {freeTime, weight, index}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > busy;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long currentTime = 0;

        for (int j = 0; j < m; j++) {

            currentTime = max(currentTime, (long long)j);

            // Release all servers that have completed their tasks.
            while (!busy.empty() &&
                   get<0>(busy.top()) <= currentTime) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If all servers are busy, jump to the earliest free time.
            if (available.empty()) {

                currentTime = get<0>(busy.top());

                // Release every server that becomes free at this time.
                while (!busy.empty() &&
                       get<0>(busy.top()) <= currentTime) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Choose the best available server.
            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;

            // Assign task and update server's free time.
            busy.push({
                currentTime + tasks[j],
                weight,
                index
            });
        }

        return ans;
    }
};
