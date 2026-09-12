vector<int> phi_sieve(int n) {
    vector<int> res(n + 1);
    for (int i = 0; i <= n; i++) res[i] = i;
    for (int i = 2; i <= n; i++) {
        if (res[i] == i) {
            for (int j = i; j <= n; j += i ) {
                res[j] -= (res[j] / i);
            }
        }
    }
    return res;
}