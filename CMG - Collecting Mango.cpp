#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/*
  key: Greedy
*/
 
#define mod     1000000007
 
string call(string &a, string &b) {
    string c = "";
    bool flag = false;
    for(int i = 0; i < a.size(); i ++) {
        if(!flag) {
            if(i == a.size() - 1) {
                c += b[i];
                continue;
            }
            if(a[i] >= b[i]) c += a[i];
            else {
                if(i == 0) {
                    c += a[i];
                    continue;
                }
                c += b[i], flag = true;
            }
        } else c += b[i];
    }
    return c;
}
 
int main() {
    ios_base::sync_with_stdio(false), cin.tie(false);
    int T;
    cin >> T;
    for(int cs = 1; cs <= T; cs ++) {
        string a, b;
        cin >> a >> b;
        bool flag = false;
        string c = max(call(a, b), call(b, a));
        ll ans = 0, p = 1;
        for(int i = c.size() - 1; i >= 0; i --) {
            if(c[i] == '1') {
                ans = (ans + p) % mod;
            }
            p = ((p * 2) % mod);
        }
        cout << "Case " << cs << ": " << ans << '\n';
    }
    cout.flush();
}
