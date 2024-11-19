#define BOOST_TEST_MODULE stack_tests

#include <boost/test/included/unit_test.hpp>

#include "classes/Stack.h"

BOOST_AUTO_TEST_CASE(test_stack_create_obj) {
    const auto stack1 = new Stack<int>;
    const auto stack2 = new Stack<string>;
    const auto stack3 = new Stack<char>;
    BOOST_CHECK(stack1 != nullptr);
    BOOST_CHECK(stack2 != nullptr);
    BOOST_CHECK(stack3 != nullptr);
}


BOOST_AUTO_TEST_CASE(test_stack_push) {
    Stack<int> queue;
    queue.push(2);
    queue.push(1);
    BOOST_CHECK(queue.head->value == 1);
    BOOST_CHECK(queue.size == 2);
    Stack<string> queue2;
    queue2.push("2");
    queue2.push("1");
    BOOST_CHECK(queue2.head->value == "1");
    BOOST_CHECK(queue.size == 2);
    Stack<char> queue3;
    queue3.push('2');
    queue3.push('1');
    BOOST_CHECK(queue3.head->value == '1');
    BOOST_CHECK(queue.size == 2);
}


BOOST_AUTO_TEST_CASE(test_stack_pop) {
    Stack<int> queue;
    queue.push(2);
    queue.push(1);
    queue.pop();
    BOOST_CHECK(queue.head->value == 2);
    queue.pop();
    BOOST_CHECK(queue.head == nullptr);
    Stack<string> queue2;
    queue2.push("2");
    queue2.push("1");
    queue2.pop();
    BOOST_CHECK(queue2.head->value == "2");
    queue2.pop();
    BOOST_CHECK(queue2.head == nullptr);
    Stack<char> queue3;
    queue3.push('2');
    queue3.push('1');
    queue3.pop();
    BOOST_CHECK(queue3.head->value == '2');
    queue3.pop();
    BOOST_CHECK(queue3.head == nullptr);
}


BOOST_AUTO_TEST_CASE(test_stack_get) {
    Stack<int> queue;
    queue.push(1);
    queue.push(2);
    BOOST_CHECK(queue.getLast() == 2);
    Stack<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2.getLast() == "2");
    Stack<char> queue3;
    queue3.push('1');
    queue3.push('2');
    BOOST_CHECK(queue3.getLast() == '2');
}

BOOST_AUTO_TEST_CASE(test_sttack_operator) {
    Stack<int> queue;
    queue.push(1);
    queue.push(2);
    std::stringstream stream;
    stream << queue;
    BOOST_CHECK(stream.str() == "[2] -> [1]");
}


BOOST_AUTO_TEST_CASE(test_stack_split_and_unsplit) {
    Stack<string> queue1;
    queue1.push("1");
    queue1.push("2");
    const string str1 = unSplitStack(queue1, ' ');
    BOOST_CHECK(str1 == "1 2 ");
    string str2 = "1,2,3";
    const Stack<string> queue2 = splitToStack(str2, ',');
    BOOST_CHECK(queue2.head->value == "3");
    BOOST_CHECK(queue2.size == 3);
}