#include "BitsOutputStream.h"
#include <string>

BitsOutputStream::BitsOutputStream(std::ostream& os):
    out{os}, waitingBits{0}, waitingCount{0} {
}


BitsOutputStream::~BitsOutputStream() {
    if (waitingCount > 0) {
        out.put(static_cast<char>(waitingBits << (DATA_SIZE - waitingCount)));
        waitingCount = 0;
    }
    out.flush();
}


void BitsOutputStream::write(int data, int size) {
    if (!(MIN_READ_SIZE <= size && size <= MAX_READ_SIZE))
        throw std::invalid_argument{"Illegal data size: must be at most 16 bits."};
    if (!(0 <= data && data < (1 << size)))
        throw std::invalid_argument{"Not enough data for the given size."};

    waitingBits = (waitingBits << size) | data;
    waitingCount += size;

    while (waitingCount >= DATA_SIZE) {
        out.put(static_cast<char>(waitingBits >> (waitingCount - DATA_SIZE)));
        waitingCount -= DATA_SIZE;
    }
}

