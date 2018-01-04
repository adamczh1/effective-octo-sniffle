#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define SIZE(x) (int)(x).size()
#define ff first
#define ss second

inline ll readi(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN=1e6+5;

struct node{
	int max, snd, cnt; // max val, 2nd max val, cnt of max val
	ll sum;
};

int n,m;
int a[MAXN];
node tree[4*MAXN];

void push(int x){
	int mx=tree[x].max;
	if(tree[x<<1].max > mx){
		tree[x<<1].sum += 1ll*(mx-tree[x<<1].max)*tree[x<<1].cnt;
		tree[x<<1].max = mx;
	}
	if(tree[x<<1|1].max > mx){
		tree[x<<1|1].sum += 1ll*(mx-tree[x<<1|1].max)*tree[x<<1|1].cnt;
		tree[x<<1|1].max = mx;
	}
}

void pull(int x){
	tree[x].sum = tree[x<<1].sum + tree[x<<1|1].sum;
	tree[x].max = max(tree[x<<1].max, tree[x<<1|1].max);
	tree[x].snd = max(tree[x<<1].snd, tree[x<<1|1].snd);
	if(tree[x<<1].max < tree[x<<1|1].max){
		tree[x].snd = max(tree[x].snd, tree[x<<1].max);
	}
	if(tree[x<<1].max > tree[x<<1|1].max){
		tree[x].snd = max(tree[x].snd, tree[x<<1|1].max);
	}
	tree[x].cnt=0;
	if(tree[x].max == tree[x<<1].max){
		tree[x].cnt += tree[x<<1].cnt;
	}
	if(tree[x].max == tree[x<<1|1].max){
		tree[x].cnt += tree[x<<1|1].cnt;
	}
}

void build(int x,int l,int r){
	if(l==r){
		tree[x]={a[l],-1,1,a[l]};
	}
	else{
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pull(x);
	}
}

void update(int x,int l,int r,int ql,int qr,int v){
	if(qr<l || r<ql || tree[x].max<=v){
		return;
	}
	if(ql<=l && r<=qr && tree[x].snd<v){
		tree[x].sum += 1ll*(v-tree[x].max)*tree[x].cnt;
		tree[x].max = v;
		return;
	}
	push(x);
	int mid=l+r>>1;
	update(x<<1,l,mid,ql,qr,v);
	update(x<<1|1,mid+1,r,ql,qr,v);
	pull(x);
}

int getmax(int x,int l,int r,int ql,int qr){
	if(qr<l || r<ql){
		return 0;
	}
	if(ql<=l && r<=qr){
		return tree[x].max;
	}
	push(x);
	int mid=l+r>>1;
	return max(getmax(x<<1,l,mid,ql,qr), getmax(x<<1|1,mid+1,r,ql,qr));
}

ll getsum(int x,int l,int r,int ql,int qr){
	if(qr<l || r<ql){
		return 0;
	}
	if(ql<=l && r<=qr){
		return tree[x].sum;
	}
	push(x);
	int mid=l+r>>1;
	return getsum(x<<1,l,mid,ql,qr)+getsum(x<<1|1,mid+1,r,ql,qr);
}

int main(){
	int T=readi();
	while(T--){
		n=readi(),m=readi();
		for(int i=1; i<=n; i++){
			a[i]=readi();
		}
		build(1,1,n);
		while(m--){
			int op=readi(),x=readi(),y=readi();
			if(op==0){
				int t=readi();
				update(1,1,n,x,y,t);
			}
			else if(op==1){
				printf("%d\n",getmax(1,1,n,x,y));
			}
			else{
				printf("%lld\n",getsum(1,1,n,x,y));
			}
		}
	}
	return 0;
}
