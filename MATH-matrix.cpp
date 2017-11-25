const int MAX=105;
const int P=1e9+7;
int add(int a,int b){
	return (a+b)%P;
}
int mul(int a,int b){
	return (1ll*a*b)%P;
}
struct mat{
	int n,m;
	int a[MAX][MAX];
	mat(int _n,int _m){
		memset(a,0,sizeof a);
		n=_n,m=_m;
	}
	int* operator[](int x){
		return a[x];
	}
	const int* operator[](int x)const{
		return a[x];
	}
	mat operator+(const mat& o){
		assert((n==o.n)&&(m==o.m));
		mat res(n,m);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				res[i][j]=add(a[i][j],o[i][j]);
			}
		}
		return res;
	}
	mat operator*(const mat& o){
		assert(m==o.n);
		mat res(n,o.m);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)for(int k=0;k<o.m;k++){
				res[i][k]=add(res[i][k],mul(a[i][j],o[j][k]));
			}
		}
		return res;
	}
	mat exp(ll p){
		assert(n==m);
		mat res(n,n),tmp=*this;
		for(int i=0;i<n;i++){
			res[i][i]=1;
		}
		for(;p;p>>=1){
			if(p&1)res=res*tmp;
			tmp=tmp*tmp;
		}
		return res;
	}
	void print(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cerr<<a[i][j]<<' ';
			}
			cerr<<endl;
		}
		cerr<<endl;
	}
};
