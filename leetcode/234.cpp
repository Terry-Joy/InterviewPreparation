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