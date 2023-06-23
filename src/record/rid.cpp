#include "record/rid.h"

namespace simpledb {
std::string RID::to_string() {
    return "[" + std::to_string(blknum_) + ", " + std::to_string(slot_) + "]";
}
}
