/**
 * Author: Nalin Bhardwaj
 * Date: 2020-01-25
 * License: CC0
 * Source: Self - https://codeforces.com/contest/827/submission/29309549
 * Description: LCA table with offline update support.
 * Time: Updates are $O(N \log N)$ total.
 */

const int maxn = int(2e5)+5, maxlog = 20, inf = int(1e9)+5;
 
int n, m, T[maxn][maxlog+1], TT[maxn][maxlog+1], F[maxn][maxlog+1], H[maxn], upar[maxn], P[maxn], taken[maxn], res[maxn];
pair<pair<int, int>, pair<int, int>> E[maxn];
vector<pair<int, int>> graph[maxn];
 
void dfs0(int node, int par, int income, int dep) {
	upar[node] = income;
	T[node][0] = par;
	H[node] = dep;
	if(income != -1) TT[node][0] = E[income].first.first;
	for(auto it: graph[node]) {
		if(it.first != par) dfs0(it.first, node, it.second, dep+1);
	}
}
 
void init()
{
	for(int j = 1;j <= maxlog;j++) {
		for(int i = 0;i < n;i++) {
			if(T[i][j-1] != -1) {
				T[i][j] = T[T[i][j-1]][j-1];
				TT[i][j] = max(TT[i][j-1], TT[T[i][j-1]][j-1]);
			}
		}
	}
}
 
void onit()
{
	for(int j = maxlog;j > 0;j--) {
		for(int i = 0;i < n;i++) {
			F[i][j-1] = min(F[i][j-1], F[i][j]);
			if(T[i][j-1] != -1) {
				int node = T[i][j-1];
				F[node][j-1] = min(F[node][j-1], F[i][j]);
			}
		}
	}
}
 
int qry(int x, int y)
{
	if(H[x] > H[y]) swap(x, y);
	int res = -inf;
	for(int i = maxlog;i >= 0;i--) {
		if(H[y]-(1<<i) >= H[x]) {
			res = max(res, TT[y][i]);
			y = T[y][i];
		}
	}
	if(x == y) return res;
	for(int i = maxlog;i >= 0;i--) {
		if(T[x][i] != T[y][i]) {
			res = max(res, TT[x][i]);
			res = max(res, TT[y][i]);
			x = T[x][i], y = T[y][i];
		}
	}
	res = max(res, TT[x][0]);
	res = max(res, TT[y][0]);
	return res;
}
 
void upd(int x, int y, int c)
{
	if(H[x] > H[y]) swap(x, y);
	for(int i = maxlog;i >= 0;i--) {
		if(H[y]-(1<<i) >= H[x]) {
			F[y][i] = min(F[y][i], c);
			y = T[y][i];
		}
	}
	if(x == y) return;
	for(int i = maxlog;i >= 0;i--) {
		if(T[x][i] != T[y][i]) {
			F[x][i] = min(F[x][i], c), F[y][i] = min(F[y][i], c);
			x = T[x][i], y = T[y][i];
		}
	}
	F[x][0] = min(F[x][0], c), F[y][0] = min(F[y][0], c);
}

// Initialise before input
for(int i = 0;i < n;i++) P[i] = i;
for(int i = 0;i < n;i++) {
	for(int j = 0;j <= maxlog;j++) T[i][j] = -1, TT[i][j] = F[i][j] = inf;
}

// Initialise after input
dfs0(0, -1, -1, 0);
init();

// Update structure
for(all u, v, c) upd(u, v, c);
onit(); // After all upd()s.
