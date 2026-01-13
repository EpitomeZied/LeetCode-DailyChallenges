class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        using ll = long long;

        long double total = 0;
        vector<pair<int, int>> events;

        for (auto& sq : squares) {
            int y = sq[1], l = sq[2];
            total += (long double)l * (long double)l;
            events.push_back({y, +l}),events.push_back({y + l, -l});
        }

        long double half = total / 2.0L;

        sort(events.begin(), events.end(),
             [](const auto& a, const auto& b) { return a.first < b.first; });

        long double area = 0.0L;
        long double width = 0.0L;
        int i = 0;
        int prevY = events[0].first;

        while (i < (int)events.size()) {
            int y = events[i].first;
            if (y > prevY && width > 0.0L) {
                long double dy = (long double)(y - prevY);
                long double gain = width * dy;

                if (area + gain >= half) {
                    long double need = half - area;
                    long double ans = (long double)prevY + need / width;
                    return (double)ans;
                }

                area += gain;
            }
            while (i < (int)events.size() && events[i].first == y) {
                width += (long double)events[i].second;
                ++i;
            }

            prevY = y;
        }
        return (double)prevY;
    }
};