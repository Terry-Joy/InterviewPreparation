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
//迭代 O(n) O(n)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head -> next)
            return head;
        ListNode * now = head;
        head = new ListNode(0);
        ListNode *pre = head;
        pre->next = now;
        while (now->next) {
            ListNode *tmp = now->next;
            now->next = tmp->next;
            tmp->next = now;
            pre->next = tmp;
            pre = now;
            now = now->next;
            if (!now)
                break;
        }
        return head->next;
    }
};