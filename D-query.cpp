#include <bits/stdc++.h>
using namespace std;


/*
	Key : Square-Root Decomposition.
	- Time Limit is strict. So added Fast I/O.
*/



const int N = 30005;
const int block = sqrt (N);
const int M = 200005;
const int LIM = 1000005;

struct data {
	int l, r, idx;
	bool operator < (data x) const {
		if (l/block == x.l/block) return r < x.r;
		else return l/block < x.l/block;
	}
	data () {};

	data (int ll, int rr, int iidx) {
		l = ll; r = rr; idx = iidx;
	}
} qry[M];


int readint() {
	int cc = getc(stdin);
	for (;cc < '0' || cc > '9';)  cc = getc(stdin);
	int ret = 0;
	for (;cc >= '0' && cc <= '9';) {
		ret = ret * 10 + cc - '0';
		cc = getc(stdin);
	}
	return ret;
}

int cnt[LIM];
int x[N];
int result[M];
int L, R, answer;

void add (int pos) {
	cnt[x[pos]] ++;
	// cout << "Added : " << pos << " : " << x[pos] << " " << cnt[x[pos]] << endl;
	if (cnt[x[pos]] == 1) {
		answer ++;
	}
}

void rmv (int pos) {
	// cout << "Removed : " << pos << endl;
	cnt[x[pos]] --;
	if (cnt[x[pos]] == 0) {
		answer --;
	}
}

int query (int qLeft, int qRight) { 
	while (qLeft != L) {
		if (L < qLeft) rmv (L ++);
		else add (-- L);
	}

	while (qRight != R) {
		if (R < qRight) add (++ R);
		else rmv (R --);
	}
	return answer;
}

int main (int argc, char const *argv[]) {

	int n;
	n = readint ();

	for (int i = 1; i <= n; i ++) {
		//scanf ("%d", &x[i]);
		x[i] = readint();
	}

	int q;
	scanf ("%d", &q);
	for (int i = 1; i <= q; i ++) {
		int l, r;
		// scanf ("%d %d", &l, &r);
		l = readint(); r = readint ();
		qry[i] = data (l, r, i);
	}

	sort (qry + 1, qry + q + 1);

	L = 1, R = 0;
	for (int i = 1; i <= q; i ++) {
		result[qry[i].idx] = query (qry[i].l, qry[i].r);
		// cout << qry[i].l << " " << qry[i].r << " -> " << result[qry[i].idx] << endl;
	}

	for (int i = 1; i <= q; i ++) {
		printf ("%d\n", result[i]);
	}

	return 0;
}
