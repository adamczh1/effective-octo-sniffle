struct flow{
    int N,S,T;
    int g[MAXN][MAXN],f[MAXN][MAXN];
    int vis[MAXN];
    void init(int n){
        N=n+2,S=n+1,T=n+2;
        memset(g,0,sizeof g);
        memset(f,0,sizeof f);
        memset(vis,0,sizeof vis);
    }
    int dfs(int s,int t,int c){
        vis[s]=1;
        if(s==t)return c;
        for(int i=1;i<=N;i++){
            int cap=g[s][i]-f[s][i];
            if(!vis[i] && cap>0){
                if(int sent=dfs(i,t,min(c,cap))){
                    f[s][i]+=sent;
                    f[i][s]-=sent;
                    return sent;
                }
            }
        }
        return 0;
    }
    int ff(){
        int res=0;
        while(int sent=dfs(S,T,INT_MAX)){
            res+=sent;
            memset(vis,0,sizeof vis);
        }
        return res;
    }
};
