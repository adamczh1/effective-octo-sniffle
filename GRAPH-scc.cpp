// tarjan
int N, M;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN];
vector<int> stk;
bool onstk[MAXN];
int Time;
vector<vector<int> > sccs;

void dfs(int cur) {
	dfn[cur] = low[cur] = ++Time;
	stk.push_back(cur);
	onstk[cur] = true;
	for (int v : adj[cur]) {
		if (!dfn[v]) {
			dfs(v);
			low[cur] = min(low[cur], low[v]);
		} else if (onstk[v]) {
			low[cur] = min(low[cur], dfn[v]);
		}
	}
	if (low[cur] == dfn[cur]) {
		vector<int> scc;
		while (stk.back() != cur) {
			scc.push_back(stk.back());
			onstk[stk.back()] = false;
			stk.pop_back();
		}
		assert(stk.back() == cur);
		scc.push_back(stk.back());
		onstk[stk.back()] = false;
		stk.pop_back();
		sccs.push_back(scc);
	}
}

// kosaraju
int N, M;
vector<int> adj[MAXN];
vector<int> radj[MAXN];
int vis[MAXN];
vector<vector<int> > sccs;

// "toposort"
vector<int> topo;
void dfs(int cur) {
	vis[cur] = 1;
	for (int v : adj[cur]) {
		if (!vis[v]) dfs(v);
	}
	topo.push_back(cur);
}

vector<int> scc;
void dfs2(int cur) {
	vis[cur] = 1;
	scc.push_back(cur);
	for (int v : radj[cur]) {
		if (!vis[v]) dfs2(v);
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int A, B;
		scanf("%d %d", &A, &B);
		adj[A].push_back(B);
		radj[B].push_back(A);
	}
	for (int i = 1; i <= N; i++) {
		if (!vis[i]) dfs(i);
	}
	reverse(topo.begin(), topo.end());
	memset(vis, 0, sizeof vis);
	for (int v : topo) {
		if (!vis[v]) {
			dfs2(v);
			sccs.push_back(scc);
			scc.clear();
		}
	}
	return 0;
}
