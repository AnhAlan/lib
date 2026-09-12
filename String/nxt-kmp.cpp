template<typename T>
vector<vector<int>> nxt(const T &s, const vector<int> &kmp_s) {
    int n = (int) s.size() - 1;
    vector<vector<int>> res(n + 1, vector<int>(26));
    for (int c = 0; c < 26; c++) {
        res[0][c] = (n >= 1 && s[1] == char(c + 'a')) ? 1 : 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i < n && s[i + 1] == char(c + 'a')) {
                res[i][c] = i + 1;
            } else {
                res[i][c] = res[kmp_s[i]][c];  
            }
        }
    }
    return res;
}