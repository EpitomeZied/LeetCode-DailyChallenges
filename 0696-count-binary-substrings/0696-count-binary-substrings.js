/**
 * @param {string} s
 * @return {number}
 */
var countBinarySubstrings = function (s) {
    let prev = 0; // length of previous group
    let cur = 1;  // length of current group
    let ans = 0;

    for (let i = 1; i < s.length; i++) {
        if (s[i] === s[i - 1]) {
            cur++;
        } else {
            ans += Math.min(prev, cur);
            prev = cur;
            cur = 1;
        }
    }

    ans += Math.min(prev, cur);
    return ans;
};
