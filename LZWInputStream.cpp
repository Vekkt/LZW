#include "LZWInputStream.h"
#include "LZWOutputStream.h"

using std::vector;

LZWInputStream::LZWInputStream(std::istream& is):
    in{is}, dict{}, current{}, previous{} {
    for (int i = 0; i <= 0xFF; ++i) {
        dict.push_back(vector{i});
    }
}

[[nodiscard]] int LZWInputStream::read() { // intellij wrongly infers the return value
    if (current.empty()) {
        const auto add_entry = dict.size() < MAX_CAPACITY && !previous.empty();
        const auto future_size = dict.size() + (add_entry ? 1 : 0);
        const auto bits = 32 - clz(static_cast<int>(future_size) - 1);
        const auto i = in.read(bits);

        if (i == EOF)
            return 0;

        const auto word = i < dict.size()
                ? dict.at(i)
                : copy_and_append_head(previous, previous);

        if (add_entry)
            dict.push_back(copy_and_append_head(previous, word));

        current.insert(current.end(), word.begin(), word.end());
        previous = word;
    }
    return remove_and_return_first(current);
}

template<typename T>
[[nodiscard]] vector<T> LZWInputStream::copy_and_append_head(const vector<T> &v1, const vector<T> &v2) {
    vector<T> r{v1};
    r.push_back(v2.front());
    return r;
}

template<typename T>
[[nodiscard]] T LZWInputStream::remove_and_return_first(std::deque<T>& queue) {
    auto res = queue.front();
    queue.pop_front();
    return res;
}


