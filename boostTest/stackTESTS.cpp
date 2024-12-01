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
    const auto stack4 = new Stack<int>(10);
    const auto stack5 = new Stack<string>(10);
    const auto stack6 = new Stack<char>(10);
    BOOST_CHECK(stack4 != nullptr);
    BOOST_CHECK(stack5 != nullptr);
    BOOST_CHECK(stack6 != nullptr);
}


BOOST_AUTO_TEST_CASE(test_stack_push) {
    Stack<int> queue;
    queue.push(2);
    queue.push(1);
    BOOST_CHECK(queue.getLast() == 1);
    BOOST_CHECK(queue.get_size() == 2);
    Stack<string> queue2;
    queue2.push("2");
    queue2.push("1");
    BOOST_CHECK(queue2.getLast() == "1");
    BOOST_CHECK(queue2.get_size() == 2);
    Stack<char> queue3;
    queue3.push('2');
    queue3.push('1');
    BOOST_CHECK(queue3.getLast() == '1');
    BOOST_CHECK(queue3.get_size() == 2);
}


BOOST_AUTO_TEST_CASE(test_stack_pop) {
    Stack<int> queue;
    queue.push(2);
    queue.push(1);
    queue.pop();
    BOOST_CHECK(queue.getLast() == 2);
    queue.pop();
    BOOST_CHECK_THROW(int i = queue[0], std::out_of_range);
    Stack<string> queue2;
    queue2.push("2");
    queue2.push("1");
    queue2.pop();
    BOOST_CHECK(queue2.getLast() == "2");
    queue2.pop();
    BOOST_CHECK_THROW(string s = queue2[0], std::out_of_range);
    Stack<char> queue3;
    queue3.push('2');
    queue3.push('1');
    queue3.pop();
    BOOST_CHECK(queue3.getLast() == '2');
    queue3.pop();
    BOOST_CHECK_THROW(char c = queue3[0], std::out_of_range);
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
    BOOST_CHECK(queue[0] == 2);
    BOOST_CHECK_THROW(queue[100], std::out_of_range);

    Stack<string> queue1;
    queue1.push("1");
    queue1.push("2");
    std::stringstream stream1;
    stream1 << queue1;
    BOOST_CHECK(stream1.str() == "[2] -> [1]");
    BOOST_CHECK(queue1[0] == "2");
    BOOST_CHECK_THROW(queue1[100], std::out_of_range);

    Stack<char> queue2;
    queue2.push('1');
    queue2.push('2');
    std::stringstream stream2;
    stream2 << queue2;
    BOOST_CHECK(stream2.str() == "[2] -> [1]");
    BOOST_CHECK(queue2[0] == '2');
    BOOST_CHECK_THROW(queue2[100], std::out_of_range);
}