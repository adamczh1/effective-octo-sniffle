struct ModInt {
	static int Mod;
	unsigned x;
	ModInt() : x(0) { }
	ModInt(signed sig) { int sigt = sig % Mod; if (sigt < 0) sigt += Mod; x = sigt; }
	ModInt(signed long long sig) { int sigt = sig % Mod; if (sigt < 0) sigt += Mod; x = sigt; }
	int get() const { return (int)x; }

	ModInt &operator+=(ModInt that) { if ((x += that.x) >= (unsigned)Mod) x -= Mod; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += Mod - that.x) >= (unsigned)Mod) x -= Mod; return *this; }
	ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % Mod; return *this; }
	ModInt &operator/=(ModInt that) { return *this *= that.inverse(); }

	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
	ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }

	ModInt inverse() const {
		signed a = x, b = Mod, u = 1, v = 0;
		while (b) {
			signed t = a / b;
			a -= t * b; std::swap(a, b);
			u -= t * v; std::swap(u, v);
		}
		if (u < 0) u += Mod;
		ModInt res; res.x = (unsigned)u;
		return res;
	}

	bool operator==(ModInt that) const { return x == that.x; }
	bool operator!=(ModInt that) const { return x != that.x; }
	ModInt operator-() const { ModInt t; t.x = x == 0 ? 0 : Mod - x; return t; }
};
int ModInt::Mod = 1000000007;
typedef ModInt mint;
mint operator^(mint a, unsigned long long k) {
	mint r = 1;
	while (k) {
		if (k & 1) r *= a;
		a *= a;
		k >>= 1;
	}
	return r;
}

vector<mint> fact, factinv;
void nCr_computeFactinv(int N) {
	N = min(N, mint::Mod - 1);
	fact.resize(N + 1); factinv.resize(N + 1);
	fact[0] = 1;
	rer(i, 1, N) fact[i] = fact[i - 1] * i;
	factinv[N] = fact[N].inverse();
	for (int i = N; i >= 1; i --) factinv[i - 1] = factinv[i] * i;
}
mint nCr(int n, int r) {
	if (n >= mint::Mod)
		return nCr(n % mint::Mod, r % mint::Mod) * nCr(n / mint::Mod, r / mint::Mod);
	return r > n ? 0 : fact[n] * factinv[n - r] * factinv[r];
}
