#include "ctk/misc/filesys.h"

#include <filesystem>

namespace ctk {

bool exists(std::string filename) {
    return std::filesystem::exists(filename);
}

bool isFile(std::string filename) {
    return std::filesystem::is_regular_file(filename);
}

bool isDir(std::string dirname) {
    return std::filesystem::is_directory(dirname);
}

// Checks if a file or directory is empty
bool isEmpty(std::string name) {
    return std::filesystem::is_empty(name);
}

void changeCurrentPath(std::string cur) {
    std::filesystem::current_path(cur);
}

std::string currentPath(std::string cur) {
    // The method current_path(NEW_PATH) changes the value 
    // of current path. Thus, aux is used to restore it.
    auto aux = std::filesystem::current_path();
    changeCurrentPath(cur);
    std::string path = std::filesystem::current_path();
    changeCurrentPath(aux);
    return path;
}

std::string absolutePath(std::string name) {
    return std::filesystem::canonical(name);
}

bool containsFileOrDir(std::string curdir, std::string filename) {
    auto aux = std::filesystem::current_path();
    changeCurrentPath(curdir);
    bool ret = exists(filename);
    changeCurrentPath(aux);
    return ret;
}

std::vector<std::string> listDir(std::string cur) {
    std::vector<std::string> files;
    for (auto& p: std::filesystem::directory_iterator(cur)) {
        files.push_back(p.path());
    }
    return files;
}

// The filename must contain all provided expressions
std::vector<std::string> listFilesContainingAllExpressions(std::string cur,
                                    const std::vector<std::string>& exps) 
{
    std::vector<std::string> files;
    for (auto& path: std::filesystem::directory_iterator(cur)) {
        std::string name = path.path();
        bool valid = true;
        for (auto& exp : exps) {
            if (name.find(exp) == std::string::npos) {
                valid = false;
                break;
            }
        }
        if (valid) files.push_back(name);
    }
    return files;
}

std::vector<std::string> listFilesContainingAnyExpressions(std::string cur,
                                    const std::vector<std::string>& exps) 
{
    std::vector<std::string> files;
    for (auto& path: std::filesystem::directory_iterator(cur)) {
        std::string name = path.path();
        bool valid = false;
        for (auto& exp : exps) {
            if (name.find(exp) != std::string::npos) {
                valid = true;
                break;
            }
        }
        if (valid) files.push_back(name);
    }
    return files;
}

}
