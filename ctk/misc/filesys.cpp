#include "ctk/misc/filesys.h"

#include <filesystem>

namespace ctk {

std::string currentPath(std::string cur) {
    // The method current_path(NEW_PATH) changes the value 
    // of current path. Thus, aux is used to restore it.
    auto aux = std::filesystem::current_path();
    std::filesystem::current_path(cur);
    std::string path = std::filesystem::current_path();
    std::filesystem::current_path(aux);
    return path;
}

void changeCurrentPath(std::string cur) {
    std::filesystem::current_path(cur);
}

std::string dirName(std::string cur) {
    std::string dir = currentPath(cur);
    return dir;
}

}
