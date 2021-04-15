#pragma once

#include <string>
#include <vector>

namespace ctk {

bool Exists(std::string filename);
bool IsFile(std::string filename);
bool IsDir(std::string dirname);
bool IsEmpty(std::string name);

void ChangeCurrentPath(std::string cur);
std::string CurrentPath(std::string cur=".");
std::string AbsolutePath(std::string name);

bool ContainsFileOrDir(std::string curdir, std::string filename);
std::vector<std::string> ListDir(std::string cur = ".");
std::vector<std::string> ListFilesContainingAllExpressions(std::string cur,
                                    const std::vector<std::string>& exps);
std::vector<std::string> ListFilesContainingAnyExpressions(std::string cur,
                                    const std::vector<std::string>& exps);

}