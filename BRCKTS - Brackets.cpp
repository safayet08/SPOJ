    #include<bits/stdc++.h>
    using namespace std;
    
    /*
      key: Range Sum and Segment Trees (Data Structure)
    */
    
     
    #define mx 40000
     
    char seq[mx + 5];
    struct info {
        int sum, minsum;
    } tree[3 * mx + 10];
     
    info Merge(info left, info right) {
        info ret;
        ret.sum = left.sum + right.sum;
        ret.minsum = min(left.minsum, left.sum + right.minsum);
        return ret;
    }
     
    void init(int node, int st, int ed) {
        if(st == ed) {
            tree[node].sum = tree[node].minsum = (seq[st] == '(' ? 1 : -1);
            return;
        }
        int mid, l, r;
        mid = (st + ed) / 2, l = 2 * node, r = 2 * node + 1;
        init(l, st, mid);
        init(r, mid + 1, ed);
        tree[node] = Merge(tree[l], tree[r]);
    }
     
    void update(int node, int st, int ed, int pos) {
        if(st == ed) {
            tree[node].sum = tree[node].minsum = -tree[node].sum;
            return;
        }
        int mid, l, r;
        mid = (st + ed) / 2, l = 2 * node, r = 2 * node + 1;
        if(pos <= mid) {
            update(l, st, mid, pos);
        } else {
            update(r, mid + 1, ed, pos);
        }
        tree[node] = Merge(tree[l], tree[r]);
    }
     
    int main() {
        int len, q, i, pos, test = 1;
        while(scanf("%d", &len) ==1 ) {
            scanf("%s", seq);
            init(1, 0, len-1);
            printf("Test %d:\n", test++);
            scanf("%d", &q);
            for(i = 0; i < q; i++) {
                scanf("%d", &pos);
                if(!pos) {
                    if(!tree[1].sum && !tree[1].minsum) {
                        printf("YES\n");
                    } else {
                        printf("NO\n");
                    }
                } else {
                    update(1, 0, len-1, pos-1);
                }
            }
        }
        return 0;
    } 
