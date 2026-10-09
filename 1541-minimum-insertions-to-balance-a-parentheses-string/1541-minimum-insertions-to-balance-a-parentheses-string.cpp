
class Solution {
public:
    int minInsertions(string s) {
        int open = 0;
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '(') {
                open++;
            }
            else {
                // If the next character is not ')',
                // insert one closing bracket.
                if (i + 1 >= s.length() || s[i + 1] != ')') {
                    ans++;
                }
                else {
                    // Consume the second ')' as well.
                    i++;
                }

                // No unmatched opening bracket?
                if (open == 0) {
                    ans++;
                    open++;
                }

                // This closing pair matches one '('.
                open--;
            }
        }

        // Every remaining '(' needs two ')'.
        ans += open * 2;

        return ans;
    }
};
