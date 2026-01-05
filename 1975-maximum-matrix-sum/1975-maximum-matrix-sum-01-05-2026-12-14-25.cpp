#define ll long long
class Solution {
public:
    ll maxMatrixSum(vector<vector<int>>& matrix) {
        ll sum = 0;
        ll minAbs = LLONG_MAX;
        ll negativeCount = 0;

        for (const auto& row : matrix) {
            for (ll val : row) {
                if (val < 0) negativeCount++;
                ll absVal = abs(val);
                sum += absVal;
                minAbs = min(minAbs, absVal);
            }
        }

        if (negativeCount % 2 == 1) {
            sum -= 2 * minAbs;
        }

        return sum;
    }
};