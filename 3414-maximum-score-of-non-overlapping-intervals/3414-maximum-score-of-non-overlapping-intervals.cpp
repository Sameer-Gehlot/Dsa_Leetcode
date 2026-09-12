class Solution {
public:

    struct Node {
        int l, r, w, idx;
    };

    // Return true if a is lexicographically smaller than b
    bool smaller(vector<int>& a, vector<int>& b) {
        return lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        vector<Node> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting point
        sort(a.begin(), a.end(), [](const Node& x, const Node& y) {
            if (x.l != y.l)
                return x.l < y.l;

            return x.idx < y.idx;
        });

        // Store all starting points for binary search
        vector<int> starts(n);

        for (int i = 0; i < n; i++) {
            starts[i] = a[i].l;
        }

        /*
            dp[i][k] =
            best answer using intervals from i onward,
            with at most k intervals.
        */

        vector<vector<long long>> dp(
            n + 1,
            vector<long long>(5, 0)
        );

        vector<vector<vector<int>>> chosen(
            n + 1,
            vector<vector<int>>(5)
        );

        // Process from right to left
        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: skip current interval
                dp[i][k] = dp[i + 1][k];
                chosen[i][k] = chosen[i + 1][k];

                // Find first interval whose start > current end
                int next = upper_bound(
                    starts.begin(),
                    starts.end(),
                    a[i].r
                ) - starts.begin();

                // Option 2: take current interval
                long long takeScore =
                    a[i].w + dp[next][k - 1];

                vector<int> takeIndices = chosen[next][k - 1];

                takeIndices.push_back(a[i].idx);

                // Keep indices sorted for lexicographical comparison
                sort(takeIndices.begin(), takeIndices.end());

                if (takeScore > dp[i][k]) {

                    dp[i][k] = takeScore;
                    chosen[i][k] = takeIndices;

                } else if (takeScore == dp[i][k] &&
                           smaller(takeIndices, chosen[i][k])) {

                    chosen[i][k] = takeIndices;
                }
            }
        }

        return chosen[0][4];
    }
};