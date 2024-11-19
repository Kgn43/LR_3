#define BOOST_TEST_MODULE queue_tests

#include <boost/test/included/unit_test.hpp>

#include "classes/Pair.h"
#include "classes/queue.h"

BOOST_AUTO_TEST_CASE(test_create_queue_obj) {
    const auto queue_1 = new queue<int>;
    const auto queue_2 = new queue<string>;
    BOOST_CHECK(queue_1 != nullptr);
    BOOST_CHECK(queue_2 != nullptr);
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
    queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    BOOST_CHECK(queue1.head->value == 1);
    BOOST_CHECK(queue1.tail->value == 2);
    queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2.head->value == "1");
    BOOST_CHECK(queue2.tail->value == "2");
}


BOOST_AUTO_TEST_CASE(test_queue_pop) {
    queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    queue1.pop();
    BOOST_CHECK(queue1.head->value == 2);
    queue1.pop();
    BOOST_CHECK(queue1.head == nullptr);
    queue1.pop();
    queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    queue2.pop();
    BOOST_CHECK(queue2.head->value == "2");
    queue2.pop();
    BOOST_CHECK(queue2.head == nullptr);
    queue2.pop();
}


BOOST_AUTO_TEST_CASE(test_queue_get) {
    queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    BOOST_CHECK(queue1.getFirst() == 1);
    queue<string> queue2;
    queue2.push("1");
    queue2.push("2");
    BOOST_CHECK(queue2.getFirst() == "1");
}

BOOST_AUTO_TEST_CASE(test_queue_operator) {
    queue<int> queue;
    queue.push(1);
    queue.push(2);
    std::stringstream stream;
    stream << queue;
    BOOST_CHECK(stream.str() == "[1] -> [2]");
}


BOOST_AUTO_TEST_CASE(test_split_and_unsplit) {
    queue<string> queue1;
    queue1.push("1");
    queue1.push("2");
    const string str1 = unSplitQueue(queue1, ' ');
    BOOST_CHECK(str1 == "1 2 ");
    string str2 = "1,2,3";
    const queue<string> queue2 = splitToQueue(str2, ',');
    BOOST_CHECK(queue2.head->value == "1");
    BOOST_CHECK(queue2.tail->value == "3");
}