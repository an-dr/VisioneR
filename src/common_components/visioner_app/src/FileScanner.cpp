
#include "FileScanner.hpp"
#include <filesystem>

FileScanner::FileScanner(const std::string &path) : m_path(path) {}

std::vector<std::string> FileScanner::GetFiles(const std::string &pattern) {
    std::vector<std::string> files;
    for (const auto &entry : std::filesystem::directory_iterator(m_path)) {
        if (entry.is_regular_file() &&
            entry.path().string().find(pattern) != std::string::npos) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}
