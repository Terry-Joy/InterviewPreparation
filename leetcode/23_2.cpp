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
//优先队列 O(knlogk) O(k)
class Solution {
public:
    struct Node {
        int val;
        ListNode *ptr;
        bool operator < (const Node &x) const {
            return val > x.val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<Node> q;
        for (auto u: lists) {
            if (u)
                q.push({u->val, u});
        }
        ListNode *head = new ListNode(0);
        ListNode *tmp = head;
        while (!q.empty()) {
            auto u = q.top();
            q.pop();
            tmp->next = u.ptr;
            if (u.ptr->next)
                q.push({u.ptr->next->val, u.ptr->next});
            tmp = tmp->next;
        }
        return head->next;
    }
};