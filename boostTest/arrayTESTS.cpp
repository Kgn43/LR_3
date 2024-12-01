#define BOOST_TEST_MODULE array_tests

#include <boost/test/included/unit_test.hpp>
#include "classes/arr.h"

BOOST_AUTO_TEST_CASE(test_create_obj) {
    const auto intArray = new arr<int>;
    const auto stringArray = new arr<string>;
    BOOST_CHECK(intArray != nullptr);
    BOOST_CHECK(stringArray != nullptr);
    const arr<int> arr1(3);
    const arr<string> arr2(3);
    BOOST_CHECK(arr1.get_size() == 3);
    BOOST_CHECK(arr2.get_size() == 3);
}


BOOST_AUTO_TEST_CASE(test_push_back) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);
    stringArray.push_back("0");
    stringArray.push_back("1");
    stringArray.push_back("2");

    BOOST_CHECK(intArray.get_size() == 3);
    BOOST_CHECK(intArray[0] == 1);
    BOOST_CHECK(intArray[1] == 2);
    BOOST_CHECK(intArray[2] == 3);
    BOOST_CHECK(stringArray.get_size() == 3);
    BOOST_CHECK(stringArray[0] == "0");
    BOOST_CHECK(stringArray[1] == "1");
    BOOST_CHECK(stringArray[2] == "2");
}


BOOST_AUTO_TEST_CASE(test_get_size) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(0);
    intArray.push_back(1);
    stringArray.push_back("0");
    BOOST_CHECK(intArray.get_size() == 2);
    BOOST_CHECK(stringArray.get_size() == 1);
}


BOOST_AUTO_TEST_CASE(test_get_by_index) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(0);
    intArray.push_back(1);
    intArray.push_back(2);
    stringArray.push_back("0");
    stringArray.push_back("1");
    stringArray.push_back("2");
    BOOST_CHECK(intArray[0] == 0);
    BOOST_CHECK(intArray[1] == 1);
    BOOST_CHECK(intArray[2] == 2);
    BOOST_CHECK_THROW(intArray[3], out_of_range);
    BOOST_CHECK(stringArray[0] == "0");
    BOOST_CHECK(stringArray[1] == "1");
    BOOST_CHECK(stringArray[2] == "2");
    BOOST_CHECK_THROW(stringArray[3], out_of_range);
}


BOOST_AUTO_TEST_CASE(test_erase) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(0);
    stringArray.push_back("0");
    stringArray.push_back("1");
    stringArray.push_back("2");
    stringArray.erase();
    intArray.erase();
    BOOST_CHECK(intArray.get_size() == 0);
    BOOST_CHECK(stringArray.get_size() == 2);
    BOOST_CHECK_THROW(intArray[0], out_of_range);
    BOOST_CHECK_THROW(stringArray[2], out_of_range);
    BOOST_CHECK_THROW(intArray.erase(), out_of_range);
}


BOOST_AUTO_TEST_CASE(test_del) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(0);
    intArray.push_back(1);
    intArray.push_back(2);
    stringArray.push_back("0");
    stringArray.push_back("1");
    stringArray.push_back("2");
    stringArray.del(0);
    intArray.del(1);
    BOOST_CHECK(intArray[1] == 2);
    BOOST_CHECK(stringArray[0] == "1");
    BOOST_CHECK_THROW(intArray.del(10), out_of_range);
}


BOOST_AUTO_TEST_CASE(test_operator) {
    arr<int> intArray;
    arr<string> stringArray;
    intArray.push_back(0);
    intArray.push_back(1);
    intArray.push_back(2);
    stringArray.push_back("test");
    stringArray.push_back("is");
    stringArray.push_back("passed");
    std::stringstream intStream;
    std::stringstream stringStream;
    intStream << intArray;
    stringStream << stringArray;
    BOOST_CHECK(intStream.str() == "[0, 1, 2]");
    BOOST_CHECK(stringStream.str() == "[test, is, passed]");
}


BOOST_AUTO_TEST_CASE(test_split_and_unsplit) {
    const string nums = "1 2 3";
    const arr<string> numsArray = splitToArr(nums, ' ');
    BOOST_CHECK(numsArray[0] == "1" && numsArray[1] == "2" && numsArray[2] == "3");
}