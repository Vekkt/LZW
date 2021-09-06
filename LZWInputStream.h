#ifndef LZW_LZWINPUTSTREAM_H
#define LZW_LZWINPUTSTREAM_H

#include "BitsInputStream.h"
#include <deque>
#include <vector>

class LZWInputStream {
public:
    explicit LZWInputStream(std::istream&);
    int read();

    template<typename T>
    std::vector<T> copy_and_append_head(const std::vector<T> &v1, const std::vector<T> &v2);

private:
    BitsInputStream in;
    std::vector<std::vector<int>> dict;
    std::deque<int> current;
    std::vector<int> previous;

    static constexpr int MAX_DATA_SIZE{16};
    static constexpr int MAX_CAPACITY{1 << MAX_DATA_SIZE};

    template<typename T> T remove_and_return_first(std::deque<T> &queue);
};

#endif //LZW_LZWINPUTSTREAM_H
