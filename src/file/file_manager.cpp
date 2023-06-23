#include "file/file_manager.h"
#include "utils/logger.h"

namespace fs = std::filesystem;

namespace simpledb {

FileManager::FileManager(
    const fs::path &db_directory,
    int blocksize
) : db_directory_(db_directory), blocksize_(blocksize) {
    fs::directory_entry dir(db_directory);
    is_new_ = !dir.exists();

    // Create the directory if the database is new
    if (is_new_) {
        fs::create_directory(db_directory);
    }

    // remove any leftover temporary tables
    for (auto &f: fs::directory_iterator(db_directory)) {
        if (f.path().filename().string().rfind("temp", 0) == 0) {
            fs::remove(f.path());
        }
    }
}

void FileManager::read(const BlockId &block_id, Page &page) {
    mutex_.lock();
    const std::string filename = block_id.filename();
    auto fh = get_file(filename);
    size_t offset = block_id.blknum() * blocksize_;
    fh -> seekp(offset, std::ios::beg);
    std::vector<char> buffer(blocksize_);
    fh -> read(&buffer[0], blocksize_);
    page.set_bytes(0, buffer);
    mutex_.unlock();
}

void FileManager::write(const BlockId &block_id, Page &page) {
    mutex_.lock();
    size_t offset = block_id.blknum() * blocksize_;
    auto fh = get_file(block_id.filename());
    fh -> seekp(offset);
    std::vector<char> page_data = page.contents();
    char* p_page_data = reinterpret_cast<char*>(page_data.data());
    fh -> write(p_page_data, blocksize_);
    mutex_.unlock();
}

BlockId FileManager::append(const std::string &filename) {
    mutex_.lock();
    int newblknum = length(filename);
    BlockId blk = BlockId(filename, newblknum);
    std::vector<char> bytes;
    bytes.resize(blocksize_);
    auto fh = get_file(filename);
    fh -> seekp(newblknum * blocksize_, std::ios::beg);
    fh -> write(&bytes[0], blocksize_);
    fh -> flush();
    mutex_.unlock();
    return blk;
}

int FileManager::length(const std::string &filename) {
    fs::path path = db_directory_ / filename;
    int size = fs::file_size(path);
    return size / blocksize_;
}

bool FileManager::is_new() {
    return is_new_;
}

int FileManager::blocksize() {
    return blocksize_;
}

std::shared_ptr<std::fstream> FileManager::get_file(const std::string &filename) {
    std::shared_ptr<std::fstream> fh = std::make_shared<std::fstream>();
    fs::path file_path = db_directory_ / filename;

    if (open_files_.find(file_path) != open_files_.end()) {
        fh = open_files_[file_path];
        if (fh -> is_open()) {
            return fh;
        }
    }

    fh -> open(file_path.string(), std::ios::binary | std::ios::in | std::ios::out);

    if (!fh -> is_open()) {
        LOG_ERROR("Can't open file: %s", file_path.string());
        throw std::runtime_error("can't open file");
    }

    open_files_[file_path] = fh;
    return fh;
}
}