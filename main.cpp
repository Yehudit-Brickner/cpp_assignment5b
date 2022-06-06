#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

int main(){
    OrgChart dad_family;
    dad_family.add_root("grand_parents");
    dad_family.add_sub("grand_parents","uncle").add_sub("grand_parents", "aunt").add_sub("grand_parents","dad");
    dad_family.add_sub("uncle", "cousin1").add_sub("uncle", "cousin2").add_sub("uncle", "cousin3").add_sub("uncle", "cousin4");
    dad_family.add_sub("aunt","cousin5").add_sub("aunt","cousin6").add_sub("aunt","cousin7");
    dad_family.add_sub("dad","brother").add_sub("dad", "sister").add_sub("dad", "me");

    cout<<"print level_order"<<endl;
    for(auto it = dad_family.begin_level_order(); it != dad_family.end_level_order(); ++it){
        cout<< *it<<endl;
    }
    cout<<"\nprint dads family tree"<<endl;
    cout<<dad_family<<endl;
    

    OrgChart mom_family;
    mom_family.add_root("grand_parents");
    mom_family.add_sub("grand_parents","uncle1").add_sub("grand_parents", "mom").add_sub("grand_parents","uncle2");
    mom_family.add_sub("uncle1","cousin1").add_sub("uncle1","cousin3");
    mom_family.add_sub("mom","brother").add_sub("mom","sister").add_sub("mom","me");
    mom_family.add_sub("uncle2","cousin2").add_sub("uncle2","cousin4").add_sub("uncle2","cousin5");

    cout<<"\nprinting mom family with the regular iterator = like level order"<<endl; 
    for(auto it = mom_family.begin(); it != mom_family.end(); ++it){
        cout<< *it<<endl;
    }
    cout<<"\nprint moms family tree"<<endl;
    cout<<mom_family<<endl;
    cout <<endl;


    OrgChart num;
    num.add_root("numbers");
    num.add_sub("numbers", "prime");
    num.add_sub("numbers", "nonprime");
    num.add_sub("prime", "even_p");
    num.add_sub("prime", "odd_p");
    num.add_sub("nonprime", "even_np");
    num.add_sub("nonprime", "odd_np");
    num.add_sub("odd_np", "1");
    num.add_sub("even_p", "2");
    num.add_sub("odd_p", "3");
    num.add_sub("even_np", "4");
    num.add_sub("odd_p", "5");
    num.add_sub("even_np", "6");
    num.add_sub("odd_p", "7");
    num.add_sub("even_np", "8");
    num.add_sub("odd_np", "9");
    num.add_sub("even_np", "10");
    num.add_root("positive numbers");
    try{
       num.add_root("positive numbers\n"); 
    }
    catch (exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  
	}

    try{
        num.add_sub("even_np","12");
    }
     catch (exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  
	}

    cout<<"print pre_order\n"<<endl;
    for(auto it = num.begin_preorder(); it != num.end_preorder(); ++it){
        cout<< *it<<endl;
    }
    cout<<endl;
    cout<<"print reverse_level_order\n"<<endl;
    for(auto it = num.begin_reverse_order(); it != num.reverse_order(); ++it){
        cout<< *it<<endl;
    }
    cout<<" printing positive numbers OrgChart"<<endl;
    cout<<num<<endl;
    return 0;
}