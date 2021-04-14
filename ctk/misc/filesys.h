#pragma once

#include <string>

namespace ctk {

std::string currentPath(std::string cur=".");
void changeCurrentPath(std::string cur);
std::string dirName(std::string cur=".");

}