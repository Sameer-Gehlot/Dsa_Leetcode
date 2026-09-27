class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr;

        for (char c : s) {

            if (c == '(') {
                // Save the string before this bracket
                st.push(curr);
                curr.clear();
            }
            else if (c == ')') {
                // Reverse the current innermost part
                reverse(curr.begin(), curr.end());

                // Add it to the previous level
                curr = st.top() + curr;
                st.pop();
            }
            else {
                curr += c;
            }
        }

        return curr;
    }
};