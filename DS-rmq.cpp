struct RMQ {
	int t[2*MAXN];
	void init(){
		memset(t,63,sizeof t);
	}
	void modify(int p,int v){
		for(t[p+=MAXN]=v;p>1;p>>=1){
			t[p>>1]=min(t[p],t[p^1]);
		}
	}
	int query(int l,int r){
		int res=INT_MAX;
		for(l+=MAXN,r+=MAXN+1;l<r;l>>=1,r>>=1){
			if(l&1) res=min(res,t[l++]);
			if(r&1) res=min(res,t[--r]);
		}
		return res;
	}
};
