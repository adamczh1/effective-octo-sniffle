void strongconnect(const vector<vi> &g,int cur,int &t){
	num[cur]=low[cur]=++t;
	stk.push_back(cur);
	onstk[cur]=1;
	for(int v:g[cur]){
		if(!num[v]){
			strongconnect(g,v,t);
			low[cur]=min(low[cur],low[v]);
		}
		else if(onstk[v]){ // important
			low[cur]=min(low[cur],num[v]);
		}
	}
	if(low[cur]==num[cur]){
		int w;
		do{
			w=stk.back();
			stk.pop_back();
			onstk[w]=0;
			scc[w]=scccnt;
		}while(w!=cur);
		scccnt++;
	}
}
