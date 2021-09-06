#include "BitsInputStream.h"

BitsInputStream::BitsInputStream(std::istream& is):
    in{is}, waitingBits{0}, waitingCount{0} {
}

[[nodiscard]] int BitsInputStream::read(int size) {
    if (!(MIN_READ_SIZE <= size && size <= MAX_READ_SIZE))
        throw std::invalid_argument{"Illegal read size: must be at most 16 bits."};

    while (waitingCount < size) {
        const auto data = in.get();
        if (data == EOF)
            return EOF;
        waitingBits = (waitingBits << DATA_SIZE) | data;
        waitingCount += 8;
    }

    waitingCount -= size;
    return (waitingBits >> waitingCount) & MASKS[size];
}

