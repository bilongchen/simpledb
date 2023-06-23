#include "file/block_id.h"

namespace simpledb {

std::string BlockId::to_string() {
    return "[" + std::to_string(blknum_) + ", " + filename_ + "]";
}
}
