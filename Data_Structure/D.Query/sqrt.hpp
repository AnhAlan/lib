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
/*
    int currL = 0, currR = -1; // empty window [currL, currR]
    for (const auto &qu : queries) {
        // expand first, then shrink, so the window never has negative size
        while (currL > qu.l) add(--currL);
        while (currR < qu.r) add(++currR);
        while (currL < qu.l) del(currL++);
        while (currR > qu.r) del(currR--);
        ans[qu.idx] = currSum;
    }
*/
