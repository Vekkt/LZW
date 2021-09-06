#ifndef LZW_BITSINPUTSTREAM_H
#define LZW_BITSINPUTSTREAM_H

#include <iostream>

class BitsInputStream {
public:
    explicit BitsInputStream(std::istream&);
    int read(int);

private:
    std::istream& in;
    int waitingBits;
    int waitingCount;

    static constexpr int MIN_READ_SIZE{0};
    static constexpr int MAX_READ_SIZE{16};
    static constexpr int DATA_SIZE{8};
    static constexpr int MASKS[]{
        0x0000, 0x0001, 0x0003, 0x0007,
        0x000F, 0x001F, 0x003F, 0x007F,
        0x00FF, 0x01FF, 0x03FF, 0x07FF,
        0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF,
        0xFFFF
    };
};

#endif //LZW_BITSINPUTSTREAM_H