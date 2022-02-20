/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
  public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        vector<ListNode *> st;
        ListNode *tmp = head;
        int cnt = 0;
        while (tmp) {
            st.push_back(tmp);
            tmp = tmp->next;
            cnt++;
        }
        if (cnt == n)
            return head->next;
        st[cnt - n - 1]->next = st[cnt - n]->next;
        return st.front();
    }
};