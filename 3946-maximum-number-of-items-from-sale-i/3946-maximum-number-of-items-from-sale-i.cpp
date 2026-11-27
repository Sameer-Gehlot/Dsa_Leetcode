class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        // Count frequency of each factor
        vector<int> freq(1501, 0);

        for (auto& item : items) {
            freq[item[0]]++;
        }

        // Precompute how many items have factors
        // divisible by each factor
        vector<int> divisibleCount(1501, 0);

        for (int f = 1; f <= 1500; f++) {
            for (int multiple = f; multiple <= 1500; multiple += f) {
                divisibleCount[f] += freq[multiple];
            }
        }

        // DP: maximum items with budget capacity b
        vector<int> dp(budget + 1, 0);

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            int reward = divisibleCount[factor];

            // First purchase activates this item type
            vector<int> activated(budget + 1, -1e9);

            for (int b = price; b <= budget; b++) {
                activated[b] = dp[b - price] + reward;
            }

            // Additional copies of the activated type
            for (int b = price; b <= budget; b++) {
                if (activated[b - price] != -1e9) {
                    activated[b] = max(
                        activated[b],
                        activated[b - price] + 1
                    );
                }
            }

            // Either skip this type or activate it
            for (int b = 0; b <= budget; b++) {
                dp[b] = max(dp[b], activated[b]);
            }
        }

        return dp[budget];
    }
};