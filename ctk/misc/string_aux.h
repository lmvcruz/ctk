#pragma once

#include <string>
#include <vector>

namespace ctk {

std::vector< std::string > SplitString(std::string str, std::string sep);

bool Contains(std::string str, std::string exp);
bool Contains(std::string str, const std::vector<std::string>& exps);

size_t IndexOf(std::string str, std::string exp, size_t init=0);

std::vector<int> ContainsIndices(std::string str, std::string exp);
std::vector<int> ContainsIndices(std::string str, 
                                const std::vector<std::string>& exps);
}