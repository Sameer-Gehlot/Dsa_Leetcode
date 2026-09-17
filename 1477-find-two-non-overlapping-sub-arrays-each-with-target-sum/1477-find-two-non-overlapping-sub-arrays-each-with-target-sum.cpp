class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        const int INF = 1e9;

        // best[i] = minimum length of a valid subarray
        // completely inside arr[0...i-1]
        vector<int> best(n + 1, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window if sum is too large
            while (left <= right && sum > target) {
                sum -= arr[left];
                left++;
            }

            // Copy the previous best answer
            best[right + 1] = best[right];

            // Found a subarray [left...right]
            if (sum == target) {
                int len = right - left + 1;

                // Need another valid subarray before 'left'
                if (best[left] != INF) {
                    ans = min(ans, len + best[left]);
                }

                // Store this subarray as the best one ending at/before right
                best[right + 1] = min(best[right + 1], len);
            }
        }

        return ans == INF ? -1 : ans;
    }
};