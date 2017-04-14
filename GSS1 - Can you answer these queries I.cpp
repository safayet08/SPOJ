#include<bits/stdc++.h>
using namespace std;

/*
  Key: Data Structure (Segment Trees and Range Sum)
*/
 
struct SEG {
 
#define mx      50000
#define inf     1000000000 + 9
 
    int A[mx + 5];
 
    struct node {
        int best_sum, pre_sum, suf_sum, total_sum;
    } tree[mx * 3 + 10];
 
    node make_node(int a, int b, int c, int d) {
        node ret;
        ret.best_sum = a, ret.pre_sum = b, ret.suf_sum = c, ret.total_sum = d;
        return ret;
    }
 
    int BEST(int a, int b, int c, int d, int e, int f) {
        return max(a, max(b, max(c, max(d, max(e, f)))));
    }
 
    node Merge(node left, node right) {
        int best_sum = -inf, pre_sum = -inf, suf_sum = -inf, total_sum = -inf;
        node ret;
        total_sum = left.total_sum + right.total_sum;
        pre_sum = max(left.pre_sum, left.total_sum + right.pre_sum);
        suf_sum = max(right.suf_sum, left.suf_sum + right.total_sum);
        best_sum = BEST(best_sum, pre_sum, suf_sum, left.best_sum, right.best_sum, left.suf_sum + right.pre_sum);
        ret = make_node(best_sum, pre_sum, suf_sum, total_sum);
        return ret;
    }
 
    void initiate(int node, int st, int ed) {
        if(st == ed) {
            int k = A[st];
            tree[node] = make_node(k, k, k, k);
            return;
        }
        int l, r, mid;
        mid = (st + ed) / 2, l = 2 * node, r = 2 * node + 1;
        initiate(l, st, mid);
        initiate(r, mid + 1, ed);
        tree[node] = Merge(tree[l], tree[r]);
    }
 
    node query(int node, int st, int ed, int i, int j) {
        if(st == i && ed == j) {
            return tree[node];
        }
        int l, r, mid;
        mid = (st + ed) / 2, l = 2 * node, r = 2 * node + 1;
 
        if(j <= mid) {
            return query(l, st, mid, i, j);
        }
        if(i > mid) {
            return query(r, mid + 1, ed, i, j);
        }
 
        return Merge(query(l, st, mid, i, mid), query(r, mid + 1, ed, mid + 1, j));
    }
 
    void Clear() {
        memset(A, 0, sizeof(A));
        memset(tree, 0, sizeof(tree));
    }
 
} H;
 
int main() {
    int n, m;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &H.A[i]);
    }
    H.initiate(1, 1, n);
    scanf("%d", &m);
    for(int i = 1; i <= m; i ++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", H.query(1, 1, n, l, r).best_sum);
    }
    return 0;
}
