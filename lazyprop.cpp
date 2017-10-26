struct segtree {
    ll t[4*MAXN],lazy[4*MAXN];
    void build(int x,int l,int r){
        if(l==r)t[x]=a[l];
        else{
            int mid=(l+r)/2;
            build(2*x,l,mid);
            build(2*x+1,mid+1,r);
            t[x]=t[2*x]+t[2*x+1];
        }
    }
    void prop(int x,int l,int r){
        t[x]+=lazy[x]*(r-l+1);
        if(l!=r){
            lazy[2*x]+=lazy[x];
            lazy[2*x+1]+=lazy[x];
        }
        lazy[x]=0;
    }
    void update(int x,int l,int r,int a,int b,ll v){
        prop(x,l,r);
        if(l>r||r<a||b<l)return;
        if(a<=l&&r<=b){
            lazy[x]+=v;
            prop(x,l,r);
            return;
        }
        int mid=(l+r)/2;
        update(2*x,l,mid,a,b,v);
        update(2*x+1,mid+1,r,a,b,v);
        t[x]=t[2*x]+t[2*x+1];
    }
    ll query(int x,int l,int r,int a,int b){
        prop(x,l,r);
        if(l>r||r<a||b<l)return 0;
        if(a<=l&&r<=b){
            return t[x];
        }
        prop(x,l,r);
        int mid=(l+r)/2;
        ll res=query(2*x,l,mid,a,b)+query(2*x+1,mid+1,r,a,b);
        return res;
    }
    void update(int a,int b,ll v){
        update(1,1,MAXN,a,b,v);
    }
    ll query(int a,int b){
        return query(1,1,MAXN,a,b);
    }
};
