#ifndef LZW_LZW_H
#define LZW_LZW_H

#include <iostream>

class LZW {
public:
    static void compress(std::istream&, std::ostream&);
    static void decompress(std::istream&, std::ostream&);
};


#endif //LZW_LZW_H
