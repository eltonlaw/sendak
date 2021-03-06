#include <assert.h>
#include <exception>
#include <vector>
#include "sendak.h"

void test_is_equal_1() {
    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 {1, 2, 3};
    assert(sendak::is_equal(v1, v2));
}

void test_is_equal_2() {
    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 {1, 2, 4};
    assert(!sendak::is_equal(v1, v2));
}

void test_is_equal_3() {
    std::vector<char> v1 {'1', '2', '3'};
    std::vector<char> v2 {'1', '2', '3'};
    assert(sendak::is_equal(v1, v2));
}

void test_parse_lisp_1() {
    std::vector<std::string> actual = sendak::lisp::tokenize("(+ 1 2 34)");
    std::vector<std::string> expected {"(", "+", "1", "2", "34", ")"};
    assert(sendak::is_equal(actual, expected));
}

void test_stack_push_pop() {
    sendak::stack<int> s {};
    assert(s.is_empty());
    s.push(5);
    assert(!s.is_empty());
    s.push(6);
    s.push(7);
    s.push(8);
    assert(s.size() == 4);

    assert(8 == s.pop());
    assert(7 == s.pop());
    assert(6 == s.pop());
    assert(5 == s.pop());
    assert(s.is_empty());
    assert(0 == s.size());
    try {
        s.pop();
    } catch (std::exception& e) {
        assert(e.what() == "Out of Bounds");
    }
}

void test_stack_size() {
    sendak::stack<int> s {};
    assert(0 == s.size());
    s.push(1);
    s.push(2);
    s.push(3);
    assert(3 == s.size());
    s.pop();
    assert(2 == s.size());
    s.push(8);
    assert(3 == s.size());
}
