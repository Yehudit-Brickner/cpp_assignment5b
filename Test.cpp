#include "doctest.h"
#include "OrgChart.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace ariel;

TEST_CASE("test1"){

    OrgChart num;
    CHECK_NOTHROW(num.add_root("numbers"));
    CHECK_NOTHROW(num.add_sub("numbers", "prime"));
    CHECK_NOTHROW(num.add_sub("numbers", "nonprime"));
    CHECK_NOTHROW(num.add_sub("prime", "even_p"));
    CHECK_NOTHROW(num.add_sub("prime", "odd_p"));
    CHECK_NOTHROW(num.add_sub("nonprime", "even_np"));
    CHECK_NOTHROW(num.add_sub("nonprime", "odd_np"));
    CHECK_NOTHROW(num.add_sub("odd_np", "1"));
    CHECK_NOTHROW(num.add_sub("even_p", "2"));
    CHECK_NOTHROW(num.add_sub("odd_p", "3"));
    CHECK_NOTHROW(num.add_sub("even_np", "4"));
    CHECK_NOTHROW(num.add_sub("odd_p", "5"));
    CHECK_NOTHROW(num.add_sub("even_np", "6"));
    CHECK_NOTHROW(num.add_sub("odd_p", "7"));
    CHECK_NOTHROW(num.add_sub("even_np", "8"));
    CHECK_NOTHROW(num.add_sub("odd_np", "9"));
    CHECK_NOTHROW(num.add_sub("even_np", "10"));
    CHECK_THROWS(num.add_sub("even_np","\n12"));
    CHECK_THROWS(num.add_sub("even_np","\r14"));


    string levelord="";
    for (auto it = num.begin_level_order(); it != num.end_level_order(); ++it){
        levelord.append(*it);
        levelord.push_back(' ');
    }
    string levelord1 = "numbers prime nonprime even_p odd_p even_np odd_np 2 3 5 7 4 6 8 10 1 9 ";
    CHECK(levelord1==levelord);


    string reverselevelord="";
    for (auto it = num.begin_reverse_order(); it != num.reverse_order(); ++it){
        reverselevelord.append(*it);
        reverselevelord.push_back(' ');
    } 
    string reverselevelord1="2 3 5 7 4 6 8 10 1 9 even_p odd_p even_np odd_np prime nonprime numbers ";
    CHECK(reverselevelord1==reverselevelord);

    string preorder="";
    for (auto it=num.begin_preorder(); it!=num.end_preorder(); ++it) {
        preorder.append(*it);
        preorder.push_back(' ');
    } 
    string preorder1="numbers prime even_p 2 odd_p 3 5 7 nonprime even_np 4 6 8 10 odd_np 1 9 ";
    CHECK(preorder1==preorder);

    cout << num << endl;


    CHECK_THROWS(num.add_root("positive \n numbers"));
    CHECK_NOTHROW(num.add_root("positive_numbers"));


    levelord="";
    for (auto it = num.begin_level_order(); it != num.end_level_order(); ++it){
        levelord.append(*it);
        levelord.push_back(' ');
    }
    levelord1 = "positive_numbers prime nonprime even_p odd_p even_np odd_np 2 3 5 7 4 6 8 10 1 9 ";
    CHECK(levelord1==levelord);


    reverselevelord="";
    for (auto it = num.begin_reverse_order(); it != num.reverse_order(); ++it){
        reverselevelord.append(*it);
        reverselevelord.push_back(' ');
    } 
    reverselevelord1="2 3 5 7 4 6 8 10 1 9 even_p odd_p even_np odd_np prime nonprime positive_numbers ";
    CHECK(reverselevelord1==reverselevelord);

    preorder="";
    for (auto it=num.begin_preorder(); it!=num.end_preorder(); ++it) {
        preorder.append(*it);
        preorder.push_back(' ');
    } 
    preorder1="positive_numbers prime even_p 2 odd_p 3 5 7 nonprime even_np 4 6 8 10 odd_np 1 9 ";
    CHECK(preorder1==preorder);

    cout << num << endl;
}

