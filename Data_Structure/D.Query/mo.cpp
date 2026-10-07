long long hiberord(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow ? (y < hpow ? 0 : 3) : (y < hpow ? 1 : 2));
    seg = (seg + rotate) & 3;
    int nx = x & (x ^ hpow);
    int ny = y & (y ^ hpow);
    static int delta[4] = {3, 0, 0, 1};
    int nrot = (rotate + delta[seg]) & 3;
    long long subSquare = 1LL << (2 * pow - 2);
    long long ans = seg * subSquare;
    long long add = hiberord(nx, ny, pow - 1, nrot);
    if (seg == 1 || seg == 2) ans += add;
    else ans += subSquare - add - 1;
    return ans;
}
struct Query{
    int l, r, id;
    long long ord;
    Query(){}
    Query(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {
        ord = hiberord(l, r, 21, 0);
    }
    bool operator < (const Query &other){
        return ord < other.ord;
    }
};

/*
    int l = 1, r = 0
    for (const &qr : q) {
        while (r < qr.r) add(++r);
        while (l < qr.l) remove(l++)
        while (l > qr.l) add(--l)
        while (r > qr.r) remove(r--)
    }

*/