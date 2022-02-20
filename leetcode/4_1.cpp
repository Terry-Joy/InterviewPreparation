//归并排序后找中位数
// O(n+m) O(n+m)
class Solution {
  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        vector<int> a;
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(),
              back_inserter(a));
        int len = nums1.size() + nums2.size(), L = a.size();
        if (len & 1)
            return a[(L + 1) / 2 - 1];
        else
            return (a[L / 2 - 1] + a[L / 2]) / 2.0;
    }
};