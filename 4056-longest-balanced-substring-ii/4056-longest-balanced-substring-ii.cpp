class Solution {
public:
    void checkBalanced(string &s, int &maxLen, const function<pair<int, int>(int, int, int)>& stateFn) {
        map<pair<int, int>, int> mp;
        mp[{0, 0}] = -1;
        int ca = 0, cb = 0, cc = 0;

        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == 'a')
                ca++;
            else if (s[i] == 'b')
                cb++;
            else
                cc++;

            pair<int, int> curr = stateFn(ca, cb, cc);

            if (mp.count(curr)) {
                maxLen = max(maxLen, i - mp[curr]);
            } else {
                mp[curr] = i;
            }
        }
    }
    int longestBalanced(string s) {
        int maxLen = 0;

        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(ca - cb, cb - cc); });

        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(ca - cb, cc);
        });
        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(ca - cc, cb);
        });
        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(cb - cc, ca);
        });
        
        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(cb, cc); }); // a only
        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(ca, cc); }); // b only
        checkBalanced(s,maxLen,[](int ca, int cb, int cc) { return make_pair(ca, cb); }); // c only

        return maxLen;
    }
};