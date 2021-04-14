#pragma once

#include <string>
#include <vector>

namespace ctk {

bool exists(std::string filename);
bool isFile(std::string filename);
bool isDir(std::string dirname);
bool isEmpty(std::string name);

void changeCurrentPath(std::string cur);
std::string currentPath(std::string cur=".");
std::string absolutePath(std::string name);

bool containsFileOrDir(std::string curdir, std::string filename);
std::vector<std::string> listDir(std::string cur = ".");
std::vector<std::string> listFilesContainingAllExpressions(std::string cur,
                                    const std::vector<std::string>& exps);
std::vector<std::string> listFilesContainingAnyExpressions(std::string cur,
                                    const std::vector<std::string>& exps);

}