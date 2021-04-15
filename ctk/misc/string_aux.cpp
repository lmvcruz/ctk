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

}
