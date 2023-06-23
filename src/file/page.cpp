#include "file/page.h"
#include <algorithm>
#include <iterator>

namespace simpledb {

Page::Page(int blocksize) {
    bb.reserve(blocksize);
}

Page::Page(const std::vector<char>& byte_buffer) {
    copy(byte_buffer.begin(), byte_buffer.end(), back_inserter(bb));
}

int Page::get_int(const int offset) const {
    assert(offset + sizeof(int) < bb.size());

    int result = 0;
    for (unsigned long i = 0; i < sizeof(int); i++) {
        result = (result << (8*i)) + bb[i+offset];
    }

    return result;
}

void Page::set_int(const int offset, const int n) {
    assert(offset + sizeof(int) < bb.size());

    int mask = 0xff;
    for (unsigned long i = 0; i < sizeof(int); i++) {
        bb[offset+i] = (n & mask) >> (8*i);
        mask = mask << (8*i); 
    }
}

std::vector<char> Page::get_bytes(const int offset) const {
    int length = get_int(offset);
    assert(length + offset + sizeof(int) <= bb.size());
    std::vector<char> results;
    copy(bb.begin() + offset + sizeof(int), bb.end(), back_inserter(results));
    return results;
}

void Page::set_bytes(const int offset, const std::vector<char> &byte_buffer) {
    assert(byte_buffer.size() + sizeof(int) + offset <= bb.size());
    set_int(offset, byte_buffer.size());
    copy(byte_buffer.begin(), byte_buffer.end(), bb.begin() + offset + sizeof(int));
}

std::string Page::get_string(const int offset) const {
    assert(offset < (int)bb.size());
    std::string result(bb.begin(), bb.end());
    return result;
}

void Page::set_string(const int offset, const std::string s) {
    std::vector<char> v(s.begin(), s.end());
    set_bytes(offset, v);
}

std::vector<char> Page::contents() {
    return bb;
}

}