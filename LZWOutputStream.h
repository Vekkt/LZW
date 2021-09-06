#ifndef LZW_LZWOUTPUTSTREAM_H
#define LZW_LZWOUTPUTSTREAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "BitsOutputStream.h"

struct VectorHash {
    auto operator()(const std::vector<int>& v) const {
        auto hash = v.size();
        for(auto &i : v) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

class LZWOutputStream {
public:
    explicit LZWOutputStream(std::ostream&);
    ~LZWOutputStream();
    void write(int data);
    void write_index(int data);

private:
    BitsOutputStream out;
    std::vector<int> prefix;
    std::unordered_map<std::vector<int>, int, VectorHash> dict;

    static constexpr int MAX_DATA_SIZE{16};
    static constexpr int MAX_CAPACITY{1 << MAX_DATA_SIZE};
};

inline int clz(int x) {
    int n = 0;
    if (x == 0) return sizeof(x) * 8;
    while (true) {
        if (x <= 0) break;
        n ++;
        x <<= 1;
    }
    return n;
}

#endif //LZW_LZWOUTPUTSTREAM_H
