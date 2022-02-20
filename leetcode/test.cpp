#include <bits/stdc++.h>
#define fi first 
#define se second
using namespace std;
using ll = long long;
using PII = pair<int, int>;

const int N = 5007;
const int MX = 1e9 + 7;
int n, w;
PII a[N];
int ans[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
    cin >> n >> w;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].fi;
        a[i].se = i;
    }

    int res = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j)
            if (a[j].fi < a[i].fi && abs(a[j].se - a[i].se) <= w)
                ans[i] = max(ans[i], ans[j] + 1);
        res = max(res, ans[i]);
    }

    cout << res;
    return 0;
}