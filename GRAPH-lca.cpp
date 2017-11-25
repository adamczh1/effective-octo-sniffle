vector<int>adj[MAXN];
int dep[MAXN];
int par[20][MAXN];
void dfs(int cur,int p=1){
    dep[cur]=(cur==1?0:dep[p]+1);
    par[0][cur]=p;
    for(int i=1;i<20;i++)par[i][cur]=par[i-1][par[i-1][cur]];
    for(int v:adj[cur]){
        if(v==p)continue;
        dfs(v,cur);
    }
}
int lca(int u,int v){
    if(dep[u]>dep[v])swap(u,v);
    for(int i=19;i>=0;i--){
        if(dep[par[i][v]] >=dep[u]){
            v=par[i][v];
        }
    }
    if(u==v)return u;
    for(int i=19;i>=0;i--){
        if(par[i][u]!=par[i][v]){
            u=par[i][u];
            v=par[i][v];
        }
    }
    return par[0][u];
}
int dist(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
}
