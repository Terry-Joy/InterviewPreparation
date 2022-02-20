class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int sz=nums.size();
        if(!sz)return 0;
        for(auto it=nums.begin();it!=nums.end();){
            if((*it)==val){
                it=nums.erase(it);
                sz--;
            }else 
                it++;
        }
        return sz;
    }
};