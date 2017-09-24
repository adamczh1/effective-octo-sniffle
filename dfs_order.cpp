vector<int> t_parent; // parent of vertex
vector<int> t_ord; // order of dfs

void tree_getorder(const vector<vector<int> > &g, int root) {
	int n = g.size();
	t_parent.assign(n + 1, -1);
	t_ord.clear();

	vector<int> stk; stk.push_back(root);
	while (!stk.empty()) {
		int i = stk.back(); stk.pop_back();
		t_ord.push_back(i);
		for (int j = SIZE(g[i]) - 1; j >= 0; j --) {
			int c = g[i][j];
			if (t_parent[c] == -1 && c != root) {
				t_parent[c] = i;
				stk.push_back(c);
			}
		}
	}
}


// euler tour order
int t_TIME = 0;
int t_start[MAXN], t_end[MAXN];
void dfs(int cur, int p = -1) {
	t_start[cur] = ++t_TIME;
	for (int v : adj[cur]) {
        if (v == p) continue;
        dfs(v, cur);
	}
	t_end[cur] = t_TIME;
}
