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
//递归 O(n) O(n)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head -> next)
            return head;
        ListNode *now = head;
        ListNode *tmp = now->next;
        now->next = swapPairs(tmp->next);
        tmp->next = now;
        return tmp;
    }
};