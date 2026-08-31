/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prev = -1;

        int minDist = INT_MAX;
        int pos = 1;

        ListNode* prevNode = head;
        ListNode* curr = head->next;

        while (curr != nullptr && curr->next != nullptr) {
            
            // Check if current node is a critical point
            bool isCritical =
                (curr->val > prevNode->val && curr->val > curr->next->val) ||
                (curr->val < prevNode->val && curr->val < curr->next->val);

            if (isCritical) {
                
                // First critical point
                if (first == -1) {
                    first = pos;
                }
                
                // We already have a previous critical point
                else {
                    minDist = min(minDist, pos - prev);
                }

                // Update previous critical point
                prev = pos;
            }

            prevNode = curr;
            curr = curr->next;
            pos++;
        }

        // Fewer than two critical points
        if (first == -1 || prev == first) {
            return {-1, -1};
        }

        // Maximum distance = last critical point - first critical point
        int maxDist = prev - first;

        return {minDist, maxDist};
    }
};