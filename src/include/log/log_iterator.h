#pragma once

#include "file/file_manager.h"

namespace simpledb {
class LogIterator {
public:
    LogIterator(FileManager *file_manager, const BlockId &block_id);
    bool has_next();
    std::vector<char> next();
    void move_to_block(const BlockId &block_id);

private:
    FileManager *file_manager;
    BlockId block_id;
    std::unique_ptr<Page> page;
    int current_pos;
    int boundary;
};
}