#include <assert.h>
#include <iostream>
#include <vector>
#include "sendak.hpp"

void test_is_equal_1() {
    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 {1, 2, 3};
    assert(sendak::is_equal(v1, v2));
    std::cout << ".";
}

void test_is_equal_2() {
    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 {1, 2, 4};
    assert(!sendak::is_equal(v1, v2));
    std::cout << ".";
}

void test_is_equal_3() {
    std::vector<char> v1 {'1', '2', '3'};
    std::vector<char> v2 {'1', '2', '3'};
    assert(sendak::is_equal(v1, v2));
    std::cout << ".";
}

void test_parse_lisp_1() {
    std::vector<std::string> actual = sendak::lisp::tokenize("(+ 1 2 34)");
    std::vector<std::string> expected {"(", "+", "1", "2", "34", ")"};
    assert(sendak::is_equal(actual, expected));
    std::cout << ".";
}

void run_tests() {
    // Instantiate vector of all testing functions (thunks)
    std::vector<void(*)()> test_fns {
        test_is_equal_1, test_is_equal_2, test_is_equal_3,
        test_parse_lisp_1,
    };
    // Loop over each unit test, running it
    for (const auto& test_fn : test_fns) {
        test_fn();
    }
    std::cout << std::endl;
}
