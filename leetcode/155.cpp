//辅助单调栈 O(1) O(n)
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

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */