#include <map>
#include <filesystem>
#include <mutex>
#include <fstream>

#include "file/block_id.h"
#include "file/page.h"

namespace simpledb {

class FileManager {
public:
    FileManager(const std::filesystem::path &db_Directory, int blocksize);
    void read(const BlockId &block_id, Page &page);
    void write(const BlockId &Block_id, Page &page);
    BlockId append(const std::string &filename);
    int length(const std::string &filename);
    bool is_new();
    int blocksize();

private:
    std::filesystem::path db_directory_;
    int blocksize_;
    bool is_new_;
    std::mutex mutex_;
    std::map<std::filesystem::path, std::shared_ptr<std::fstream>> open_files_;

    std::shared_ptr<std::fstream> get_file(const std::string &filename);
};

}