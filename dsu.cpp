struct dsu{
    int par[MAXN];
    void init(){
        for(int i=0;i<MAXN;i++)par[i]=i;
    }
    int find(int v){
        return par[v]<0?v:(par[v]=find(par[v]));
    }
    void merge(int a,b){
        if((a=find(a))==(b=find(b)))return;
        if(par[y]<par[x])swap(x,y);
        par[x]+=par[y];
        par[y]=x;
    }
};
