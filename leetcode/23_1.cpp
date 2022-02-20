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
//分治 O(knlogk) O(k)
class Solution {
public:
    ListNode* merge(ListNode*x1, ListNode *x2) {
        if (!x1 || !x2) 
            return x1 ? x1 : x2; 
        ListNode * head = new ListNode(0), *a = x1, *b = x2;
        ListNode *tmp = head;
        while (a && b) {
            if (a->val < b->val) {
                tmp->next = a;
                a = a->next;
            } else {
                tmp->next = b;
                b = b->next;
            }
            tmp = tmp->next;
        }
        tmp->next = (a ? a : b);
        return head->next;
    }
    ListNode * solve(const vector<ListNode*>& lists, int l,int r) {
        if (l == r) 
            return lists[l];
        if (l > r)
            return nullptr;
        int mid = (l + r) >> 1;
        return merge(solve(lists, l, mid), solve(lists, mid + 1, r));
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return solve(lists, 0, lists.size() - 1);
    }
};