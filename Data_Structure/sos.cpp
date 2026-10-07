for (int i = 0; i < n; i++) {
    s[1 << i] = a[i];
}
for (int i = 0; i < n; i++) {
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & (1 << i))) {
            s[mask | (1 << i)] += s[mask];
        }
    }
}