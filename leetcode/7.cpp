class Solution {
  public:
    int reverse(int x) {
        int now = 0, x2 = x;
        while (x) {
            if (now > INT_MAX / 10 || now < INT_MIN / 10)
                return 0;
            now = now * 10 + x % 10;
            x /= 10;
        }
        return now;
    }
};