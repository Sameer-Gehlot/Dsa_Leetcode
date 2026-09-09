class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        long long x = 1000;

        while (x <= n) {
            // Every number from x to n
            // has one extra comma at this level.
            ans += n - x + 1;

            // Avoid overflow
            if (x > n / 1000)
                break;

            x *= 1000;
        }

        return ans;
    }
};