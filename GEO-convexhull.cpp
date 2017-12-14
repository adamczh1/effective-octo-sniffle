ll cross(pii O, pii A, pii B){
    return 1ll*(A.first-O.first)*(B.second-O.second) - 1ll*(A.second-O.second)*(B.first-O.first);
}
vector<pii> convex_hull(vector<pii> P) {
    int n=SIZE(P), k=0;
    if (n==1) return P;
    vector<pii> H(2*n);
    sort(P.begin(),P.end());
    for(int i=0;i<n;i++){
        while(k>=2 && cross(H[k-2],H[k-1],P[i])<=0) k--;
        H[k++]=P[i];
    }
    for(int i=n-2,t=k+1;i>=0;i--){
        while(k>=t && cross(H[k-2],H[k-1],P[i])<=0) k--;
        H[k++]=P[i];
    }
    H.resize(k-1);
    return H;
}
