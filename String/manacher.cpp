void manacher(const string &s, vector<int> &d1, vector<int> &d2) {
    int n = (int) s.size() - 1;
    d1.assign(n + 1, 0);
    d2.assign(n + 1, 0);
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
        while (i - k >= 1 && i + k <= n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
        while (i - k - 1 >= 1 && i + k <= n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}