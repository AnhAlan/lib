vector<int> mobius(int n) {
    vector<int> res(n + 1, 0);
    res[1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i * 2; j <= n; j += i) {
            res[j] -= res[i];
        }
    }
    return res;
}