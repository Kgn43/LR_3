#define BOOST_TEST_MODULE queue_tests

#include <boost/test/included/unit_test.hpp>

#include "classes/Pair.h"
#include "classes/queue.h"

BOOST_AUTO_TEST_CASE(test_create_queue_obj) {
    const auto queue_1 = new Queue<int>;
    const auto queue_2 = new Queue<string>;
    BOOST_CHECK(queue_1 != nullptr);
    BOOST_CHECK(queue_2 != nullptr);
    const auto queue_3 = new Queue<int>(1);
    const auto queue_4 = new Queue<string>(10);
    BOOST_CHECK(queue_3 != nullptr);
    BOOST_CHECK(queue_4 != nullptr);
}


BOOST_AUTO_TEST_CASE(test_Node) {
    const auto Node_1 = new Node<int>;
    const auto Node_2 = new Node<string>;
    const auto Node_3 = new Node<int>(10);
    const auto Node_4 = new Node<string>("1");
    const auto Node_5 = new Node<int>(10, nullptr);
    const auto Node_6 = new Node<string>("1", nullptr);
    BOOST_CHECK(Node_1 != nullptr);
    BOOST_CHECK(Node_2 != nullptr);
    BOOST_CHECK(Node_3 != nullptr);
    BOOST_CHECK(Node_4 != nullptr);
    BOOST_CHECK(Node_5 != nullptr);
    BOOST_CHECK(Node_6 != nullptr);
}


BOOST_AUTO_TEST_CASE(test_queue_push) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    BOOST_CHECK(queue1[0] == 1);
    BOOST_CHECK(queue1[1] == 2);
    Queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2[0] == "1");
    BOOST_CHECK(queue2[1] == "2");
}


BOOST_AUTO_TEST_CASE(test_queue_pop) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    queue1.pop();
    BOOST_CHECK(queue1[0] == 2);
    queue1.pop();
    BOOST_CHECK_THROW(queue1[0], std::out_of_range);
    queue1.pop();
    Queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    queue2.pop();
    BOOST_CHECK(queue2[0] == "2");
    queue2.pop();
    BOOST_CHECK_THROW(queue2[0], std::out_of_range);
    queue2.pop();
}


BOOST_AUTO_TEST_CASE(test_queue_get) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    BOOST_CHECK(queue1.getFirst() == 1);
    Queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2.getFirst() == "1");
}


BOOST_AUTO_TEST_CASE(test_queue_get_size) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    BOOST_CHECK(queue1.get_size() == 2);
    Queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2.get_size() == 2);
}


BOOST_AUTO_TEST_CASE(test_queue_operator) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    std::stringstream stream;
    stream << queue;
    BOOST_CHECK(stream.str() == "[1] -> [2]");

    Queue<string> queue1;
    queue1.push("1");
    queue1.push("2");
    std::stringstream stream1;
    stream1 << queue1;
    BOOST_CHECK(stream1.str() == "[1] -> [2]");
}