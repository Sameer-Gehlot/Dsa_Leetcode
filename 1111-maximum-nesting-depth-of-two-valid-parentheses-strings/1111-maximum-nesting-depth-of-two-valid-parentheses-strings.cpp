class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans(seq.size());

        int depth = 0;

        for (int i = 0; i < seq.size(); i++) {
            if (seq[i] == '(') {
                depth++;

                // Assign based on current depth
                ans[i] = depth % 2;
            } 
            else {
                // Closing bracket belongs to the same level
                ans[i] = depth % 2;

                depth--;
            }
        }

        return ans;
    }
};