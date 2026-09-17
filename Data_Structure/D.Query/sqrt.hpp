int block; // block = sqrt(n)
struct Query {
    int l, r, id;
    bool operator < (const Query &other) const {
        int block_a = l / block;
        int block_b = other.l / block;
        if (block_a != block_b) return block_a < block_b;
        if (block_a & 1) return r > other.r;
        return r < other.r;
    }
};
