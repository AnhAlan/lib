template<typename T, typename Y>
void add_mod(T &x, const Y &y) {
    x += y;
    if (x < 0) x += mod;
    if (x >= mod) x -= mod;
}
template<typename T, typename Y>
void sub_mod(T &x, const Y &y) {
    x -= y;
    if (x < 0) x += mod;
}
template<typename T, typename Y>
void mul_mod(T &x, const Y &y) {
    x = (int)(1ll * x * y % mod);
}