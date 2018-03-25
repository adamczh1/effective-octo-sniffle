mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> r(0,n);
	int ran=r(rng);
