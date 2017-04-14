#include<bits/stdc++.h>
#define MAXN 100000+10
using namespace std;
typedef long long LL;
 
struct segment_tree
{
    struct node
    {
        int st;
        int en;
        int mid;
        LL value;
    };
 
    node tree[4 * MAXN];
    LL lazy[4 * MAXN];
    segment_tree () {}
 
    void init_tree(int idx, int b, int e)
    {
 
        tree[idx].st = b, tree[idx].en = e, tree[idx].mid = (b+e)/2;
 
        int left, right, md;
        left = 2*idx, right = 2*idx + 1, md = (b+e)/2;
 
        if (b != e) ///If idx isn't a leaf.
        {
            init_tree(left, b, md);
            init_tree(right, md+1, e);
            tree[idx].value = tree[left].value + tree[right].value;
        }
 
        ///or if there is an array of elements given we initiate the tree value with that array
        ///and all idx of lazy at first would be 0.
        tree[idx].value = lazy[idx] = 0;
    }
 
    LL getValue(int idx)
    {
        ///Under the idx node total tree[idx].en - tree[idx].st + 1 leafs
        /// We multiply this value for every leaf, that's the propagation technique.
        return tree[idx].value + (lazy[idx] * (long long) (tree[idx].en - tree[idx].st + 1));
    }
 
    ///Pushes down the propagation value to the immediate children of idx.
    ///Clears the propagation value at idx.
    void refresh(int idx)
    {
        int left, right;
        left = 2*idx, right = 2*idx + 1;
 
        lazy[left] += lazy[idx];
        lazy[right] += lazy[idx];
        lazy[idx] = 0;
    }
 
    void update(int idx, int i, int j, int value)
    {
        ///If the segment is completely in the range we move no further
        ///We just add value to lazy[idx]
        if (tree[idx].st >= i && tree[idx].en <= j)
        {
            lazy[idx] += value;
            return;
        }
 
        ///If the segment isn't in the range any of it
        if (tree[idx].st > j || tree[idx].en < i)
            return;
 
        ///Some part of the segment is in the range
        ///Thus we need to go to both the children of idx
        int left, right, md;
        left = 2*idx, right = 2*idx + 1, md = (i+j)/2;
 
        if (tree[idx].st <= i || tree[idx].en >= j)
        {
            refresh(idx);
            update(left, i, j, value);
            update(right, i, j, value);
            tree[idx].value = getValue(left) + getValue(right);
        }
    }
 
    LL query(int idx, int i, int j)
    {
        if (tree[idx].st >= i && tree[idx].en <= j)
            return getValue(idx);
 
        if (tree[idx].st > j || tree[idx].en < i)
            return 0;
 
        LL result = 0;
        int left, right, md;
        left = 2*idx, right = 2*idx + 1, md = (i+j)/2;
        if (tree[idx].st < i || tree[idx].en > j)
        {
            refresh(idx);
            result = query(left, i, j) + query(right, i, j);
            tree[idx].value = getValue(left) + getValue(right);
        }
        return result;
    }
 
    void Clear()
    {
        int i;
        for(i=0; i<=4*MAXN; i++)
            tree[i].value = 0, tree[i].st = 0, tree[i].en = 0, tree[i].mid = 0;
    }
};
 
segment_tree TREE;
 
int main()
{
    int T, p, q, v, i;
    scanf("%d", &T);
    int A[1000];
    while (T--)
    {
        int n,c;
        scanf("%d", &n);
        scanf("%d", &c);
 
        //TREE.Clear();
        TREE.init_tree(1, 1, n);
        for (i=1; i<=c; i++)
        {
            scanf("%d", &n);
            if (n == 0)
            {
                scanf("%d %d %d", &p, &q, &v);
                TREE.update(1, p, q, v);
            }
            else
            {
                scanf("%d%d", &p, &q);
                printf("%lld\n", TREE.query(1, p, q));
            }
        }
    }
    return 0;
}
