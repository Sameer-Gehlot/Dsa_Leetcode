
class Solution {
public:

    multiset<long long> lo, hi;
    long long sumLo = 0, sumHi = 0;

    void balance() {

        int total = lo.size() + hi.size();
        int required = (total + 1) / 2;

        while (lo.size() > required) {
            auto it = prev(lo.end());
            long long val = *it;

            lo.erase(it);
            sumLo -= val;

            hi.insert(val);
            sumHi += val;
        }

        while (lo.size() < required) {
            auto it = hi.begin();
            long long val = *it;

            hi.erase(it);
            sumHi -= val;

            lo.insert(val);
            sumLo += val;
        }
    }

    void add(long long num) {

        if (lo.empty() || num <= *lo.rbegin()) {
            lo.insert(num);
            sumLo += num;
        }
        else {
            hi.insert(num);
            sumHi += num;
        }

        balance();
    }

    void remove(long long num) {

        auto it = lo.find(num);

        if (it != lo.end()) {
            sumLo -= num;
            lo.erase(it);
        }
        else {
            auto it2 = hi.find(num);
            sumHi -= num;
            hi.erase(it2);
        }

        balance();
    }

    long long getCost() {

        long long median = *lo.rbegin();

        return median * (long long)lo.size() - sumLo
             + sumHi - median * (long long)hi.size();
    }

    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        vector<long long> cost(n, 0);

        // Calculate minimum cost of every window

        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i] = getCost();
            }
        }

        // DP initialization
        // Zero subarrays = zero cost for every prefix

        const long long INF = 1e18;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {

            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current element
                curr[i] = curr[i - 1];

                // Select a window ending at i-1
                if (i >= x) {

                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - 1]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
