#include<iostream>
#include<stdexcept>
#include"list.h"
using namespace std;

List::List(){
        sentinel_head = new Node(true);
        sentinel_tail = new Node(true);
        sentinel_head->next = sentinel_tail;
        sentinel_tail->prev = sentinel_head;
        sentinel_head->prev = nullptr;
        sentinel_tail->next = nullptr;
    }
    List::~List(){
        Node* temp4 = sentinel_head;
        while(temp4 != nullptr){
            Node* temp5 = temp4;
            temp4 = temp4->next;
            delete temp5;
        }
    }
    // Insert an element at the tail of the linked list 
    void List::insert(int v){
        Node *p = new Node(v,sentinel_tail,sentinel_tail->prev);
        sentinel_tail->prev->next = p;
        sentinel_tail->prev = p;
    }

    // Delete the tail of the linked list and return the value
    // You need to delete the valid tail element, not the sentinel
    int List::delete_tail(){
        if (sentinel_tail->prev == sentinel_head){
            throw runtime_error("Empty List");
        }
        int temp1 = sentinel_tail->prev->get_value();
        Node* temp2 = sentinel_tail->prev;
        sentinel_tail->prev = sentinel_tail->prev->prev;
        temp2->prev->next = sentinel_tail;
        temp2->next=nullptr;
        temp2->prev=nullptr;
        delete temp2;
        return temp1;
    }

    // Return the size of the linked list 
    // Do not count the sentinel elements
    int List::get_size(){
        Node* temp3 = sentinel_head->next;
        if (sentinel_head->next != sentinel_tail){
        int count = 1;
        while (temp3->next!=sentinel_tail){
            temp3 = temp3->next;
            count += 1;
        }
        return count;}
        else{
            return 0;
        }
    }
    // Return a pointer to the sentinel head of the linked list 
    Node* List::get_head(){
        return sentinel_head;
    }
    