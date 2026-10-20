
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;
            int prevMax = 0;

            for (int start = 0; start < n; start += k) {
                int end = start + k - 1;
                int mn = nums[start];
                int mx = nums[start];
                int descents = 0;

                for (int j = start; j <= end; j++) {
                    mn = min(mn, nums[j]);
                    mx = max(mx, nums[j]);

                    if (j < end && nums[j] > nums[j + 1]) {
                        descents++;
                    }
                }

                if (nums[end] > nums[start]) {
                    descents++;
                }

                if (descents > 1) {
                    valid = false;
                    break;
                }

                if (start > 0 && prevMax > mn) {
                    valid = false;
                    break;
                }

                prevMax = mx;
            }

            if (valid) {
                ans += k;
            }
        }

        return ans;
    }
};
