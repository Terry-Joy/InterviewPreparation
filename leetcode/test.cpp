#include<bits/stdc++.h>
using namespace std;
int partition(vector<int> &nums, int k, int l, int r) {
    int i = l, j = r;
    while (i < j) {
        while (i < j && nums[i] <= nums[l])
            i++;
        while (i < j && nums[j] >= nums[l])
            j--;
        swap(nums[i], nums[j]);
    }
    swap(nums[l], nums[i]);
    int target = r - i + 1;
    if (target > k)
        return partition(nums, k, i + 1, r);
    else if (target < k)
        return partition(nums, k - target + 1, l, i);
    else
        return nums[i];
}
int findKthLargest(vector<int> &nums, int k) {
    return partition(nums, k, 0, nums.size() - 1);
}
int main() {
    int n, k;
	cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> k;
	findKthLargest(a, k);
}