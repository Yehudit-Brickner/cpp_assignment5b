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

OrgChart& OrgChart::add_root(string s){
    if(s.empty()){
        throw std::invalid_argument( "empty string" );    
    }
    if (this->_root==nullptr){
        this->_root=new Node(s);
        return *this; 
    }
    this->_root->data=s;
    return *this;
             
}


OrgChart& OrgChart::add_sub(string const & s1, string  s2){
    if( s1.empty() || s2.empty()){
            throw std::invalid_argument( "empty string" );    
    }
    if (this->_root==nullptr){
        throw std::invalid_argument( "the orgchart is empty" ); 
    }
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
    // throw error parent no in orgchart 
    throw std::invalid_argument( "parent is not in the orgchart" );   
}


void OrgChart::getchildren(Node* n, queue<Node*>* que){
    for (unsigned long i =0; i< n->kids.size();i++){
        que->push(n->kids[i]);
    } 
}


ostream& ariel::operator<<(ostream& output, const OrgChart& org){
    // making a queue of the nides in level order
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
    // checking what ayer it is in 
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


void OrgChart:: set_next__level_order() const{
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



Node* OrgChart::set_next__reverse_level_order() const{
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


void OrgChart::set_next__preorder() const{
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
    // for (int i =n->kids.size()-1; i>=0;i--){
    //     que->push(n->kids[(size_t)i]);
    // } 
    for (unsigned long i=n->kids.size()+1;i>1;i--){
        que->push(n->kids[i-2]);
    }
} 


void OrgChart::getkids_st(Node* n, stack<Node*>* st){
    // for (int i =n->kids.size()-1; i>=0;i--){
    //     st->push(n->kids[(size_t)i]);
    // } 
    for (unsigned long i=n->kids.size()+1;i>1;i--){
        st->push(n->kids[i-2]);
    }
}



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
