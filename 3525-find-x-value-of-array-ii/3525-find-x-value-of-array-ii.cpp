class Solution {
public:
    struct Node {
        long long cnt[5] = {};
        int prod = 1;
    };

    int k;
    vector<Node> seg;

    Node mergeNode(const Node& left, const Node& right) {
        Node res;

        // Product of the whole combined segment
        res.prod = (left.prod * right.prod) % k;

        // Prefixes completely inside the left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] += left.cnt[r];
        }

        // Prefixes that use the whole left segment
        // and then some prefix of the right segment.
        for (int r = 0; r < k; r++) {
            int newRem = (left.prod * r) % k;
            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        seg[node] = mergeNode(seg[node * 2], seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            int rem = val % k;

            seg[node] = Node();
            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        seg[node] = mergeNode(seg[node * 2], seg[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        // Completely inside query range
        if (ql <= l && r <= qr)
            return seg[node];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->k = k;

        int n = nums.size();
        seg.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;
            update(1, 0, n - 1, index, value);

            // Get all prefix-product remainders
            // in nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};