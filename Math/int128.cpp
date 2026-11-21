__int128 string_to_i128(const string &s) {
    __int128 res = 0;
    bool negative = false;
    int i = 0;
    if (s[0] == '-') {
        negative = true;
        i = 1;
    }
    for (; i < (int)s.size(); i++) {
        res = res * 10 + (s[i] - '0');
    }
    return negative ? -res : res;
}
string print_int128(__int128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        s += char('0' + x % 10);
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
}