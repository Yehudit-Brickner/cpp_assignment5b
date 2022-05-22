#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

namespace ariel{
    

    class OrgChart{
        public:

            struct Node{
                string data;
                vector<Node *> kids;
                Node* parent;
                Node* next;

                Node(string &d) : data(d), parent(nullptr), next(nullptr){}

                Node (string &d, Node * n) : data(d), parent(n), next(nullptr){}

                ~Node(){
                    for(Node *n:kids){
                        delete(n);
                    }
                }
            };

            Node* _root;

            //constructer
            OrgChart():_root(nullptr){}
            // ~OrgChart(){
            //     queue<Node*>helper;
            //     stack<Node*>st;
            //     helper.push(this->_root);
            //     while(!helper.empty()){
            //         st.push(helper.front());
            //         getkids_q(st.top(), &helper); 
            //         helper.pop();
            //     }
            //     while(!st.empty()){
            //         delete(st.top());
            //         st.pop();
            //     }
                
            // }
            
            //create a "real root for the tree or change the string of the root
            OrgChart add_root(string s){
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


            // add a kid to one of the nodes in the tree
            // we will find the parent node and add the kid to its vector
            OrgChart add_sub(string s1,string s2){
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

            // gets the kid of a node from right to left
            void getchildren(Node* n, queue<Node*>* que){
                for (unsigned long i =0; i< n->kids.size();i++){
                    que->push(n->kids[i]);
                } 
            }


            // print the tree in a nice way
            friend ostream& operator<<(ostream& output, const OrgChart& org){
                cout<< "printing OrgChart"<<endl; 
                string s1="------------------";
                string s2="---------";
                string s3="|";
                return output;
            }
            

            class Iterator{
                private:
                Node* pointer_to_current_node;
                public:
                Iterator(Node * n){
                    pointer_to_current_node=n;   
                }
                string operator*(){
                    return pointer_to_current_node->data; 
                } 

                string* operator->(){
                    return &(pointer_to_current_node->data);
                }

                Iterator& operator++(){
                    pointer_to_current_node=pointer_to_current_node->next;
                    return *this;
                }

                Iterator operator++(int){
                    Iterator iterator= *this;
                    ++(*this);
                    return iterator; 
                }


                bool operator==(const Iterator& other) const{
                    return pointer_to_current_node == other.pointer_to_current_node;
                }

                bool operator!=(const Iterator& other) const{
                    return !(*this==other);
                }

            } ;

            void set_next__level_order(){
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


            Node* set_next__reverse_level_order(){
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

            void set_next__preorder(){
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

                  
        void getkids_q(Node* n, queue<Node*>* que){
            for (int i =n->kids.size()-1; i>=0;i--){
                que->push(n->kids[(size_t)i]);
            } 
        } 


            void getkids_st(Node* n, stack<Node*>* st){
                for (int i =n->kids.size()-1; i>=0;i--){
                    st->push(n->kids[(size_t)i]);
                } 
            }




            Iterator begin_level_order(){
                if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                set_next__level_order();
                return Iterator(this->_root);
            }

            Iterator end_level_order(){
                 if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return Iterator(nullptr);
            }

            Iterator begin_reverse_order(){
                if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return Iterator(set_next__reverse_level_order());
            }
            Iterator reverse_order(){
                 if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return Iterator(nullptr); 
            }

            Iterator begin_preorder(){
                if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                set_next__preorder();
                return Iterator(this->_root);
            }
            Iterator end_preorder(){
                 if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return Iterator(nullptr);
            }

            Iterator begin(){
                 if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return begin_level_order();
            }
            Iterator end(){
                 if(this->_root==nullptr){
                    throw std::invalid_argument( "chart is empty!" );  
                }
                return end_level_order();
            }
        

    };
            
}

  