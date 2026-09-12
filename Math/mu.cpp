vector<int> mu(int n) {
    vector<int> res(n + 1);
    vector<bool> is_composite(n + 1, false);
    vector<int> primes;
    res[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            res[i] = -1;
        }
        for (const int &p : primes) {
            if (1ll * p * i > n) break;
            is_composite[p * i] = true;
            if (i % p == 0) {
                res[p * i] = 0;
                break;
            }
            res[p * i] = -res[i];
        }
    }
    return res;
}