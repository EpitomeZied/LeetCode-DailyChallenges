/**
 * @param {number} left
 * @param {number} right
 * @return {number}
 */
var countPrimeSetBits = function (left, right) {
    const primes = new Set([2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]);

    const popcount = (x) => {
        let count = 0;
        while (x !== 0) {
            x &= (x - 1);
            count++;
        }
        return count;
    };

    let ans = 0;
    for (let n = left; n <= right; n++) {
        if (primes.has(popcount(n))) ans++;
    }
    return ans;

};