#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>

namespace sendak {

// Vector Equality
//
// Copied from: https://www.techiedelight.com/check-two-vectors-equal-cpp/
template<typename T>
bool is_equal(std::vector<T> const &v1, std::vector<T> const &v2)
{
    return (v1.size() == v2.size() &&
            std::equal(v1.begin(), v1.end(), v2.begin()));
}

namespace lisp {

// Create a list of tokens
//
// Ascii representing some lisp code is parsed into 1d vector of strings
// representing tokenized symbols
std::vector<std::string> tokenize(std::string source_code) {
    std::vector<std::string> tokens;
    std::string str;

    std::string specials {"+-()\"'"};
    for (char const &c: source_code) {
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
    return tokens;
}

std::vector<std::string> tokenize_file(std::string fp) {
    std::ifstream is(fp);
    std::stringstream buffer;
    buffer << is.rdbuf();
    is.close();

    return tokenize(buffer.str());
}

} // ns parser
} // ns sendak
