#include <bits/stdc++.h> 
using namespace std; 

const int maxn = 2e5; 
int n, q;
long long a[maxn], dp[1 << 18]; 
vector<int> adj[maxn]; 

void dfs(int u = 0, int p = -1, int d = 0) {
	dp[d ^ ((1 << 18) - 1)] ^= a[u]; 
	for (int v : adj[u]) {
		if (v != p) {
			dfs(v, u, d + 1); 
		}
	}
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); 
	cin >> n >> q; 
	for (int i = 1; i < n; i++) {
		int u, v; 
		cin >> u >> v;
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i]; 
	}
	dfs(); 
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < (1 << 18); j++) {
			if (!(j & 1 << i)) {
				dp[j] ^= dp[j ^ (1 << i)]; 
			}
		}
	}
	while (q--) {
		long long x; 
		cin >> x; 
		cout << (x ? dp[(x - 1) & ((1 << 18) -1)] : a[0]) << "\n"; 
	}
	return 0; 
}
