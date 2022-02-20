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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode*head=nullptr,*tmp=nullptr;
        int add=0;
        while(l1||l2){
            int sum=(l1?l1->val:0)+(l2?l2->val:0)+add;
            int s=sum%10;
            add=(sum>=10);
            if(!head){
                head=tmp=new ListNode(s);
            }else{
                tmp->next=new ListNode(s);
                tmp=tmp->next;
            }
            if(l1){
                l1=l1->next;
            }
            if(l2){
                l2=l2->next;
            }
        }
        if(add){
            tmp->next=new ListNode(add);
        }
        return head;
    }
};