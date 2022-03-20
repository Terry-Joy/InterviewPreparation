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

## 72.编辑距离
考虑$dp[i][j]$表示将a的前i个字母和b的前j个字母匹配完成所需要的最小步数，考虑所有操作对A执行，假如$s1[i] == s2[j], 则dp[i][j] = dp[i - 1][j - 1]$, 否则考虑增删替换，即可解决，注意初始化的时候，$dp[0][i]$和$dp[i][0]$一起初始化了，如果压维，进入行的时候再初始化。

```cpp
//O(nm) O(nm)
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= n; ++i)
            dp[i][0] = i;
        for (int i = 0; i <= m; ++i)
            dp[0][i] = i;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1])  
                    dp[i][j] = dp[i - 1][j - 1];
                else 
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
        return dp[n][m];
    }
};

//O(nm) O(m)
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> dp(m + 1, 0);
        for (int i = 0; i <= m; ++i)
            dp[i] = i; //dp[0][i]
        for (int i = 1; i <= n; ++i) {
            int pre = dp[0];//dp[i - 1][j - 1]
            dp[0] = i; //dp[i][0]
            for (int j = 1; j <= m; ++j) {
                int now = dp[j];//dp[i - 1][j]
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = pre;
                } else {
                    dp[j] = min(pre, min(dp[j - 1], now)) + 1;
                }
                pre = now;
            }
        }
        return dp[m];
    }
};
```

## 94.二叉树中序遍历
递归不说，迭代的话利用栈的思想，首先在根非空的时候，一直往左走并压栈，假如为空的时候，就可以弹出栈顶，并且走右子树了，注意当栈非空和根非0都是满足的。
//递归O(n) O(n)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        function<void(TreeNode*)> dfs = [&](TreeNode* x) {
            if (!x)
                return;
            dfs(x->left);
            ans.emplace_back(x->val);
            dfs(x->right);
        };
        dfs(root);
        return ans;
    }
};

//迭代 O(n) O(n)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root)
            return ans;
        stack<TreeNode*> tmp;
        while (!tmp.empty() || root) {
            if (root) {
                tmp.push(root);
                root = root->left;
            } else {
                auto it = tmp.top();
                tmp.pop();
                ans.emplace_back(it->val);
                root = it->right;
            }
        }
        return ans;
    }
};

## 394 字符串解码
这个问题实际上是括号匹配问题，我们可以考虑用栈来解决，我们可以考虑整个字符串为如下结构 a5[b]。 相当于最外层可以看成a = ""罢了，记录当前的数字和字母，每次遇到左括号的时候，就压入栈中，然后将字母和数字清空，相当于存下了a和5，遇到右括号的时候，弹出栈顶，同时把当前累积的字符串乘上数字，并且加上栈中的字母，相当于是 a + 5*b， 
```cpp
class Solution {
public:
    string decodeString(string s) {
        int now = 0;
        string ans = "";
        stack<pair<int, string>> st;
        for (auto u : s) {
            if (isdigit(u)) {
                now = now * 10 + (u - '0');
            } else if (u == '['){//左括号的时候把...[]中的...和当前重复数字压栈
                st.push({now, ans});
                ans = "";
                now = 0;
            } else if (u == ']') {
                auto [a, b] = st.top();
                st.pop();
                string tmp = "";
                for (int i = 0; i < a; ++i) //..5[..] 内部括号为tmp 
                    tmp += ans;
                ans = b + tmp;
            } else 
                ans += u;
        }
        return ans;
    }
};
```

## 239
煞笔题，deque模拟下单调队列就好了
//单调队列 O(n)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> st;
        vector<int> ans;        
        for (int i = 0; i < nums.size(); ++i) {
            while (!st.empty() && nums[i] >= nums[st.back()]) {
                st.pop_back();
            }
            st.push_back(i);
            while (st.size() >= 2 && st.back() - st.front() >= k) {
                st.pop_front();
            }
            if (i >= k - 1) 
                ans.emplace_back(nums[st.front()]);
        }
        return ans;
    }
};

## 200
煞笔题，bfs或者dfs都可以秒。如果不加vis用 0标记也可，也可用dsu合并1，但是常数更大。
```cpp
//bfs O(nm) O(nm)
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool> (m, false));
        auto check = [&](int i, int j) {
            return i >= 0 && i < n && j >= 0 && j < m && !vis[i][j] && grid[i][j] == '1';
        };
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!vis[i][j] && grid[i][j] == '1') {
                    ans++;
                    vis[i][j] = true;
                    queue<pair<int, int> > q;
                    q.push({i, j});
                    while (!q.empty()) {
                        auto [u, v] = q.front();
                        q.pop();
                        if (check(u, v + 1)) {
                            q.push({u, v + 1});
                            vis[u][v + 1] = true;
                        } 
                        if (check(u + 1, v)) {
                            q.push({u + 1, v});
                            vis[u + 1][v] = true;
                        }
                        if (check(u - 1, v)) {
                            q.push({u - 1, v});
                            vis[u - 1][v] = true;
                        } 
                        if (check(u, v - 1)) {
                            q.push({u, v - 1});
                            vis[u][v - 1] = true;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
```cpp

## 234.回文链表
两个方法
+ O(n) O(n) 
存入数组后双指针判断即可。

+ O(n) O(1) 
利用快慢指针找到中点，确定前后两部分，假如是奇数，中间的数属于前面，然后反转后半部分和前半部分比较即可，注意要反转回来，不修改原链表。
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *low = head, *fast = head;
        while (fast->next && fast->next->next) {
            low = low->next;
            fast = fast->next->next;
        }
        ListNode *fiEnd = low, *seSt = low->next;
        auto reverseList = [&](ListNode *start) {
            ListNode *pre = nullptr, *cur = start;
            while (cur) {
                ListNode *tmp = cur->next;
                cur->next = pre;
                pre = cur;
                cur = tmp;
            }
            return pre;
        };
        ListNode* tmp = reverseList(seSt);
        bool ans = true;
        while (tmp) {
            if (head->val != tmp->val) {
                ans = false;
                break;
            }
            head = head->next;
            tmp = tmp->next;
        }
        low->next = reverseList(seSt);
        return ans;
    }
};

## 98.验证二叉搜索树
```cpp
本质上是通过中序遍历判断是否有序即可.
//中序递归遍历 O(n) O(n)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> ans;
        bool flag = true;
        function<void(TreeNode*)> dfs = [&](TreeNode *x) {
            if (!x)return;
            dfs(x->left);
            if (ans.size() >= 1 && x->val <= ans.back()) {
                flag = false;
            } 
            ans.emplace_back(x->val);
            dfs(x->right);
        };
        dfs(root);
        return flag;
    }
};

迭代就是不断走左压栈,直到遇到空的时候才弹出栈顶,弹出栈顶意味着该节点的左子树已经全部遍历完, 所以输出本身, 根变成该节点的右子树.
//中序迭代遍历 
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> ans;
        vector<TreeNode*> st;
        while (st.size() >= 1 || root) {
            if (root) {
                st.emplace_back(root);
                root = root->left;
            } else {
                auto it = st.back();
                st.pop_back();
                ans.emplace_back(it->val);
                root = it->right;
            }
        }        
        for (int i = 1; i < ans.size(); ++i) {
            if (ans[i] <= ans[i - 1]) {
                return false;
            }
        }
        return true;
    }
};
```

## 102 二叉树层序遍历
bfs，每次统计队列当前层数节点数量，一次性拿完即可。
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root)
            return ans;
        vector<int> tmp;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                auto it = q.front();
                q.pop();
                tmp.emplace_back(it->val);
                if (it->left) {
                    q.push(it->left);
                }
                if (it->right) {
                    q.push(it->right);
                }
            }
            ans.emplace_back(tmp);
            tmp.clear();
        }
        return ans;
    }
};
```

## 279
+ dp的做法太sb不讲了，直接d，O(nsqrt(n)) O(n)
+ 讲讲脑残规律法，直接cv官方了
  [![bgAKbT.png](https://s1.ax1x.com/2022/03/08/bgAKbT.png)](https://imgtu.com/i/bgAKbT)

## 146 LRU缓存
采用哈希表维护一个链表，链表的node保存key，value和前后指针即可。头部尾部初始化避免边界，我们发现其实只需要两个函数，一个是删除一个节点，一个是把节点从头节点插入。然后暴力模拟即可。

## 287 
n + 1个数，数字在[1，n]内，可知至少存在一个重复的整数，且只存在唯一重复的数，不修改数组实现O（1）空间
+ 二分 O(nlogn) O(1) 
考虑二分范围[1, n]，统计小于等于mid的数量，假如小于等于mid的数量> mid的话，显然答案一定在[l, mid]间，抽屉原理即可得出，否则在[mid + 1, r]间，以为边界就是[1,2,3,xxx]，取mid恰好和前面连续的时候

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int l = 1, n = nums.size(), r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (nums[i] <= mid) {
                    cnt++;
                }
            if (cnt > mid) {
                r = mid;
            } else 
                l = mid + 1;
        }
        return r;
    }
};

76.最小覆盖子串
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 

+ 双指针+哈希表
  用一个哈希表存t字母出现次数，枚举右端点，左端点单调前进即可。注意要在合法的时候才能前进。

牛客top101

3.无重复字符的最长子串
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
枚举右端点，哈希表存某个字母最后出现的位置即可，发现重复就更新左端点位置。

4.链表
k个一组翻转链表
主要的思想是先建立一个虚拟节点，每次查询的时候先往前k步看可不可行，如果可行的话，就得到fi往后k步的一个反转的三指针，分别是下一个反转后的头尾，和尾的下一个，调整指针后fi等于下一个的头，就变成子问题了，注意k等于1和节点为空的时候直接返回即可.

4.寻找两个正序数组的中位数
大无语题，我们可以转化成求两个有序数组的第k小问题，考虑奇数就是n/2 + 1, 偶数就是n/2, n/2 + 1，
两个有序数组第k小问题可以二分思想来解决，注意边界情况，就是两边越界，还有k==1的时候，

[0, k/2 - 1], [0, k/2 - 1];
```cpp
while (true) {
	// 边界情况
	if (index1 == length1) {
		return nums2[index2 + k - 1];
	}
	if (index2 == length2) {
		return nums1[index1 + k - 1];
	}
	if (k == 1) {
		return Math.min(nums1[index1], nums2[index2]);
	}
	
	// 正常情况
	int half = k / 2;
	int newIndex1 = Math.min(index1 + half, length1) - 1;
	int newIndex2 = Math.min(index2 + half, length2) - 1;
	int pivot1 = nums1[newIndex1], pivot2 = nums2[newIndex2];
	if (pivot1 <= pivot2) {
		k -= (newIndex1 - index1 + 1);
		index1 = newIndex1 + 1;
	} else {
		k -= (newIndex2 - index2 + 1);
		index2 = newIndex2 + 1;
	}
}