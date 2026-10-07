map<int, int> mp;
for (int i = 0; i < n; i++) {
    cin >> a[i];
    mp[a[i]]++;
}
vector<int> optimize;
for (auto [v, cnt] : mp) {
    int k = 1;
    while (cnt >= k) {
        optimize.push_back(v * k);
        cnt -= k;
        k *= 2;
    }
    if (cnt > 0) {
        optimize.push_back(v * cnt);
    }
}
bitset<MAX_SUM + 1> bs;
bs[0] = 1;
for (int x : optimize) {
    if (x <= MAX_SUM) {
        bs |= (bs << x);
    }
}