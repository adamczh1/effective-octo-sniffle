#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;

int N, M;
vector<int> adj[MAXN];
int a[MAXN], b[MAXN];
int dfn[MAXN], low[MAXN];
bool art[MAXN];
vector<pii> stk;
vector<vector<pii> > bcc;
int Time;

void dfs(int cur, int p = -1) {
	dfn[cur] = low[cur] = ++Time;
	int ch = 0;
	for (int v : adj[cur]) if (v != p) {
		if (!dfn[v]) {
			stk.push_back({cur, v});
			dfs(v, cur);
			low[cur] = min(low[cur], low[v]);
			ch++;
			if (low[v] >= dfn[cur]) {
				if (p == -1 && ch > 1) art[cur] = true;
				if (p != -1) art[cur] = true;
				vector<pii> tmp;
				while (stk.back() != make_pair(cur, v)) {
					tmp.push_back(stk.back());
					stk.pop_back();
				}
				tmp.push_back(stk.back());
				stk.pop_back();
				bcc.push_back(tmp);
			}
		} else if (dfn[v] < dfn[cur]) {
			low[cur] = min(low[cur], dfn[v]);
			stk.push_back({cur, v});
		}
	}
}

int bct_sz;
int art_id[MAXN];
int bcc_id[MAXN];
set<int> bct[MAXN];

void build_bct() {
	for (int i = 1; i <= N; i++) {
		if (art[i]) {
			art_id[i] = ++bct_sz;
		}
	}
	int i = 0;
	for (const vector<pii> &tmp : bcc) {
		bcc_id[i++] = ++bct_sz;
		for (const pii &p : tmp) {
			if (art[p.first]) {
				bct[bct_sz].insert(art_id[p.first]);
				bct[art_id[p.first]].insert(bct_sz);
			}
			if (art[p.second]) {
				bct[bct_sz].insert(art_id[p.second]);
				bct[art_id[p.second]].insert(bct_sz);
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &a[i], &b[i]);
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}
	dfs(1);
	build_bct();
	int leafcnt = 0;
	for (int i = 1; i <= bct_sz; i++) {
		if (bct[i].size() == 1) {
			leafcnt++;
		}
	}
	printf("%d\n", (leafcnt + 1) / 2);
	return 0;
}
