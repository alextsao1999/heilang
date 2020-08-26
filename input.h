//
// Created by Alex on 8/26/2020.
//

#ifndef HEILANG_INPUT_H
#define HEILANG_INPUT_H
#include <fstream>
class StreamIter {
    std::istream *stream = nullptr;
    int chr = 0;
public:
    using iterator_category = typename std::input_iterator_tag;
    using value_type = char;
    using difference_type = long;
    using pointer = const char *;
    using reference = char &;
    constexpr StreamIter() = default;
    StreamIter(std::istream &os) : stream(&os) {
        ++*this;
    }
    inline bool empty() const { return stream == nullptr; }
    inline bool eof() const { return  !stream || (stream && stream->eof()); }
    inline const int operator*() const { return chr; }
    inline StreamIter&operator++() {
        chr = (!empty()) ? stream->get() : 0;
        return *this;
    }
    inline bool operator==(const StreamIter &rhs) {
        return rhs.empty() && eof();
    }
    inline bool operator!=(const StreamIter &rhs) {
        return !(*this == rhs);
    }
};
class FileStreamWrapper {
private:
    std::fstream file;
public:
    FileStreamWrapper(const char *path) {
        file.open(path, std::ios::in);
    }
    ~FileStreamWrapper() {
        if (file.is_open()) {
            file.close();
        }
    }
    StreamIter begin() {
        return StreamIter(this->file);
    }
    StreamIter end() { return StreamIter(); }
};
template<class char_t = char>
class StringIter {
    const char_t *current = nullptr;
public:
    using iterator_category = typename std::input_iterator_tag;
    using value_type = char_t;
    using difference_type = long;
    using pointer = const char_t *;
    using reference = char_t &;
    constexpr StringIter() = default;
    constexpr StringIter(const char_t *current) : current(current) {}
    inline bool empty() const { return current == nullptr; }
    inline const char operator*() const { return current ? *current : 0; }
    inline StringIter&operator++() {
        current++;
        return *this;
    }
    inline bool operator==(const StringIter &rhs) {
        return rhs.empty() && **this == '\0';
    }
    inline bool operator!=(const StringIter &rhs) {
        return !(*this == rhs);
    }
};

#endif //HEILANG_INPUT_H
