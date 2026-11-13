class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {

        int n = nums.size();

        long long ans = 0;
        long long cost = 0;

        int right = n - 1;

        deque<pair<int, int>> st;

        for (int left = n - 1; left >= 0; left--) {

            int cnt = 1;

            // Merge smaller groups
            while (!st.empty() && st.back().first <= nums[left]) {

                auto [val, c] = st.back();
                st.pop_back();

                cost += 1LL * (nums[left] - val) * c;

                cnt += c;
            }

            st.push_back({nums[left], cnt});

            // Reduce window size
            while (cost > k) {

                auto [val, c] = st.front();

                cost -= val - nums[right];

                right--;

                if (c == 1) {
                    st.pop_front();
                }
                else {
                    st.front().second--;
                }
            }

            // Count valid subarrays
            ans += right - left + 1;
        }

        return ans;
    }
};