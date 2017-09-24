struct FenwickTree {
	vector<ll> v;
	void init(int n) { v.assign(n + 1, 0); }
	void add(int i, ll x) {
		for (; i<SIZE(v); i += i & -i) v[i] += x;
	}
	ll sum(int i) const { // [1, i]
		ll r = 0;
		for (; i > 0; i -= i & -i) r += v[i];
		return r;
	}
	ll sum(int left, int right) const { // [left, right]
		return sum(right) - sum(left - 1);
	}
};
