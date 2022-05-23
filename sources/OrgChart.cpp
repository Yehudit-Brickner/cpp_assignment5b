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

OrgChart OrgChart::add_root(string s){
    if( s.empty()){
        throw std::invalid_argument( "empty string" );    
    }
    if (this->_root==nullptr){
        this->_root=new Node(s);
    }
    else{
        this->_root->data=s;
    }
    return *this;      
}


OrgChart OrgChart::add_sub(string s1,string s2){
    if( s1.empty() || s2.empty()){
            throw std::invalid_argument( "empty string" );    
    }
    if (this->_root==nullptr){
        throw std::invalid_argument( "the orgchart is empty" ); 
    }
    queue<Node*> q;
    queue<Node*>helper;
    helper.push(this->_root);
    while(helper.size()!=0){
        if (helper.front()->data==s1){
            helper.front()->kids.push_back(new Node (s2, helper.front()));
            return *this;
        }
        q.push(helper.front());
        getchildren(helper.front(), &helper); 
        helper.pop();
    }
    // throw error parent no in orgchart 
    throw std::invalid_argument( "parent is not in the orgchart" );   
}


void OrgChart::getchildren(Node* n, queue<Node*>* que){
    for (unsigned long i =0; i< n->kids.size();i++){
        que->push(n->kids[i]);
    } 
}


ostream& ariel::operator<<(ostream& output, const OrgChart& org){
    cout<< "printing OrgChart"<<endl; 
    string s1="------------------";
    string s2="---------";
    string s3="|";
    return output;
}


void OrgChart:: set_next__level_order(){
    queue<Node*>q;
    queue<Node*>helper;
    helper.push(this->_root);
    while(!helper.empty()){
        q.push(helper.front());
        getchildren(helper.front(), &helper); 
        helper.pop();
        if(!helper.empty()){
            q.front()->next = helper.front();
            q.pop();                   
        }
        else{
            q.front()->next=nullptr;
            q.pop();  
        }
    }
}



Node* OrgChart::set_next__reverse_level_order(){
    queue<Node*>helper;
    stack<Node*>st;
    helper.push(this->_root);
    while(!helper.empty()){
        st.push(helper.front());
        getkids_q(st.top(), &helper); 
        helper.pop();
    }
    Node * beginig_of_iter=st.top();
    while(!st.empty()){
        helper.push(st.top());
        st.pop();
        if(!st.empty()){
            helper.front()->next=st.top();
            helper.pop();
        }
        else{
            helper.front()->next=nullptr;
            helper.pop();
        }
    }
    return beginig_of_iter; 
}




void OrgChart::set_next__preorder(){
    stack<Node*> helper;
    queue<Node*> q;
    helper.push(this->_root);
    while(!helper.empty()){
        q.push(helper.top());
        helper.pop();
        getkids_st(q.front(), &helper);
        if(!helper.empty()){
            q.front()->next = helper.top();
            q.pop();                   
        }
        else{
            q.front()->next = nullptr;
            q.pop();
        }
    }    
}


void OrgChart::getkids_q(Node* n, queue<Node*>* que){
    for (int i =n->kids.size()-1; i>=0;i--){
        que->push(n->kids[(size_t)i]);
    } 
} 


void OrgChart::getkids_st(Node* n, stack<Node*>* st){
    for (int i =n->kids.size()-1; i>=0;i--){
        st->push(n->kids[(size_t)i]);
    } 
}
