class Solution {
public:
    int myAtoi(string s) {
        int i = 0, sign = 1, tmp = 0;        //没有符号字符时sign是正数

        while(s[i] == ' ')  ++i;              //1.忽略前导空格

        if(s[i] == '+' || s[i] == '-')        //2.确定正负号
            sign = (s[i++] == '-') ? -1 : 1;  //s[i]为+的话sign依旧为1，为-的话sign为-1

        while(s[i] >= '0' && s[i] <= '9')     //3.检查输入是否合法
        {
            int c = s[i] - '0';
            if (tmp > INT_MAX / 10 || (tmp == INT_MAX / 10 && c > 7))
                return (sign == -1) ? INT_MIN : INT_MAX;
            tmp = tmp * 10 + c;
            ++i;
        }
        return tmp * sign;
    }
};
