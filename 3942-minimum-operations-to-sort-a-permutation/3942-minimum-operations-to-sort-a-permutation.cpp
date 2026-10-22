
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }

        bool increasing = true;
        bool decreasing = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] + i) % n) {
                increasing = false;
            }

            if (nums[i] != (nums[0] - i + n) % n) {
                decreasing = false;
            }
        }

        int ans = INT_MAX;

        // Case 1: Increasing circular order
        if (increasing) {
            // Rotate left, or reverse twice to rotate right
            ans = min(zero, n - zero + 2);
        }

        // Case 2: Decreasing circular order
        if (decreasing) {
            int k = (zero + 1) % n;

            // One reversal plus the minimum rotations
            int cost = 1 + min(k, n - k);

            ans = min(ans, cost);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
