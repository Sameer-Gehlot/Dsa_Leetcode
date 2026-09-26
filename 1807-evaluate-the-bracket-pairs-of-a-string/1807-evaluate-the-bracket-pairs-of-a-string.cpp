class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key -> value
        for (auto& k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans;

        for (int i = 0; i < s.size(); ) {

            if (s[i] == '(') {
                // Find closing bracket
                int j = i + 1;

                while (s[j] != ')') {
                    j++;
                }

                // Extract key
                string key = s.substr(i + 1, j - i - 1);

                // Replace with value if known
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += '?';

                // Move after ')'
                i = j + 1;
            }
            else {
                ans += s[i];
                i++;
            }
        }

        return ans;
    }
};