#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    vector<ll> xs;
    static const int MAXN = 400000 * 4; 
    int nodes[MAXN];
    ll covered[MAXN];

    int nSeg; 
    int merge(const int &a, const int &b) {
        return a + b; 
    }

    void build(int ni = 0, int ns = 0, int ne = 0) {
        nodes[ni] = 0;
        covered[ni] = 0;
        if (ns == ne) return;
        int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;
        build(l, ns, m);
        build(r, m + 1, ne);
    }

    void pull(int ni, int ns, int ne) {
        if (nodes[ni] > 0) {
            covered[ni] = xs[ne + 1] - xs[ns];
        } else {
            if (ns == ne) covered[ni] = 0;
            else {
                int l = ni * 2 + 1, r = l + 1;
                covered[ni] = covered[l] + covered[r];
            }
        }
    }

    void update(int qs, int qe, int v, int ni, int ns, int ne) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && ne <= qe) {
            nodes[ni] += v;
            pull(ni, ns, ne);
            return;
        }
        int l = ni * 2 + 1, r = l + 1, m = ns + (ne - ns) / 2;
        update(qs, qe, v, l, ns, m);
        update(qs, qe, v, r, m + 1, ne);
        pull(ni, ns, ne);
    }

    struct Event {
        ll y;
        int delta;
        int l, r;
        bool operator<(const Event& other) const {
            return y < other.y;
        }
    };

    double separateSquares(vector<vector<int>>& squares) {
        int n = (int)squares.size();
        xs.reserve(2 * n);

        for (auto &sq : squares) {
            ll x = sq[0], len = sq[2];
            xs.push_back(x);
            xs.push_back(x + len);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        nSeg = (int)xs.size() - 1;
        if (nSeg <= 0) return 0.0;

        vector<Event> events;
        events.reserve(2 * n);

        for (auto &sq : squares) {
            ll x = sq[0], y = sq[1], len = sq[2];
            ll x2 = x + len, y2 = y + len;

            int L = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
            int R = (int)(lower_bound(xs.begin(), xs.end(), x2) - xs.begin());
            int segL = L;
            int segR = R - 1;
            if (segL <= segR) {
                events.push_back({y,  +1, segL, segR});
                events.push_back({y2, -1, segL, segR});
            }
        }

        sort(events.begin(), events.end());
        if (events.empty()) return 0.0;
        build(0, 0, nSeg - 1);

        long double totalArea = 0.0L;
        ll prevY = events[0].y;

        int i = 0, m = (int)events.size();
        while (i < m) {
            ll y = events[i].y;
            ll dy = y - prevY;

            if (dy != 0) {
                totalArea += (long double)covered[0] * (long double)dy;
                prevY = y;
            }

            while (i < m && events[i].y == y) {
                update(events[i].l, events[i].r, events[i].delta, 0, 0, nSeg - 1);
                i++;
            }
        }

        long double half = totalArea / 2.0L;
        build(0, 0, nSeg - 1);

        long double acc = 0.0L;
        prevY = events[0].y;
        i = 0;

        while (i < m) {
            ll y = events[i].y;
            ll dy = y - prevY;

            if (dy != 0) {
                long double stripArea = (long double)covered[0] * (long double)dy;

                if (acc + stripArea >= half) {
                    if (covered[0] == 0) return (double)prevY;
                    long double need = half - acc;
                    long double ansY = (long double)prevY + need / (long double)covered[0];
                    return (double)ansY;
                }

                acc += stripArea;
                prevY = y;
            }

            while (i < m && events[i].y == y) {
                update(events[i].l, events[i].r, events[i].delta, 0, 0, nSeg - 1);
                i++;
            }

            if (fabsl(acc - half) <= 1e-18L) return (double)prevY;
        }

        return (double)prevY;
    }
};
