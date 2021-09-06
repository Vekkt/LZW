#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <chrono>
#include "LZW.h"

struct SizeReader {
    std::uintmax_t size{};
private: friend
    std::ostream& operator<<(std::ostream& os, SizeReader sr) {
        int i{};
        auto mantissa = static_cast<double>(sr.size);
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B";
    }
};

double ratio(auto size1, auto size2) {
    return 100 * (1 - static_cast<double>(size1) / static_cast<double>(size2));
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Wrong number of arguments. Exiting." << std::endl;
        return 1;
    }

    std::string input_file_name{"./" + std::string{argv[1]}};
    std::string compr_file_name{"./" + std::string{argv[2]}};
    std::string output_file_name{"./" + std::string{argv[3]}};

    try {
        std::ifstream in{input_file_name};
        std::ofstream out{compr_file_name};

        std::cout << "Starting compression..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        LZW::compress(in, out);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "File compressed in: " << duration.count() / 1e6 << " seconds" << std::endl;

        auto original_size = std::filesystem::file_size(input_file_name);
        auto compress_size = std::filesystem::file_size(compr_file_name);
        std::cout << "Original file size: " << SizeReader{original_size} << std::endl;
        std::cout << "Compressed file size: " << SizeReader{compress_size} << std::endl;
        std::cout << "Compression ratio: " << ratio(compress_size, original_size) << "%" << std::endl;
    } catch(std::exception& e){
        std::cout << "Error encountered during compression. Exiting." << std::endl;
    }

    std::cout << "-----------------------" << std::endl;

    try {
        std::ifstream in{compr_file_name};
        std::ofstream out{output_file_name};

        auto start = std::chrono::high_resolution_clock::now();
        LZW::decompress(in, out);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "File decompressed in: " << duration.count() / 1e6 << " seconds" << std::endl;
    } catch(std::exception& e){
        std::cout << "Error encountered during decompression. Exiting." << std::endl;
    }

    return 0;
}
