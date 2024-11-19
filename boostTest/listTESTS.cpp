#define BOOST_TEST_MODULE list_tests

#include <boost/test/included/unit_test.hpp>
#include "classes/list.h"

BOOST_AUTO_TEST_CASE(test_create_obj) {
    const auto list_1 = new List<int>;
    const auto list_2 = new List<string>;
    const auto list_3 = new List<Pair>;
    const auto node_1 = new ListNode<Pair>;
    const auto node_2 = new ListNode<string>("123", nullptr, nullptr);
    const auto node_3 = new ListNode<int>(1);
    BOOST_CHECK(list_1 != nullptr);
    BOOST_CHECK(list_2 != nullptr);
    BOOST_CHECK(list_3 != nullptr);
    BOOST_CHECK(node_1 != nullptr);
    BOOST_CHECK(node_2 != nullptr);
    BOOST_CHECK(node_3 != nullptr);
}


BOOST_AUTO_TEST_CASE(test_Pair_operators) {
    Pair Pair_1("1","1");
    Pair Pair_2("2", "1");
    Pair Pair_3("1", "1");
    BOOST_CHECK(Pair_1 != Pair_2);
    BOOST_CHECK(Pair_1 == Pair_3);
    std::stringstream stream;
    stream << Pair_1;
    BOOST_CHECK(stream.str() == "1, 1");
}


BOOST_AUTO_TEST_CASE(test_list_int_insert) {
    List<int> list;
    list.headInsert(3);
    list.headInsert(2);
    list.headInsert(1);
    list.backInsert(4);
    List<int> list_2;
    list_2.backInsert(0);
    BOOST_CHECK(list.first->value == 1);
    BOOST_CHECK(list.last->value == 4);
    BOOST_CHECK(list.first->next->value == 2);
    BOOST_CHECK(list_2.first == list_2.last);
}


BOOST_AUTO_TEST_CASE(test_list_string_insert) {
    List<string> list;
    list.headInsert("3");
    list.headInsert("2");
    list.headInsert("1");
    list.backInsert("4");
    List<string> list_2;
    list_2.backInsert("0");
    BOOST_CHECK(list.first->value == "1");
    BOOST_CHECK(list.last->value == "4");
    BOOST_CHECK(list.first->next->value == "2");
    BOOST_CHECK(list_2.first == list_2.last);
}


BOOST_AUTO_TEST_CASE(test_list_pair_insert) {
    List<Pair> list;
    list.headInsert({"3", "3"});
    list.headInsert({"2", "2"});
    list.headInsert({"1", "1"});
    list.backInsert({"4", "4"});
    List<Pair> list_2;
    list_2.backInsert({"0", "0"});
    BOOST_CHECK(list.first->value.key == "1");
    BOOST_CHECK(list.last->value.key == "4");
    BOOST_CHECK(list.first->next->value.key == "2");
    BOOST_CHECK(list_2.first == list_2.last);
}


BOOST_AUTO_TEST_CASE(test_list_operator) {
    List<int> list;
    list.backInsert(1);
    list.backInsert(2);
    std::stringstream stream;
    stream << list;
    BOOST_CHECK(stream.str() == "{[1] <=> [2]}");
    List<string> list1;
    list1.backInsert("1");
    list1.backInsert("2");
    std::stringstream stream1;
    stream1 << list1;
    BOOST_CHECK(stream1.str() == "{[1] <=> [2]}");
    List<Pair> list2;
    list2.backInsert({"1", "1"});
    list2.backInsert({"2", "2"});
    std::stringstream stream2;
    stream2 << list2;
    BOOST_CHECK(stream2.str() == "{[1, 1] <=> [2, 2]}");
}


BOOST_AUTO_TEST_CASE(test_list_int_del) {
    List<int> list;
    list.headInsert(3);
    list.headInsert(2);
    list.headInsert(1);
    list.delFirst();
    BOOST_CHECK(list.first->value == 2);
    list.delLast();
    BOOST_CHECK(list.last->value == 2);
    List<int> list_2;
    list_2.backInsert(1);
    list_2.delFirst();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    list_2.backInsert(1);
    list_2.delLast();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    List<int> list_3;
    list_3.backInsert(1);
    list_3.backInsert(2);
    list_3.backInsert(3);
    list_3.backInsert(4);
    list_3.backInsert(5);
    list_3.backInsert(6);
    list_3.backInsert(7);
    list_3.delByVal(1);
    BOOST_CHECK(list_3.first->value == 2);
    list_3.delByVal(7);
    BOOST_CHECK(list_3.last->value == 6);
    list_3.delByVal(3);
    BOOST_CHECK(list_3.first->next->value == 4);
    BOOST_CHECK_THROW(list_3.delByVal(1000), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(test_list_string_del) {
    List<string> list;
    list.headInsert("3");
    list.headInsert("2");
    list.headInsert("1");
    list.delFirst();
    BOOST_CHECK(list.first->value == "2");
    list.delLast();
    BOOST_CHECK(list.last->value == "2");
    List<string> list_2;
    list_2.backInsert("1");
    list_2.delFirst();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    list_2.backInsert("1");
    list_2.delLast();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    List<string> list_3;
    list_3.backInsert("1");
    list_3.backInsert("2");
    list_3.backInsert("3");
    list_3.backInsert("4");
    list_3.backInsert("5");
    list_3.backInsert("6");
    list_3.backInsert("7");
    list_3.delByVal("1");
    BOOST_CHECK(list_3.first->value == "2");
    list_3.delByVal("7");
    BOOST_CHECK(list_3.last->value == "6");
    list_3.delByVal("3");
    BOOST_CHECK(list_3.first->next->value == "4");
    BOOST_CHECK_THROW(list_3.delByVal("1000"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(test_list_pair_del) {
    List<Pair> list;
    list.headInsert({"3", "3"});
    list.headInsert({"2", "2"});
    list.headInsert({"1", "1"});
    list.delFirst();
    BOOST_CHECK(list.first->value.key == "2");
    list.delLast();
    BOOST_CHECK(list.last->value.key == "2");
    List<Pair> list_2;
    list_2.backInsert({"3", "3"});
    list_2.delFirst();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    list_2.backInsert({"3", "3"});
    list_2.delLast();
    BOOST_CHECK(list_2.first == nullptr && list_2.last == nullptr);
    List<Pair> list_3;
    list_3.backInsert({"1", "1"});
    list_3.backInsert({"3", "3"});
    list_3.delByVal({"3", "3"});
    BOOST_CHECK(list_3.first->value.key == "1");
}


BOOST_AUTO_TEST_CASE(test_list_find) {
    List<int> list;
    list.headInsert(3);
    list.headInsert(2);
    list.headInsert(1);
    bool isFined = list.find(1);
    BOOST_CHECK(isFined == true);
    isFined = list.find(100);
    BOOST_CHECK(isFined == false);
    List<string> list1;
    list1.headInsert("1");
    bool isFined1 = list1.find("1");
    BOOST_CHECK(isFined1 == true);
    isFined1 = list1.find("100");
    BOOST_CHECK(isFined1 == false);
    List<Pair> list2;
    list2.headInsert({"1", "1"});
    bool isFined2 = list2.find({"1", "1"});
    BOOST_CHECK(isFined2 == true);
    isFined2 = list2.find({"100", "100"});
    BOOST_CHECK(isFined2 == false);
}


BOOST_AUTO_TEST_CASE(test_split_and_unsplit) {
    const string str1 = "1 2 3";
    const List<string> list = splitToList(str1, ' ');
    BOOST_CHECK(list.first->value == "1" && list.last->value == "3");
    List<string> list2;
    list2.backInsert("1");
    list2.backInsert("2");
    list2.backInsert("3");
    const string str2 = unSplitList(list2);
    BOOST_CHECK(str2 == str1 + ' ');
    const string str3 = "1,1___2,2___3_,3";
    const List<Pair> list_3 = splitToListPair(str3, "___", ',');
    BOOST_CHECK(list_3.first->value.key == "1");
}
