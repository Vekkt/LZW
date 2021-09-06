#include "LZWOutputStream.h"
#include <unordered_map>
#include <utility>

LZWOutputStream::LZWOutputStream(std::ostream& os):
    out{os}, prefix{}, dict{MAX_CAPACITY} {
    for (int i = 0; i <= 0xFF; ++i)
        dict.emplace(std::vector{i}, i);
}

LZWOutputStream::~LZWOutputStream() {
    if (!prefix.empty()) {
        write_index(dict.at(prefix));
        prefix.clear();
    }
}

void LZWOutputStream::write(int data) {
    prefix.push_back(data & 0xFF);

    if (dict.find(prefix) != dict.end()) // find: main overhead overall
        return;

    const auto trimmed_prefix = std::vector<int>{prefix.begin(), prefix.end() - 1};
    write_index(dict.at(trimmed_prefix));

    if (dict.size() < MAX_CAPACITY)
        dict.emplace(std::pair{prefix, dict.size()});

    prefix.erase(prefix.begin(), prefix.end()-1);
}

void LZWOutputStream::write_index(int data) {
    out.write(data, 32 - clz(static_cast<int>(dict.size())-1));
}
