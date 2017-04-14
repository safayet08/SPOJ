#include<bits/stdc++.h>
using namespace std;

/*
  key: Matrix Exponention
*/
 
typedef long long int LL;
 
const int mod = 1000000007;
const int D = 35;
 
struct matrix {
    LL mat[D + 2][D + 2], dim;
    matrix () {}
    matrix(int d) {
        dim = d;
        for(int i = 1; i <= dim; i++) {
            for(int j = 1; j <= dim; j++) {
                mat[i][j] = (i == j);
            }
        }
    }
    matrix operator * (const matrix &r) {
        matrix ret = matrix(dim);
        assert(dim == r.dim);
        for(int i = 1; i <= dim; i++) {
            for(int j = 1; j <= dim; j++) {
                ret.mat[i][j] = 0;
                for(int k = 1; k <= ret.dim; k++) {
                    ret.mat[i][j] = (ret.mat[i][j] + ((LL) mat[i][k] * r.mat[k][j]) % mod) % mod;
                }
            }
        }
        return ret;
    }
};
 
inline matrix expo(matrix &in, LL p) {
    matrix ret = matrix(in.dim), aux = in;
    while(p) {
        if(p & 1) {
            ret = ret * aux;
        }
        aux = aux * aux;
        p >>= 1;
    }
    return ret;
}
 
inline LL power(LL a, LL p) {
    LL ret = 1, x = a;
    while (p) {
        if (p & 1) {
            ret = (ret * x), ret %= mod;
        }
        x %= mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    for(int cs = 1; cs <= T; cs ++) {
        int n, k, t;
        scanf("%d %d %d", &t, &k, &n);
        LL ans = 0, f[31];
        if(t == 1) {
            ans = power((LL)k, (LL)n);
            printf("%lld\n", ans);
        } else if(t == 0) {
            ans = 0;
            printf("%lld\n", ans);
        } else {
            f[0] = 1;
            f[t] = power((k + 1), t) - 1;
            f[t] = (f[t] + mod) % mod;
            for(int i = 1; i < t; i ++) {
                f[i] = (k + 1) * f[i - 1] % mod;
                f[i] %= mod, f[i] += mod, f[i] %= mod;
            }
            if(n <= t) {
                printf("%lld\n", f[n]);
                continue;
            } else {
                int d = (t + 1);
                matrix T = matrix(d);
                T.mat[1][1] = (k + 1), T.mat[1][d] = -(k);
                for(int i = 2; i <= d; i ++) {
                    T.mat[i][i - 1] = 1, T.mat[i][i] = 0;;
                }
                T = expo(T, (LL) n - t);
                for(int i = 1, j = t; i <= d; i ++, j --) {
                    ans = (ans + T.mat[1][i] * f[j]) % mod;
                }
                ans = (ans + mod) % mod;
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
