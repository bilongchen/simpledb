#include <string>

namespace simpledb {

class RID {
public:
    explicit RID(int blknum, int slot) {
        this->blknum_ = blknum;
        this->slot_ = slot;
    }

    int blknum() {
        return blknum_;
    }

    int slot() {
        return slot_;
    }

    std::string to_string();
 
private:
    int blknum_;
    int slot_;
};

}
