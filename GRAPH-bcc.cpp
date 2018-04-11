void dfs(int cur,int p=-1){
	dfn[cur]=low[cur]=++Time;
	int ch=0;
	for(int v:g[cur])if(v!=p){
		if(!dfn[v]){
			ch++;
			stk.emplace_back(cur,v);
			dfs(v,cur);
			low[cur]=min(low[cur],low[v]);
			if(low[v]>=dfn[cur]){
				if(p==-1 && ch>1) art[cur]=1;
				if(p!=-1) art[cur]=1;
				vector<pii> li;
				while(stk.back()!=pii(cur,v)){
					li.push_back(stk.back());
					stk.pop_back();
				}
				li.push_back(stk.back());
				stk.pop_back();
				bcc.push_back(li);
			}
		}
		else if(dfn[v]<dfn[cur]){
			low[cur]=min(low[cur],dfn[v]);
			stk.emplace_back(cur,v);
		}
	}
}
