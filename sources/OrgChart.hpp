#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

namespace ariel{
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

    class OrgChart{
        public:
            Node* _root;

            //constructer
            OrgChart():_root(nullptr){}
            ~OrgChart(){}
            
            //     // queue<Node*>helper;
            //     // stack<Node*>st;
            //     // helper.push(this->_root);
            //     // while(!helper.empty()){
            //     //     st.push(helper.front());
            //     //     getkids_q(st.top(), &helper); 
            //     //     helper.pop();
            //     // }
            //     // while(!st.empty()){
            //     //     delete(st.top());
            //     //     st.pop();
            //     // } 
            
            
            //create a "real root for the tree or change the string of the root
            OrgChart add_root(string s);
          


            // add a kid to one of the nodes in the tree
            // we will find the parent node and add the kid to its vector
            OrgChart add_sub(string s1,string s2);
        
           

            // gets the kid of a node from right to left
            void getchildren(Node* n, queue<Node*>* que);
  


            // print the tree in a nice way
            friend ostream& operator<<(ostream& output, const OrgChart& org);
  
            

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

        void set_next__level_order();
                

        Node* set_next__reverse_level_order();
        

        void set_next__preorder();
         
         
        void getkids_q(Node* n, queue<Node*>* que);
      

        void getkids_st(Node* n, stack<Node*>* st);
       


        Iterator begin_level_order();
        // {
        //     if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     set_next__level_order();
        //     return Iterator(this->_root);
        // }

        Iterator end_level_order();
        // {
        //         if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return Iterator(nullptr);
        // }

        Iterator begin_reverse_order();
        // {
        //     if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return Iterator(set_next__reverse_level_order());
        // }

        Iterator reverse_order();
        // {
        //         if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return Iterator(nullptr); 
        // }

        Iterator begin_preorder();
        // {
        //     if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     set_next__preorder();
        //     return Iterator(this->_root);
        // }

        Iterator end_preorder();
        // {
        //         if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return Iterator(nullptr);
        // }

        Iterator begin();
        // {
        //         if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return begin_level_order();
        // }

        Iterator end();
        // {
        //         if(this->_root==nullptr){
        //         throw std::invalid_argument( "chart is empty!" );  
        //     }
        //     return end_level_order();
        // }
        

    };
            
}

  