class Solution {
public:
    bool checkValidString(string s) {

        int low = 0;
        int high = 0;

        for (char ch : s) {

            if (ch == '(') {
                low++;
                high++;
            }

            else if (ch == ')') {
                low--;
                high--;
            }

            else { // '*'
                low--;   // * treated as ')'
                high++;  // * treated as '('
            }

            // We can never have fewer than 0 unmatched '('
            low = max(low, 0);

            // Even our maximum possibility is invalid
            if (high < 0)
                return false;
        }

        return low == 0;
    }
};