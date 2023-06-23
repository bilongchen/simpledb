#include <string>

namespace simpledb {

class BlockId {
public:
    explicit BlockId(std::string filename, int blknum) {
        this->blknum_ = blknum;
        this->filename_ = filename;
    }

    std::string filename() const {
        return this->filename_;
    }

    int blknum() const {
        return this->blknum_;
    }

    std::string to_string();

private:
    int blknum_;
    std::string filename_;
};
}
