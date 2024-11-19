#define BOOST_TEST_MODULE singleConnList_tests

#include <boost/test/included/unit_test.hpp>

#include "classes/singleConnList.h"

BOOST_AUTO_TEST_CASE(test_create_obj) {
    const auto slist_1 = new sList<int>;
    const auto slist_2 = new sList<string>;
    BOOST_CHECK(slist_1 != nullptr);
    BOOST_CHECK(slist_2 != nullptr);
}

BOOST_AUTO_TEST_CASE(test_insert) {
    sList<int> list;
    list.headInsert(2);
    list.headInsert(1);
    list.backInsert(3);
    BOOST_CHECK(list.head->value == 1);
    BOOST_CHECK(list.head->next->next->value == 3);
    sList<string> list2;
    list2.headInsert("2");
    list2.headInsert("1");
    list2.backInsert("3");
    BOOST_CHECK(list2.head->value == "1");
    BOOST_CHECK(list2.head->next->next->value == "3");
}


BOOST_AUTO_TEST_CASE(test_del) {
    sList<int> list_1;
    list_1.headInsert(3);
    list_1.headInsert(2);
    list_1.headInsert(1);
    list_1.delFirst();
    BOOST_CHECK(list_1.head->value == 2);
    list_1.delLast();
    BOOST_CHECK(list_1.head->next == nullptr);
    sList<int> list_2;
    list_2.headInsert(4);
    list_2.headInsert(3);
    list_2.headInsert(2);
    list_2.headInsert(1);
    list_2.delByVal(1);
    BOOST_CHECK(list_2.head->value == 2);
    list_2.delByVal(4);
    BOOST_CHECK(list_2.head->next->next == nullptr);
    list_2.delByVal(888);
}


BOOST_AUTO_TEST_CASE(test_scl_del_str) {
    sList<string> list_1;
    list_1.headInsert("3");
    list_1.headInsert("2");
    list_1.headInsert("1");
    list_1.delFirst();
    BOOST_CHECK(list_1.head->value == "2");
    list_1.delLast();
    BOOST_CHECK(list_1.head->next == nullptr);
    sList<string> list_2;
    list_2.headInsert("4");
    list_2.headInsert("3");
    list_2.headInsert("2");
    list_2.headInsert("1");
    list_2.delByVal("1");
    BOOST_CHECK(list_2.head->value == "2");
    list_2.delByVal("4");
    BOOST_CHECK(list_2.head->next->next == nullptr);
    list_2.delByVal("888");
}


BOOST_AUTO_TEST_CASE(test_scl_operator) {
    sList<int> list1;
    list1.headInsert(1);
    list1.backInsert(2);
    std::stringstream stream;
    stream << list1;
    BOOST_CHECK(stream.str() == "{[1], [2]}");
    sList<string> list2;
    list2.headInsert("1");
    list2.backInsert("2");
    std::stringstream stream2;
    stream2 << list2;
    BOOST_CHECK(stream2.str() == "{[1], [2]}");
}


BOOST_AUTO_TEST_CASE(test_scl_find) {
    sList<int> list1;
    list1.headInsert(1);
    list1.headInsert(0);
    BOOST_CHECK(list1.find(1) == true);
    BOOST_CHECK(list1.find(999) == false);
    sList<string> list2;
    list2.headInsert("1");
    list2.headInsert("0");
    BOOST_CHECK(list2.find("1") == true);
    BOOST_CHECK(list2.find("999") == false);
}