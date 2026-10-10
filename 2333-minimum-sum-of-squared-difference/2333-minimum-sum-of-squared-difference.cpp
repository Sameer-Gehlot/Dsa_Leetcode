
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        long long k = 1LL * k1 + k2;

        vector<int> freq(100001, 0);
        long long total = 0;
        int maxDiff = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);

            freq[d]++;
            total += d;
            maxDiff = max(maxDiff, d);
        }

        // All differences can become zero.
        if (k >= total) {
            return 0;
        }

        // Reduce the largest differences in groups.
        for (int d = maxDiff; d > 0 && k > 0; d--) {
            long long take = min(k, (long long)freq[d]);

            freq[d] -= take;
            freq[d - 1] += take;
            k -= take;
        }

        // Calculate the final sum of squares.
        long long ans = 0;

        for (int d = 1; d <= maxDiff; d++) {
            ans += 1LL * freq[d] * d * d;
        }

        return ans;
    }
};
