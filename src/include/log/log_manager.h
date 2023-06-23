#pragma once

#include <memory>

#include "file/file_manager.h"
#include "common/constants.h"

namespace simpledb {

class LogManager {
public:
    LogManager(FileManager *file_manager, const std::string log_file);
    void flush(int lsn);
    int append(const std::vector<char> logrec);

private:
    FileManager *file_manager;
    std::unique_ptr<Page> log_page;
    BlockId currentblk;
    string logfile;
    int latest_lsn = 0;
    int last_saved_lsn = 0;
    std::mutex lock;

    BlockId append_new_block();
    void flush();
};
}