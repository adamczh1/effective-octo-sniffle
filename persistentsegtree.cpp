struct persistent_segment_tree{
	int tree_deg;
	int root[MAXN];
	struct tree_node{
		int lc,rc;
		int val;
	}t[10001000];
	void modify(int &x,int k,int l,int r,int pos,int v){
		t[x=++tree_deg]=t[k];
		if (l==r){
			t[x].val=v;
			return;
		}
		int mid=l+r>>1;
		if (pos<=mid) modify(t[x].lc,t[k].lc,l,mid,pos,v);
		else modify(t[x].rc,t[k].rc,mid+1,r,pos,v);
		t[x].val=t[t[x].lc].val+t[t[x].rc].val;
	}
	int query(int x,int l,int r,int ql,int qr){
		if(l>qr||r<ql||l>r)return 0;
		if(ql<=l&&r<=qr)return t[x].val;
		int mid=l+r>>1;
		return query(t[x].lc,l,mid,ql,qr)+query(t[x].rc,mid+1,r,ql,qr);
	}
};
