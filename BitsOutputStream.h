#ifndef LZW_BITSOUTPUTSTREAM_H
#define LZW_BITSOUTPUTSTREAM_H

#include <iostream>

class BitsOutputStream {
public:
    explicit BitsOutputStream(std::ostream&);
    ~BitsOutputStream();
    void write(int, int);

private:
    std::ostream& out;
    int waitingBits;
    int waitingCount;

    static constexpr int MIN_READ_SIZE{0};
    static constexpr int MAX_READ_SIZE{16};
    static constexpr int DATA_SIZE{8};
};

#endif //LZW_BITSOUTPUTSTREAM_H
