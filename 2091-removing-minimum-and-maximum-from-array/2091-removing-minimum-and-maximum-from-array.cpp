class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find indices of minimum and maximum
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // Make minIndex the smaller index
        if (minIndex > maxIndex)
            swap(minIndex, maxIndex);

        // 1. Remove both from the front
        int fromFront = maxIndex + 1;

        // 2. Remove both from the back
        int fromBack = n - minIndex;

        // 3. Remove min from front and max from back
        int bothEnds = (minIndex + 1) + (n - maxIndex);

        return min({fromFront, fromBack, bothEnds});
    }
};