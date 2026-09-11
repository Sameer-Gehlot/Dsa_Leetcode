class Solution {
public:
    int totalNumbers(vector<int>& digits) {

        int freq[10] = {};

        // Count frequency of each digit
        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // First digit
        for (int a = 1; a <= 9; a++) {

            if (freq[a] == 0)
                continue;

            // Second digit
            for (int b = 0; b <= 9; b++) {

                if (freq[b] == 0)
                    continue;

                // Third digit must be even
                for (int c = 0; c <= 8; c += 2) {

                    if (freq[c] == 0)
                        continue;

                    // Check if we have enough copies
                    if (a == b && b == c) {
                        if (freq[a] >= 3)
                            ans++;
                    }
                    else if (a == b) {
                        if (freq[a] >= 2)
                            ans++;
                    }
                    else if (a == c) {
                        if (freq[a] >= 2)
                            ans++;
                    }
                    else if (b == c) {
                        if (freq[b] >= 2)
                            ans++;
                    }
                    else {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};