#include "bits/stdc++.h"
using namespace std;

/*
  key: Greedy
*/
 
#define input()                 freopen("C:\\Users\\safayet007\\Desktop\\in.txt", "r", stdin)
#define output()                freopen("C:\\Users\\safayet007\\Desktop\\out.txt", "w", stdout);
#define FOR(i, a, b)            for(__typeof(b) i = a; i <= b; i++)
#define REP(i, a)               for(__typeof(a) i = 0; i < a; i++)
#define REPN(i, a)              for(__typeof(a) i = 1; i <= a; i++)
#define ITERATE(it, v)          for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)
#define D(x)                    cout << #x << " = " << (x) << endl
#define bitcount                __builtin_popcount			
#define oo                      (INT_MAX / 2)	
#define pb                      push_back
#define mp                      make_pair
#define gcd                     __gcd
#define endl                    '\n'
 
typedef long long LL;
typedef pair <int, int> pii;
 
#define N_MAX 10005
 
struct cow {
	int g, d;
	bool operator<(cow const& c) const {
		return g < c.g;
	}
} cows[N_MAX];
 
inline bool sort_by_d(cow const& a, cow const& b) {
	return a.d > b.d;
}
 
int main (int argc, char const *argv[]) {
	//ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
 		freopen ("C:\\Users\\safayet007\\Desktop\\in.txt", "r", stdin);
		freopen ("C:\\Users\\safayet007\\Desktop\\out.txt", "w", stdout);
	#endif
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &cows[i].g);
		scanf("%d", &cows[i].d);
	}
	sort(cows, cows + n, sort_by_d);
	int curcow = 0, total = 0;
	priority_queue<cow> q;
	for (int t = 10000; t >= 1; t--) {
		while (curcow < n && t <= cows[curcow].d) {
			q.push(cows[curcow]);
			curcow++;
		}
		if (q.size() > 0) {
			total += q.top().g;
			q.pop();
		}
	}
	printf("%d\n", total);
	fflush (stdout); 
	return 0;
} 
