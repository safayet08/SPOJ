#include "bits/stdc++.h"
using namespace std;

/*
  Key: COnvex Hull Trick
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
 
struct line {
    LL m, c;
    line () {}
    line(LL m_, LL c_) {
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
            if (L[idx + 1].m * x + L[idx + 1].c < L[idx].m * x + L[idx].c) idx += 1;
            else break;
        }
        return L[idx].m * x + L[idx].c;
    }
} solve;
 
int main () {
    //ios_base::sync_with_stdio(false); cin.tie(false);
    vector < pair <LL, LL> > xx, yy;
    int n; scanf("%d", &n);
    REP (i, n) {
        LL x, y; scanf("%lld %lld", &x, &y);
        xx.push_back(mp(x, y));
    }
    sort(xx.begin(), xx.end());
    REP (i, n) {
        while (not yy.empty()) {
            if(yy.back().second <= xx[i].second) yy.pop_back();
            else break;
        }
        yy.push_back(xx[i]);
    }
    LL cost = 0;
    solve.add(yy[0].second, 0);
    int idx = 0, m = yy.size();
    REP (i, m) {
        cost = solve.query(yy[i].first, idx);
        if(i == m) continue;
        solve.add(yy[i + 1].second, cost);
    }
    printf("%lld\n", cost);
    return 0;
} 
