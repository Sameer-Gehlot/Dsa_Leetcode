class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1000000007;

        long long N = n + k - 1;
        long long R = 2 * k;

        // factorial
        vector<long long> fact(N + 1, 1);
        vector<long long> invFact(N + 1, 1);

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        // Fast power
        auto power = [&](long long a, long long b) {
            long long res = 1;

            while (b > 0) {
                if (b & 1)
                    res = res * a % MOD;

                a = a * a % MOD;
                b >>= 1;
            }

            return res;
        };

        invFact[N] = power(fact[N], MOD - 2);

        for (int i = N; i >= 1; i--) {
            invFact[i - 1] = invFact[i] * i % MOD;
        }

        // C(N, R)
        long long ans = fact[N];

        ans = ans * invFact[R] % MOD;
        ans = ans * invFact[N - R] % MOD;

        return (int)ans;
    }
};