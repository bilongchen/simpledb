#include <string>
#include <vector>

namespace simpledb {

class Page {
public:
    Page(int blocksize);

    Page(const std::vector<char> &byte_buffer);

    int get_int(const int offset) const;

    void set_int(const int offset, const int n);

    std::vector<char> get_bytes(const int offset) const;

    void set_bytes(const int offset, const std::vector<char> &byte_buffer);

    std::string get_string(const int offset) const;

    void set_string(const int offset, std::string s);

    int max_length(int strlen);

    // needed by FileManager class
    std::vector<char> contents();

private:
    std::vector<char> bb;
};
}
