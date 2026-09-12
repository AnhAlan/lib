int euclid(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int inv(int b, int P) {
    int x1 = 0, y1 = 0;
    int g = euclid(b, P, x1, y1);
    assert(g == 1);
    x1 %= P;
    if (x1 < 0) x1 += P;
    return x1;
}