class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        int ptr = 0;
        while (ptr < n - 2 && nums[ptr] < nums[ptr + 1]) {
            ptr++;
        }
        if (ptr == 0) {
            return false;
        }
        int ptr2 = ptr;
        while (ptr2 < n - 1 && nums[ptr2] > nums[ptr2 + 1]) {
            ptr2++;
        }
        if (ptr2 == ptr or ptr2 == n - 1) {
            return false;
        }
        while (ptr2 < n - 1 && nums[ptr2] < nums[ptr2 + 1]) {
            ptr2++;
        }
        return ptr2 == n - 1;
    }
};