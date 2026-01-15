class Solution {
public:
    int longestConsecutiveRun(vector<int> a) {
        if (a.empty()) return 0;
        sort(a.begin(), a.end());
        int best = 1, cur = 1;
        for (int i = 1; i < (int)a.size(); i++) {
            if (a[i] == a[i - 1] + 1) {
                cur++;
            } else {
                best = max(best, cur);
                cur = 1;
            }
        }
        best = max(best, cur);
        return best;
    }

    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int maxH = longestConsecutiveRun(hBars); 
        int maxV = longestConsecutiveRun(vBars); 

        int side = min(maxH + 1, maxV + 1);
        return side * side;
    }
};
