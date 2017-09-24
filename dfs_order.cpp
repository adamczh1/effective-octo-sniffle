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
vector<int> t_parent;
vector<int> t_ord;

template<typename T>
void wtree_getorder(const vector<vector<pair<int, T> > > &gw, int root, vector<T> &t_weight) {
	int n = (int)gw.size();
	t_parent.assign(n, -1);
	t_ord.clear();
	t_weight.assign(n, T());

	vector<int> stk; stk.push_back(root);
	while (!stk.empty()) {
		int i = stk.back(); stk.pop_back();
		t_ord.push_back(i);
		for (int j = (int)gw[i].size() - 1; j >= 0; j --) {
			int c = gw[i][j].first;
			if (t_parent[c] == -1 && c != root) {
				t_parent[c] = i;
				t_weight[c] = gw[i][j].second;
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
