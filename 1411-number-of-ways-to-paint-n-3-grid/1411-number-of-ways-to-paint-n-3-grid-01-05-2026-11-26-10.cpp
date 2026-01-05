class Solution {
public:
  int numOfWays(int n) {
    const int MOD = 1e9 + 7;

    long long patternABA = 6, patternABC = 6;


    while (--n) {
      long long nextPatternABA = (patternABA * 3 + patternABC * 2) % MOD;

      long long nextPatternABC = (patternABA * 2 + patternABC * 2) % MOD;

      patternABA = nextPatternABA;

      patternABC = nextPatternABC;
    }


    return static_cast<int>((patternABA + patternABC) % MOD);
  }
};