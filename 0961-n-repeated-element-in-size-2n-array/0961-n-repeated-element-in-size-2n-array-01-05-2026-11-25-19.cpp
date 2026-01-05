#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int repeatedNTimes(vector<int> &nums) {
    vector<int> count(10001, 0);
    for (int i = 0; i < nums.size(); i++) {
      count[nums[i]]++;
      if (count[nums[i]] > 1) {
        return nums[i];
      }
    }
    return -1;
  }
};
