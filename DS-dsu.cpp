template<int SZ> struct DSU {
	int fa[SZ];
	void init() {
		memset(fa, -1, sizeof fa);
	}
	int find(int x) {
		return fa[x] < 0 ? x : fa[x] = find(fa[x]);
	}
	int size(int x) {
		return -fa[find(x)];
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (size(x) > size(y)) {
			swap(x, y);
		}
		fa[y] += fa[x];
		fa[x] = y;
	}
};
