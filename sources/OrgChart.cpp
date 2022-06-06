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

// create/update the root of the OrgChart
OrgChart& OrgChart::add_root(string s){
    // if the string is empty or contains illegal char we will throw an exception
    const int onetwosix=126;
    const int threetwo=32;
    if(s.empty()){
        throw std::invalid_argument( "empty string" );    
    }
    for (unsigned long i=0; i<s.length();i++){
        if(s[i]< threetwo || s[i]>onetwosix){
            throw std::invalid_argument( "string contains illegal char" );  
        }
    }
    // if the root is a nullptr we will create a new node with the string     
    if (this->_root==nullptr){
        this->_root=new Node(s);
        return *this; 
    }
    // if the root isnt a null poiner we will change the string of the node
    this->_root->data=s;
    return *this;
             
}

// add a leaf to the OrgChart
OrgChart& OrgChart::add_sub(string const & s1, string  s2){
    // if the either string is empty or the orgchart root is a nullptr or s2 contains illegal char we will throw an exception
    const int onetwosix=126;
    const int threetwo=32;
    if( s1.empty() || s2.empty()){
            throw std::invalid_argument( "empty string" );    
    }
    if (this->_root==nullptr){
        throw std::invalid_argument( "the orgchart is empty" ); 
    }
    
    for (unsigned long i=0; i<s2.length();i++){
        if(s2[i]< threetwo || s2[i]>onetwosix){
            throw std::invalid_argument( "string contains illegal char" );  
        }
    } 
    // we will look for the parent node
    // once we found it we will add to the parnets vector a pointer to a the kids new node 
    queue<Node*> q;
    queue<Node*>helper;
    helper.push(this->_root);
    while(!helper.empty()){
        if (helper.front()->data==s1){
            helper.front()->kids.push_back(new Node (s2, helper.front()));
            return *this;
        }
        q.push(helper.front());
        getchildren(helper.front(), &helper); 
        helper.pop();
    }
    // if we went through the whole OrgChrart and didint find the parent we will throw an error
    throw std::invalid_argument( "parent is not in the orgchart" );   
}

// print the OrgChart 
ostream& ariel::operator<<(ostream& output, const OrgChart& org){
    // making a queue of the nodes in level order
      cout<< "printing OrgChart"<<endl; 
    
    queue<Node*>q;
    queue<Node*>helper;
    helper.push(org._root);
    while(!helper.empty()){
        q.push(helper.front());
        OrgChart::getchildren(helper.front(), &helper); 
        helper.pop();
    }
    // going threw the nodes
    // checking what layer it is in 
    // printing  at the beging if the layer what the layer is 
    // then printing each node - their parent and kids
    int level =0;
    output<<"level "<< level<< "\n";
    while (!q.empty()){
        if(q.front()->parent!=nullptr){
            int count=0;
            Node *kid=q.front();
            while(kid->parent!=nullptr){
                kid=kid->parent;
                count++;
            }
            if (count!=level){
                level=count;
                output<< "level "<< level <<"\n";
            }
        }
        if(q.front()->parent!=nullptr)  {
            output <<"node: "<< q.front()->data <<"," << "   parent: " << q.front()->parent->data<< ",";
        }
        else{
            output <<"node: "<< q.front()->data <<",";
        }
        if(!q.front()->kids.empty()){
            output << " kids:   "; 
            for (unsigned long i=0; i<q.front()->kids.size(); i++){
                output<<q.front()->kids[i]->data<< ",  ";
            }
        }
        output<<"\n";
        q.pop();
        }
  
    return output;
}

// sets the next of all the nodes for level order using BFS
void OrgChart:: set_next__level_order() const{
    // usng 2 queues we will create a queue of the whole OrgChart using BFS
    queue<Node*>q;
    queue<Node*>helper;
    helper.push(this->_root);
    while(!helper.empty()){
        q.push(helper.front());
        getchildren(helper.front(), &helper); 
        helper.pop();
        // setting the next for each node
        if(!helper.empty()){
            q.front()->next = helper.front();
            q.pop();                   
        }
        // the last nodes next is nullptr
        else{
            q.front()->next=nullptr;
            q.pop();  
        }
    }
}

// sets the next of all the nodes for reverse level order using BFS
Node* OrgChart::set_next__reverse_level_order() const{
    // using a stack and a queue we will create a stack of the whole OrgChart using BFS 
    // form the right most kids to the left most kids
    
    queue<Node*>helper;
    stack<Node*>st;
    helper.push(this->_root);
    while(!helper.empty()){
        st.push(helper.front());
        getkids_q(st.top(), &helper); 
        helper.pop();
    }
    // the top of the stack is the beging of the iterator 
    Node * beginig_of_iter=st.top();
    // we will set the next for all the nodes
    while(!st.empty()){
        helper.push(st.top());
        st.pop();
        if(!st.empty()){
            helper.front()->next=st.top();
            helper.pop();
        }
        // the last nodes next is nullptr
        else{
            helper.front()->next=nullptr;
            helper.pop();
        }
    }
    return beginig_of_iter; 
}

// sets the next of all the nodes for preorder using DFS
void OrgChart::set_next__preorder() const{
    // using a queue and a stack we will create a queue of the whole OrgChart using DFS
    // form the right most kids to the left most kids

    stack<Node*> helper;
    queue<Node*> q;
    helper.push(this->_root);
    while(!helper.empty()){
        q.push(helper.top());
        helper.pop();
        getkids_st(q.front(), &helper);
        // setting the next for each node
        if(!helper.empty()){
            q.front()->next = helper.top();
            q.pop();                   
        }
        // the last nodes next is nullptr
        else{
            q.front()->next = nullptr;
            q.pop();
        }
    }    
}

// add the kids of a node to the queue from the left most kid to the right most kid
void OrgChart::getchildren(Node* n, queue<Node*>* que){
    for (unsigned long i =0; i< n->kids.size();i++){
        que->push(n->kids[i]);
    } 
}

// add the kids of a node to the queue from the right most kid to the left most kid
void OrgChart::getkids_q(Node* n, queue<Node*>* que){
    for (unsigned long i=n->kids.size()+1;i>1;i--){
        que->push(n->kids[i-2]);
    }
} 

// add the kids of a node to the stack from the right most kid to the left most kid
void OrgChart::getkids_st(Node* n, stack<Node*>* st){
    for (unsigned long i=n->kids.size()+1;i>1;i--){
        st->push(n->kids[i-2]);
    }
}


// set all of the next by calling the correct set function and return the pointer to the beging and end node of the iterators.
OrgChart::Iterator OrgChart::begin_level_order()const{
    if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    set_next__level_order();
    return Iterator(this->_root);
}

OrgChart::Iterator OrgChart::end_level_order()const{
        if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin_reverse_order()const{
    if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return Iterator(set_next__reverse_level_order());
}

OrgChart::Iterator OrgChart::reverse_order()const{
        if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return Iterator(nullptr); 
}

OrgChart::Iterator OrgChart::begin_preorder()const{
    if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    set_next__preorder();
    return Iterator(this->_root);
}

OrgChart::Iterator OrgChart::end_preorder()const{
        if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin()const{
        if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return begin_level_order();
}

OrgChart::Iterator OrgChart::end()const{
        if(this->_root==nullptr){
        throw std::invalid_argument( "chart is empty!" );  
    }
    return end_level_order();
}
