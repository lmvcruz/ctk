#include "ctk/misc/string_aux.h"

#include <regex>

namespace ctk {

std::vector< std::string > SplitString(std::string str, std::string sep) {
    std::vector<std::string> splitted;
    std::string regex_sep_str = "[" + sep + "]+";
    std::regex regex_sep(regex_sep_str);
    std::sregex_token_iterator tokens(str.cbegin(), str.cend(), regex_sep, -1);
    std::sregex_token_iterator end;
    for(; tokens != end; ++tokens){
        splitted.push_back(*tokens);
    }
    return splitted;
}

bool Contains(std::string str, std::string exp) {
    return str.find(exp) != std::string::npos;
}

bool Contains(std::string str, const std::vector<std::string>& exps) {
    for (auto& exp: exps) {
        if (Contains(str, exp))
            return true;
    }
    return false;
}

size_t IndexOf(std::string str, std::string exp, size_t init) {
    return str.find(exp, init);
}

std::vector<int> ContainsIndices(std::string str, std::string exp) {
    std::vector<int> indices;
    size_t pos = IndexOf(str, exp, 0);
    while (pos != std::string::npos) {
        indices.push_back(pos);
        pos = IndexOf(str, exp, pos + 1);
    }
    return indices;
}

// Since the indices are sorted, the occurence in the returned 
// vector are not related to the expressions order
std::vector<int> ContainsIndices(std::string str, 
            const std::vector<std::string>& exps) {
    std::vector<int> indices;
    for (auto& exp: exps) {
        auto newIndices = ContainsIndices(str, exp);
        indices.insert(indices.end(), newIndices.begin(), newIndices.end());
    }
    std::sort(indices.begin(), indices.end());
    return indices;
}

}
