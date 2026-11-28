class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;
        int maxFactor = 0;

        for (auto& item : items) {
            minPrice = min(minPrice, item[1]);
            maxFactor = max(maxFactor, item[0]);
        }

        // Count how many items have each factor
        vector<int> freq(maxFactor + 1, 0);

        for (auto& item : items) {
            freq[item[0]]++;
        }

        // Calculate the free-item gain for each factor
        vector<int> gain(maxFactor + 1, 0);

        for (int f = 1; f <= maxFactor; f++) {
            for (int multiple = f; multiple <= maxFactor; multiple += f) {
                gain[f] += freq[multiple];
            }

            if (gain[f] > 0)
                gain[f]--;
        }

        // Collect profitable double-value purchases
        vector<pair<int, int>> deals;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            if (gain[factor] > 0 && 1LL * price < 2LL * minPrice) {
                deals.push_back({price, gain[factor]});
            }
        }

        // Cheapest deals first
        sort(deals.begin(), deals.end());

        long long ans = 0;
        long long remainingBudget = budget;

        // Buy double-value copies
        for (auto& deal : deals) {
            int price = deal.first;
            int limit = deal.second;

            long long count = min(
                (long long)limit,
                remainingBudget / price
            );

            ans += count * 2;
            remainingBudget -= count * price;
        }

        // Use leftover budget for ordinary copies
        ans += remainingBudget / minPrice;

        return (int)ans;
    }
};