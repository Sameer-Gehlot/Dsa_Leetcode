class Solution {
public:
    string s;
    int pos = 0;

    // Cartesian product / concatenation
    set<string> combine(set<string>& a, set<string>& b) {
        set<string> res;

        for (const string& x : a) {
            for (const string& y : b) {
                res.insert(x + y);
            }
        }

        return res;
    }

    // Parse one expression
    set<string> parse() {
        set<string> result;
        set<string> current;

        while (pos < s.size() && s[pos] != '}') {

            if (s[pos] == ',') {
                // Union
                for (const string& x : current)
                    result.insert(x);

                current.clear();
                pos++;
            }

            else if (s[pos] == '{') {
                pos++;  // skip '{'

                set<string> inside = parse();

                pos++;  // skip '}'

                if (current.empty()) {
                    current = inside;
                } else {
                    current = combine(current, inside);
                }
            }

            else {
                // Single letter
                string word(1, s[pos]);
                pos++;

                set<string> letter = {word};

                if (current.empty()) {
                    current = letter;
                } else {
                    current = combine(current, letter);
                }
            }
        }

        // Add the final part
        for (const string& x : current)
            result.insert(x);

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> ans = parse();

        return vector<string>(ans.begin(), ans.end());
    }
};