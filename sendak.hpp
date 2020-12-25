#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

namespace sendak {
namespace lisp {

/* create a list of tokens */
std::vector<std::string> tokenizer(std::string fp) {
    std::ifstream is(fp);
    char c;
    std::vector<std::string> tokens;
    std::string str;

    std::string specials {"+-()\"'"};
    while (is.get(c)) {
        // To handle arbitrarily long names, if previous char was an
        // alphanumeric and current one isn't then the symbol has
        // terminated and can be pushed to the tokens vector
        if (!str.empty() && !isalnum(c)) {
            tokens.push_back(str);
            str.clear();
        }

        // Main char handling loop
        if (isspace(c)) {
            // whitespace is ignored
        }
        // check for arbitrary strings/numbers (this and the other call to
        // alnum will need to change depending on what's allowed in
        // variable names)
        else if (isalnum(c)) {
            str.append(1, c);
        }
        else if (specials.find(c) != std::string::npos) {
            tokens.push_back(std::string {c});
        }
    }
    is.close();
    return tokens;
}

void Parser::read(std::string fp) {
    auto tokens = tokenizer(fp);

    for (auto t: tokens) {
        std::cout << t << " ";
    }
}

} // ns parser
} // ns sendak
