#include <iostream>
#include "test_sendak.h"

void run_tests() {
    // Instantiate vector of all testing functions (thunks)
    std::vector<void(*)()> test_fns {
        test_is_equal_1,
        test_is_equal_2,
        test_is_equal_3,
        test_parse_lisp_1,
        test_Stack,
    };
    // Loop over each unit test, running it
    for (const auto& test_fn : test_fns) {
        test_fn();
        std::cout << ".";
    }
    std::cout << std::endl;
}

// Runs all unit tests
int main(int argc, char** argv) {
    run_tests();
}
