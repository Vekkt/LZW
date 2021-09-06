#include "LZW.h"
#include "LZWOutputStream.h"
#include "LZWInputStream.h"

void LZW::compress(std::istream& in, std::ostream& out) {
    LZWOutputStream cmpr{out};
    char* memblock = new char[1];
    while (in.read(memblock, sizeof(char)))
        cmpr.write(*memblock);
}

void LZW::decompress(std::istream& in, std::ostream& out) {
    LZWInputStream cmpr{in};
    while (int c = cmpr.read())
        out.put(static_cast<char>(c));
}
