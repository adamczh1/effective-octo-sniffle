struct UnionFind {
	vector<int> data;
	void init(int n) { data.assign(n+1, -1); }
	bool unionSet(int x, int y) {
		x = root(x); y = root(y);
		if (x != y) {
			if (data[y] < data[x]) swap(x, y);
			data[x] += data[y]; data[y] = x;
		}
		return x != y;
	}
	bool findSet(int x, int y) { return root(x) == root(y); }
	int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
	int size(int x) { return -data[root(x)]; }
};
template<int SZ> struct DSU {
	int fa[SZ];
	void init(){ memset(fa,-1,sizeof fa); }
	int find(int x){ return fa[x]<0 ? x : fa[x]=find(fa[x]); }
	int size(int x){ return -fa[find(x)]; }
	void unite(int x,int y){
		x=find(x), y=find(y);
		if(x==y) return;
		if(size(y)>size(x)) swap(x,y);
		fa[x]+=fa[y];
		fa[y]=x;
	}
};
