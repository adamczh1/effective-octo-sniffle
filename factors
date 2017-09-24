vector<bool> isprime;
vector<int> primes;
void sieve(int n) {
	if ((int)isprime.size() >= n + 1) return;
	isprime.assign(n + 1, true);
	isprime[0] = isprime[1] = false;
	int sqrtn = (int)(sqrt(n * 1.) + .5);
	for (int i = 2; i <= sqrtn; i ++) if (isprime[i]) {
		for (int j = i * i; j <= n; j += i)
			isprime[j] = false;
	}
	primes.clear();
	for (int i = 2; i <= n; i ++) if (isprime[i])
		primes.push_back(i);
}

typedef int FactorsInt;
typedef vector<pair<FactorsInt, int> > Factors;
void primeFactors(FactorsInt x, Factors &out_v) {
	out_v.clear();
	int sqrtx = (int)(sqrt(x*1.) + 10.5);
	sieve(sqrtx);
	for (vector<int>::const_iterator p = primes.begin(); p != primes.end(); ++ p) {
		if (*p > sqrtx) break;
		if (x % *p == 0) {
			int t = 1;
			x /= *p;
			while (x % *p == 0) {
				t ++;
				x /= *p;
			}
			out_v.push_back(make_pair(*p, t));
		}
	}
	if (x != 1) out_v.push_back(make_pair(x, 1));
}
