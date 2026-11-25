class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<unsigned long long> pref(n + 1, 0);
        vector<unsigned long long> power(n + 1, 1);

        const unsigned long long base = 131;

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] * base + nums[i] + 1;
            power[i + 1] = power[i] * base;
        }

        auto check = [&](int len) {
            unordered_map<unsigned long long, int> freq;

            for (int i = 0; i + len <= n; i++) {
                unsigned long long hash =
                    pref[i + len] - pref[i] * power[len];

                freq[hash]++;
            }

            for (auto& [hash, count] : freq) {
                if (count == 1)
                    return true;
            }

            return false;
        };

        int low = 1, high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (check(mid))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};