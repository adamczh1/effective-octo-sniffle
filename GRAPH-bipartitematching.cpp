bool dfs(int cur){
	if(vis[cur]) return 0;
	vis[cur]=1;
	for(int v:g[cur]){
		if(match[v]==-1 || dfs(match[v])){
			match[cur]=v;
			match[v]=cur;
			return 1;
		}
	}
	return 0;
}
int bimatch(){
	memset(match,-1,sizeof match);
	int res=0;
	for(int i=1;i<=n;i++)if(match[i]==-1){
		memset(vis,0,sizeof vis);
		if(dfs(i))res++;;
	}
	return res;
}

struct bipartitematch{
    vector<int> G[MAXN];
    int n, m, match[MAXN], dist[MAXN];
    // n: number of nodes on left side, nodes are numbered 1 to n
    // m: number of nodes on right side, nodes are numbered n+1 to n+m
    bool bfs() {
        int i, u, v, len;
        queue< int > Q;
        for(i=1; i<=n; i++) {
            if(!match[i]) {
                dist[i] = 0;
                Q.push(i);
            }
            else dist[i] = INF;
        }
        dist[0] = INF;
        while(!Q.empty()) {
            u = Q.front(); Q.pop();
            if(u) {
                len = G[u].size();
                for(i=0; i<len; i++) {
                    v = G[u][i];
                    if(dist[match[v]]==INF) {
                        dist[match[v]] = dist[u] + 1;
                        Q.push(match[v]);
                    }
                }
            }
        }
        return (dist[0]!=INF);
    }

    bool dfs(int u) {
        int i, v, len;
        if(u) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==dist[u]+1) {
                    if(dfs(match[v])) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int hopcroft_karp() {
        memset(match,0,sizeof match);
        int matching = 0, i;
        while(bfs())
            for(i=1; i<=n; i++)
                if(!match[i] && dfs(i))
                    matching++;
        return matching;
    }
};
