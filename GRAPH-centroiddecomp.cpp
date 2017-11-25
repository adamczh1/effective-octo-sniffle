vector<pii>G[MAXN];
bool iscen[MAXN];
int subsz[MAXN];
int n,k,ans;
void init(){
    memset(iscen,0,sizeof iscen);
    memset(subsz,0,sizeof subsz);
    ans=0;
    for(int i=0;i<MAXN;i++)G[i].clear();
}
void add_edge(int a,int b,int c){
    G[a].push_back(make_pair(b,c));
    G[b].push_back(make_pair(a,c));
}

int calc_subsz(int cur,int p){
    subsz[cur]=1;
    for(pii e:G[cur]){
        int v=e.first;
        if(v==p||iscen[v])continue;
        subsz[cur]+=calc_subsz(v,cur);
    }
    return subsz[cur];
}
int search_cen(int cur,int p,int t){
    for(pii e:G[cur]){
        int v=e.first;
        if(v==p||iscen[v])continue;
        if(subsz[v]>t/2)return search_cen(v,cur,t);
    }
    return cur;
}
void work(int cur);
void solve_subproblem(int cur){
    calc_subsz(cur,-1);
    int cen=search_cen(cur,-1,subsz[cur]);
    iscen[cen]=1;
    for(pii e:G[cen]){
        int v=e.first;
        if(iscen[v])continue;
        solve_subproblem(v);
    }
    work(cen);
    iscen[cen]=0;
}

void calc_lens(vector<int>&A,int cur,int p,int d){
    A.push_back(d);
    for(pii e:G[cur]){
        int v=e.first;
        int w=e.second;
        if(v==p||iscen[v])continue;
        calc_lens(A,v,cur,d+w);
    }
}
int enumerate(vector<int>&A){
    sort(A.begin(),A.end());
    int sz=A.size();
    int res=0;
    for(int l=0,r=sz-1;l<r;){
        if(A[l]+A[r]<=k)res+=r-l,l++;
        else r--;
    }
    return res;
}
void work(int cur){
    // paths passing through centroid
    vector<int>lens;
    lens.push_back(0);
    for(int i=0;i<(int)G[cur].size();i++){
        pii e=G[cur][i];
        int v=e.first;
        int w=e.second;
        if(iscen[v])continue;
        vector<int>sub_lens;
        calc_lens(sub_lens,v,cur,w);
        ans-=enumerate(sub_lens);
        for(int j=0;j<(int)sub_lens.size();j++){
            lens.push_back(sub_lens[j]);
        }
    }
    ans+=enumerate(lens);
}
