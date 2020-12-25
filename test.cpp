#include <assert.h>
#include <iostream>
#include <vector>
#include "sendak.hpp"

void test_parse_lisp() {
    sendak::lisp::Parser p;
    p.read("test.clj");
}

// Runs all unit tests
int main(int argc, char** argv) {
    // Instantiate vector of all testing functions (thunks)
    std::vector<void(*)()> test_fns {
        test_parse_lisp,
    };
    // Loop over each unit test, running it
    for (const auto& test_fn : test_fns) {
        test_fn();
    }
}
