## 155.最小栈
+ O(1) O(n) 辅助栈做法
利用一个辅助栈保存当前最小值。push的时候判断下就好了
```cpp
class MinStack {
public:
    stack<int> st;
    stack<int> help;
    MinStack() {
    }
    
    void push(int val) {
        st.push(val);
        if (help.empty()) {
            help.push(val);
        } else if (val >= help.top()) {
            help.push(help.top());
        } else 
            help.push(val);
    }
    
    void pop() {
        if (st.empty())
            return;
        st.pop();
        help.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return help.top();
    }
};
```

+ O(1) O(n) 利用一个栈完成
和上面那个做法几乎一样，一个当前值，一个最小值。
```cpp
class MinStack {
public:
    stack<int> st;
    MinStack() {
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push(val);
            st.push(val);
        } else {
            int mn = st.top();
            st.push(val);
            if (val >= mn) {
                st.push(mn);
            } else 
                st.push(val);
        }
    }
    
    void pop() {
        if (st.empty())
            return;
        st.pop();
        st.pop();
    }
    
    int top() {
        int mn = st.top();
        st.pop();
        int ans = st.top();
        st.push(mn);
        return ans;
    }
    
    int getMin() {
        return st.top();
    }
};
```
+ O(1) O(1) 待补