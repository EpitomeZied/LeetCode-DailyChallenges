class Solution {
public:
    struct Node {
        long long mn, mx, lzAdd, lzSet;

        void setv(long long v) {
            mn = mx = v;
            lzSet = v;
            lzAdd = 0;
        }
        void addv(long long v) {
            mn += v;
            mx += v;
            lzAdd += v;
        }
    };

    struct SegTree {
        int n;
        vector<Node> st;
        static const long long NO_SET = -1;

        SegTree(int n_, long long initVal) : n(n_) {
            st.assign(4 * n, Node{0, 0, 0, NO_SET});
            build(0, 0, n - 1, initVal);
        }

        Node merge(const Node &a, const Node &b) {
            Node res;
            res.mn = std::min(a.mn, b.mn);
            res.mx = std::max(a.mx, b.mx);
            res.lzAdd = 0;
            res.lzSet = NO_SET;
            return res;
        }

        void build(int ni, int ns, int ne, long long initVal) {
            st[ni].lzAdd = 0;
            st[ni].lzSet = NO_SET;
            if (ns == ne) {
                st[ni].mn = st[ni].mx = initVal;
                return;
            }
            int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;
            build(l, ns, m, initVal);
            build(r, m + 1, ne, initVal);
            st[ni] = merge(st[l], st[r]);
        }

        void pushDown(int ni, int ns, int ne) {
            if (ns == ne) return;
            int l = ni * 2 + 1, r = l + 1;

            if (st[ni].lzSet != NO_SET) {
                st[l].setv(st[ni].lzSet);
                st[r].setv(st[ni].lzSet);
                st[ni].lzSet = NO_SET;
            }
            if (st[ni].lzAdd != 0) {
                st[l].addv(st[ni].lzAdd);
                st[r].addv(st[ni].lzAdd);
                st[ni].lzAdd = 0;
            }
        }

        void updateAdd(int qs, int qe, long long v, int ni, int ns, int ne) {
            if (qs > ne || qe < ns) return;
            if (qs <= ns && ne <= qe) {
                st[ni].addv(v);
                return;
            }
            pushDown(ni, ns, ne);
            int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;
            updateAdd(qs, qe, v, l, ns, m);
            updateAdd(qs, qe, v, r, m + 1, ne);
            st[ni] = merge(st[l], st[r]);
        }

        void updateAdd(int l, int r, long long v) {
            if (l > r) return;
            updateAdd(l, r, v, 0, 0, n - 1);
        }

        long long queryPoint(int pos, int ni, int ns, int ne) {
            if (ns == ne) return st[ni].mn;
            pushDown(ni, ns, ne);
            int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;
            if (pos <= m) return queryPoint(pos, l, ns, m);
            return queryPoint(pos, r, m + 1, ne);
        }

        long long queryPoint(int pos) {
            return queryPoint(pos, 0, 0, n - 1);
        }

        int firstEqual(int qs, int qe, long long target, int ni, int ns, int ne) {
            if (qs > ne || qe < ns) return -1;
            if (target < st[ni].mn || target > st[ni].mx) return -1;
            if (ns == ne) return ns;

            pushDown(ni, ns, ne);
            int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;

            int left = firstEqual(qs, qe, target, l, ns, m);
            if (left != -1) return left;
            return firstEqual(qs, qe, target, r, m + 1, ne);
        }

        int firstEqual(int l, int r, long long target) {
            if (l > r) return -1;
            return firstEqual(l, r, target, 0, 0, n - 1);
        }
    };

    int longestBalanced(std::vector<int>& nums) {
        int N = (int)nums.size();

        int SZ = N + 1;


        SegTree st(SZ, N+5);

        unordered_map<int,int> last;

        int ans = 0;

        for (int r = 0; r < N; r++) {
            int x = nums[r];
            int s = (x % 2 == 0) ? +1 : -1;

            auto it = last.find(x);
            if (it != last.end()) {
                int p = it->second;
                st.updateAdd(p + 1, N, -s);
            }
            st.updateAdd(r + 1, N, +s);
            last[x] = r;

            long long target = st.queryPoint(r + 1);   
            int k = st.firstEqual(0, r, target);         
            if (k != -1) ans = std::max(ans, (r + 1) - k);
        }

        return ans;
    }
};
