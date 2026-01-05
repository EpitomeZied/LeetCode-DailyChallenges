#define ll long long
class Solution {
  ll count_divisors(ll num) {
    ll i, counter = 0;
    for (i = 1; i * i < num; i++) {
      if (!(num % i))
        counter += 2;
    }
    if ((i * i) == num)
      counter++;

    return counter;
  }
  ll sum_of_divisors(ll n) {
    ll sum_divisors = 0;
    for (int i = 1; i < sqrt(n); i++)
      if (n % i == 0)
        sum_divisors += ((n / i) + i);
    ll sq = sqrt(n);
    return sum_divisors + (sq * sq == n ? sq : 0);
  }

public:
  int sumFourDivisors(vector<int> &nums) {
    map<int, ll> memo;
    ll ans = 0;
    for (auto &num : nums) {
      if (memo.count(num) and memo[num] != -1)
        ans += memo[num];
      else {
        if (count_divisors(num) == 4) {
          int sum = sum_of_divisors(num);
          ans += sum;
          memo[num] = sum;
        } else
          memo[num] = -1;
      }
    }
    return ans;
  }
};
