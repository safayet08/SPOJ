#include "bits/stdc++.h"
using namespace std;

/*
  Key: Convex Hull Trick
*/
 
#define input()                   freopen("C:\\Users\\safayet007\\Desktop\\in.txt", "r", stdin)
#define output()                  freopen("C:\\Users\\safayet007\\Desktop\\out.txt", "w", stdout);
#define FOR(i, a, b)              for(__typeof(b) i = a; i <= b; i++)
#define REP(i, a)                 for(__typeof(a) i = 0; i < a; i++)
#define REPN(i, a)                for(__typeof(a) i = 1; i <= a; i++)
#define ITERATE(it, v)            for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)
#define D(x)                      cout << #x << " = " << (x) << endl
#define all(v)                    (v).begin(), (v).end()
#define SET(a, val)               memset(a, val, sizeof a)
#define pb                        push_back
#define mp                        make_pair
#define endl                      '\n'
 
typedef long long LL;
 
const int MAX = 1000000;
LL x[MAX + 5], cs[MAX + 5], dp[MAX + 5];
 
struct line {
    LL m, c;
    line () {}
    line (LL m_, LL c_) {
        m = m_; c = c_;
    }
    bool operator < (line d) const {
        return m < d.m;
    }
};
 
struct CHT {
    vector <line> L;
    bool bad(line a, line b, line c) {
        return (c.c - a.c) * (a.m - b.m) < (b.c - a.c) * (a.m - c.m);
    }
    void add(LL m, LL c) {
        L.push_back(line(m, c));
        int sz = L.size();
        if(sz < 3) return;
        while (bad(L[sz - 3], L[sz - 2],L[sz - 1])) {
            L.erase(L.end() - 2); sz --;
            if(sz < 3) break;
        }
    }
    LL query(LL x, int &idx) {
        int sz = L.size();
        if (idx >= sz)
            idx = sz - 1;
        while (idx < sz - 1) {
            if (L[idx + 1].m * x + L[idx + 1].c > L[idx].m * x + L[idx].c) idx += 1;
            else break;
        }
        return L[idx].m * x + L[idx].c;
    }
} solve;
 
LL get_val(LL a, LL b, LL c, int idx) {
    LL ret = (a * cs[idx] * cs[idx]) + (b * cs[idx]) + c;
    return ret;
}
 
LL get_m(LL a, LL b, LL c, int idx) {
    LL ret = (- 2 * a * cs[idx]);
    return ret;
}
 
LL get_c(LL a, LL b, LL c, int idx) {
    LL ret = dp[idx] + (a * cs[idx] * cs[idx]) - (b * cs[idx]);
    return ret;
}
 
int main () {
    int n, T; LL a, b, c;
    scanf("%d", &T);
    while(T --) {
        scanf("%d %lld %lld %lld", &n, &a, &b, &c);
        REPN (i, n) {
            scanf("%d", &x[i]);
            cs[i] = (x[i] + cs[i - 1]);
        }
        dp[1] = get_val(a, b, c, 1); solve.L.clear();
        solve.add( get_m(a, b, c, 1) , get_c(a, b, c, 1));
        for(int i = 2, idx = 0; i <= n; i ++) {
            dp[i] = get_val(a, b, c, i);
            dp[i] = max(dp[i], dp[i] + solve.query(cs[i], idx));
            solve.add( get_m(a, b, c, i) , get_c(a, b, c, i));
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
