#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <exception>
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

class out_of_bounds_exception: public std::exception {
  virtual const char* what() const throw()
  {
    return "Out of Bounds";
  }
} out_of_bounds_ex;

template<class T>
class stack {
    public:
        stack();
        stack(int);
        ~stack();
        bool is_empty();
        void push(T);
        T pop();
    private:
        void realloc_arr();
        int top = 0;
        int stack_size = 5;
        T* arr;
};

template<class T>
stack<T>::stack() {
    arr = (T*) std::malloc(stack_size * sizeof(T));
}

template<class T>
stack<T>::stack(int s) {
    stack_size = s;
    arr = (T*) std::malloc(stack_size * sizeof(T));
}

template<class T>
stack<T>::~stack(){
    std::free(arr);
}

template<class T>
bool stack<T>::is_empty() {
    return top == 0; 
}

template<class T>
void stack<T>::realloc_arr() {
    stack_size = stack_size * 2;
    arr = (T*)realloc(arr, stack_size * sizeof(T));
}

template<class T>
void stack<T>::push(T val) {
    if (top == stack_size - 1) {
        realloc_arr(); 
    }
    arr[top++] = val;
}

template<class T>
T stack<T>::pop() {
    if (--top == -1) {
        throw out_of_bounds_ex;
    } else {
        return arr[top];
    }
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

} // ns lisp

} // ns sendak
