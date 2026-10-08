class Solution {
public:
    string removeOuterParentheses(string s) {
        
        string ans;
        int balance = 0;

        for (char c : s) {

            if (c == '(') {
                balance++;

                // Outer opening bracket nahi hai
                if (balance > 1) {
                    ans += c;
                }
            }
            else {
                balance--;

                // Outer closing bracket nahi hai
                if (balance > 0) {
                    ans += c;
                }
            }
        }

        return ans;
    }
};