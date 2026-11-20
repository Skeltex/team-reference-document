// Линейное решето: O(n), считает lp, primes и mu[1..n].
vi lp, primes, mu;
void sieve_mobius(int n) {
    lp.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (p > lp[i] || (li)i * p > n) break;
            lp[i * p] = p;
            mu[i * p] = (p == lp[i]) ? 0 : -mu[i];
        }
    }
}
