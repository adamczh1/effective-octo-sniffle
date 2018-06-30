void insert(data c,int x,int l,int r){
	int mid=l+r>>1;
	bool initially_lower=f(c,N)<f(t[x],N);
	if(f(c,mid)<f(t[x],mid)){
		swap(t[x],c);
		if(l==r) return;
		if(initially_lower){
			insert(c,2*x,l,mid);
		}
		else{
			insert(c,2*x+1,mid+1,r);
		}
	}
	else{
		if(l==r) return;
		if(initially_lower){
			insert(c,2*x+1,mid+1,r);
		}
		else{
			insert(c,2*x,l,mid);
		}
	}
}
 
data query(int x,int l,int r,ll pos){
	if(l==r) return t[x];
	int mid=l+r>>1;
	if(pos<=mid){
		data tmp=query(2*x,l,mid,pos);
		if(f(tmp,pos)<f(t[x],pos)) return tmp;
		return t[x];
	}
	data tmp=query(2*x+1,mid+1,r,pos);
	if(f(tmp,pos)<f(t[x],pos)) return tmp;
	return t[x];
}
