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

                Node(string &d) : data(d), parent(nullptr){}

                Node (string &d, Node * n) : data(d), parent(n){}
            };

            Node* _root;

            //constructer
            OrgChart():_root(nullptr){}
            
            //create a "real root for the tree or change the string of the root
            OrgChart add_root(string s){
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
                    Node* dad=helper.front();
                    q.push(dad);
                    helper.pop();
                    getchildren(dad, &helper); 
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
            
           
            // this iterartor transverses the OrgChart by levels from top to bottom, each level in transversed from left to right
            class level_order_iterator{
                private:
                    queue<Node*> q;
                    Node* pointer_to_current_node;
                    
                public:
                    level_order_iterator(Node* n){
                        queue<Node*>helper;
                        helper.push(n);
                        while(helper.size()!=0){
                            Node* dad=helper.front();
                            this->q.push(dad);
                            helper.pop();
                            getkids(dad, &helper); 
                        }
                       pointer_to_current_node = n;
                    }

                    void getkids(Node* n, queue<Node*>* que){
                        for (unsigned long i =0; i< n->kids.size();i++){
                            que->push(n->kids[i]);
                        } 
                    }
 
                    string operator*(){
                       return this->q.front()->data; 
                    } 

                    level_order_iterator* operator->(){
                        return this;
                    }

                    level_order_iterator& operator++(){
                        this->q.pop();
                        pointer_to_current_node=q.front();
			            return *this;
                    }

                    level_order_iterator& operator++(int){
                        level_order_iterator iterator=*this;
                        ++(*this);
                        return iterator; 
                    }


                    bool operator==(const level_order_iterator& other) const{
                        return pointer_to_current_node == other.pointer_to_current_node;
                    }

                    bool operator!=(const level_order_iterator& other) const{
                        return !(*this==other);
                    }
                 
            };

            //this iterator transverses the OrgChart by levels bottom to top, each level in transversed from left to right
            class reverse_level_order_iterator{
                private:
                    Node* pointer_to_current_node;
                    stack<Node*> st;
                    
                public:
                    reverse_level_order_iterator(Node* n){
                        queue<Node*>helper;
                        helper.push(n);
                        while(helper.size()!=0){
                            Node* dad=helper.front();
                            this->st.push(dad);
                            helper.pop();
                            getkids(dad, &helper); 
                        }
                       pointer_to_current_node = n;
                    }

                    void getkids(Node* n, queue<Node*>* que){
                        for (unsigned long i =n->kids.size()-1; i>=0;i--){
                            que->push(n->kids[i]);
                        } 
                    } 

                    string operator*(){
                       return this->st.top()->data;
                    } 

                    reverse_level_order_iterator* operator->(){
                        return this;
                    }

                    reverse_level_order_iterator& operator++(){
                        this->st.pop();
                        pointer_to_current_node=st.top();
			            return *this;
                    }

                    reverse_level_order_iterator& operator++(int){
                        reverse_level_order_iterator iterator=*this;
                        ++(*this);
                        return iterator; 
                    }


                    bool operator==(const reverse_level_order_iterator& other) const{
                        return pointer_to_current_node == other.pointer_to_current_node;
                    }

                    bool operator!=(const reverse_level_order_iterator& other) const{
                        return !(*this==other);
                    }
                 
            };
            
            // this iterator transverses the OrGChart in preorder. that means that for each node it will visit the node first then its kids in order from left to right
            class preorder_iterator{
                private:
                    queue<Node*> q;
                    Node* pointer_to_current_node;
                    
                public:
                   
                    preorder_iterator(Node* n){
                        stack<Node*> helper;
                        helper.push(n);
                        while(helper.size()!=0){
                            Node* dad=helper.top();
                            this->q.push(dad);
                            getkids(dad, &helper);
                        }
                        pointer_to_current_node = n;
                    }

                    void getkids(Node* n, stack<Node*>* st){
                        for (unsigned long i =n->kids.size()-1; i>=0;i--){
                            st->push(n->kids[i]);
                        } 
                    }
                    
                    string operator*(){
                       return this->q.front()->data; 
                    } 

                    preorder_iterator* operator->(){
                        return this;
                    }

                    preorder_iterator& operator++(){
                        this->q.pop();
                        pointer_to_current_node=this->q.front();
			            return *this;
                    }

                    preorder_iterator& operator++(int){
                        preorder_iterator iterator=*this;
                        ++(*this);
                        return iterator; 
                    }


                     bool operator==(const preorder_iterator& other) const{
                        return pointer_to_current_node == other.pointer_to_current_node;
                    }

                    bool operator!=(const preorder_iterator& other) const{
                        return !(*this==other);
                    }
            };

            level_order_iterator begin_level_order(){
               return level_order_iterator(this->_root);
            }
            level_order_iterator end_level_order(){
                Node* n =nullptr;
                return level_order_iterator(n);
            }

            reverse_level_order_iterator begin_reverse_order(){ 
                return reverse_level_order_iterator(this->_root);
            }
            reverse_level_order_iterator reverse_order(){
                Node* n =nullptr;
                return reverse_level_order_iterator(n); 
            }

            preorder_iterator begin_preorder(){
                return preorder_iterator(this->_root);
            }
            preorder_iterator end_preorder(){
                Node* n =nullptr;
                return preorder_iterator(n);
            }

            level_order_iterator begin(){
                return begin_level_order();
            }
            level_order_iterator end(){
                return end_level_order();
            }
        

    };
            
}

  