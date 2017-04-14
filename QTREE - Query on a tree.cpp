        #include "bits/stdc++.h"
        using namespace std;
        
        /*
          Key: Heavy Light Decomposition, Tree Decomposition, Range Minimum/Maximum Query
          Category: Data Structure
        */
        
        
        typedef pair <int, int> edge;
        vector <edge> v;
         
        vector <edge> g[10010];
        int heavy[10010];
        int sub[10010];
        int chain[10010];
        int pa[10010];
        int head[10010];
        int cost[10010];
        int dep[10010];
         
        int n;
        int t[10010 * 4];
        int pos[10010];
         
        void update(int x, int val, int c = 1, int b = 1, int e = n) {
        	if(b == e) {
        		t[c] = val;
        		return ; 
        	}
        	int m = (b + e) >> 1;
        	int l = c << 1;
        	int r = l + 1;
        	if(x <= m) update(x, val, l, b, m);
        	else update(x, val, r, m+1, e);
        	t[c] = max(t[l], t[r]);
        }
        int query(int x, int y, int c = 1, int b = 1, int e = n) {
        	if(x <= b and e <= y) {
        		return t[c];
        	}
        	if(y < b or e < x) return 0;
        	int m = (b + e) >> 1;
        	int l = c << 1;
        	int r = l + 1;
        	return max(query(x, y, l, b, m), query(x, y, r, m+1, e));
        }
         
        void dfs(int x, int par) {
        	pa[x] = par;
        	heavy[x] = -1;
        	sub[x] = 1;
        	for(unsigned j = 0; j < g[x].size(); j++) {
        		edge k = g[x][j];
         
        		int i = k.first;
        		if(i == par) continue;
        		cost[i] = k.second;
        		dep[i] = 1 + dep[x];
         
        		dfs(i, x);
        		sub[x] += sub[i];
        		if(heavy[x] == -1 or sub[heavy[x]] < sub[i]) {
        			heavy[x] = i;
        		}
        	}
        }
        void init() {
        	dfs(1, 1);
        	int num = 0;
        	int position = 1;
         
        	for(int i = 1; i <= n; i++) {
        		if(pa[i] == -1 or heavy[pa[i]] != i) {
        			++num;
        			for(int k = i; k != -1; k = heavy[k]) {
        				pos[k] = position++;
        				update(pos[k], cost[k]);
         
        				chain[k] = num;
        				head[k] = i;
        			}
        		}
        	}
        }
         
        int answer(int u, int v) {
        	int ans = 0;
        	while(chain[u] != chain[v]) {
        		if(dep[head[u]] > dep[head[v]]) swap(u, v);
        		ans = max(ans, query(pos[head[v]], pos[v]));
        		v = pa[head[v]]; 
        	}
        	if(dep[u] > dep[v]) swap(u, v);
        	if(dep[heavy[u]] <= dep[v]) ans = max(ans, query(pos[heavy[u]], pos[v]));
        	return ans;
        }
         
        int main(int argc, char const *argv[])
        {	
        	int test;
        	scanf("%d", &test);
         
        	for(int cs = 1; cs <= test; cs++) {
        		scanf("%d", &n);
         
        		memset(t, 0, sizeof t);
        		v.clear();
        		for(int i = 1; i <= n; i++) g[i].clear();
         
        		v.push_back(edge(-1, -1));
        		for(int i = 1; i < n; i++) {
        			int p, q, r;
        			scanf("%d %d %d", &p, &q, &r);
        			g[p].push_back(edge(q, r));
        			g[q].push_back(edge(p, r));
        			v.push_back(edge(p, q));
        		}
        		init();
        		for(int i = 1; i < n; i++) {
        			if(pa[v[i].first] == v[i].second) swap(v[i].first, v[i].second);
        		}
        		while(1) {
        			char s[15];
        			int x, y;
        			scanf("%s", s);
        			if(s[0] == 'D') break;
         
        			scanf("%d %d", &x, &y);
        			if(s[0] == 'Q') {
        				printf("%d\n", answer(x, y));
        			} else {
        				update(pos[v[x].second], y);
        			}
        		}
        	}
        	return 0;
        }  
