mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<int> r(1,n);
int x=r(rng);
