class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0)
			return 0;
		int now = 0, x2 = x;
		while (x) {
			if (now > INT_MAX / 10)//特判溢出或ll
				return 0;
			now = now * 10 + x % 10;
			x /= 10;
		}
		return now == x2;
	}
};