// better implementation in the making

#include <bits/stdc++.h>
using namespace std;

struct node{
	int pri,key,sz,flip;
	node *lc,*rc;
};
typedef node* pnode;
int sz(pnode x){
	return x?x->sz:0;
}
void pull(pnode x){
	if(x)x->sz=sz(x->lc)+1+sz(x->rc);
}

void split(pnode x,pnode &l,pnode &r,int v){ // v goes to r
	if(!x) l=NULL,r=NULL;
	else if(x->key<v)
		split(x->rc,x->rc,r,v),l=x;
	else
		split(x->lc,l,x->lc,v),r=x;
	pull(x);
}

void merge(pnode &x,pnode l,pnode r){
	if(!l)x=r;
	else if(!r)x=l;
	else if(l->pri>r->pri)
		merge(l->rc,l->rc,r),x=l;
	else
		merge(r->lc,l,r->lc),x=r;
	pull(x);
}

pnode newnode(int v){
	pnode res=new node();
	res->pri=rand();
	res->key=v;
	res->sz=1;
	res->flip=0;
	res->lc=res->rc=NULL;
	return res;
}

bool exists(pnode x,int v){
	if(!x) return false;
	if(x->key==v) return true;
	if(x->key>v) return exists(x->lc,v);
	return exists(x->rc,v);
}

void insert(pnode &x,pnode item){
	if(!x) x=item;
	else if(x->pri<item->pri){
		split(x,item->lc,item->rc,item->key);
		x=item;
	}
	else{
		if(item->key>=x->key) insert(x->rc,item);
		else insert(x->lc,item);
	}
	pull(x);
}

void erase(pnode &x,int v){
	if(!x) return;
	else if(x->key==v){
		pnode tmp=x;
		merge(x,x->lc,x->rc);
		free(tmp);
	}
	else{
		if(x->key>v){
			erase(x->lc,v);
		}
		else erase(x->rc,v);
	}
	pull(x);
}

int kth(pnode x,int k){
	if(!x) return -1;
	if(k==sz(x->lc)+1) return x->key;
	if(sz(x->lc)>=k)
		return kth(x->lc,k);
	return kth(x->rc,k-1-sz(x->lc));
}

int countless(pnode &x,int v){
	pnode l,r;
	split(x,l,r,v);
	int res=sz(l);
	merge(x,l,r);
	return res;
}

pnode root;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int Q;
	cin>>Q;
	while(Q--){
		char c;
		cin>>c;
		int x;
		cin>>x;
		if(c=='I'){
			if(!exists(root,x))
				insert(root,newnode(x));
		}
		else if(c=='D'){
			erase(root,x);
		}
		else if(c=='K'){
			if(sz(root)>=x)
				cout<<kth(root,x)<<endl;
			else cout<<"invalid"<<endl;
		}
		else cout<<countless(root,x)<<endl;
	}
	return 0;
}
