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


        Node &operator=(Node const &other) = default;
        Node &operator=(Node &&other) = default;
        Node(Node&) = default;
        Node(Node&&) = default;
        

        ~Node(){
           for (unsigned long i=0; i<this->kids.size();i++){
                delete(this->kids[i]);
            }
        }
    };

    class OrgChart{
        public:
            Node* _root;

            //constructer
            OrgChart():_root(nullptr){}
            ~OrgChart(){
                delete(this->_root); 
            }

           
            // function needed for a smart pointer???
            OrgChart &operator=(OrgChart const &other) = default;
            OrgChart &operator=(OrgChart &&other) = default;
            OrgChart(OrgChart&) = default;
            OrgChart(OrgChart&&) = default;

            //create a "real root for the tree or change the string of the root
            OrgChart& add_root(string s);
          

            // add a kid to one of the nodes in the tree
            // we will find the parent node and add the kid to its vector
            OrgChart& add_sub(string const & s1,string s2);
        


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

        void set_next__level_order() const;
                
        Node* set_next__reverse_level_order()const;
        
        void set_next__preorder()const;

        // gets the kid of a node from right to left
        static void getchildren(Node* n, queue<Node*>* que);

        // get the kids of a node from left to right 
        static void getkids_q(Node* n, queue<Node*>* que);

        // get kids of a node from left to right
        static void getkids_st(Node* n, stack<Node*>* st);
       

        // get the begining and end of the iterator
        Iterator begin_level_order()const;
        Iterator end_level_order() const;
    
        Iterator begin_reverse_order()const ;
        Iterator reverse_order() const;

        Iterator begin_preorder()const ;
        Iterator end_preorder() const;
        
        
        // works like a level order
        Iterator begin()const ;
        Iterator end() const;
      
        

    };
            
}

  