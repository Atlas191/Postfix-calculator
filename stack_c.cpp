#include<iostream>
#include<stdexcept>
using namespace std;
#include "stack_c.h"



Stack_C::Stack_C(){
        stk = new List();
    }

    // Destructor
    Stack_C::~Stack_C(){
        delete stk;
    }

    void Stack_C::push(int data){
        stk->insert(data);
    }

    int Stack_C::pop(){
        if (stk->get_size() == 0){
            throw runtime_error("Empty Stack");
        }
        return stk->delete_tail();
    }

    int Stack_C::get_element_from_top(int idx){
        if(idx<stk->get_size() && idx>=0){
        Node* temp = stk->get_head();
        int i = 0;
        while(i<stk->get_size() - idx){
            temp = temp->next;
            i++;
        } 
        return temp->get_value();
        }

        throw runtime_error("Index out of range");

    }

    int Stack_C::get_element_from_bottom(int idx){
        if (idx< stk->get_size() && idx>=0){
        Node* temp = stk->get_head();
        int i = 0;
        while(i<=idx){
            temp = temp->next;
            i++;
        } 
        return temp->get_value();}
        else{
            throw runtime_error("Index out of range");
        }
    }

    void Stack_C::print_stack(bool top_or_bottom){
        if (top_or_bottom == 0){
            Node* temp = stk->get_head();
            int i = 0;
    
            while(i<stk->get_size()){
                temp = temp->next;
                i++;
                cout<<temp->get_value()<<" ";
            } 
        }
        else {
            Node* a = stk->get_head();
            int i = 0;
            while (i<stk->get_size()){
                a = a->next;
                i++;
            }
            int j = stk->get_size();
            while(j>0){
                cout<<a->get_value()<<" ";
                a = a->prev;
                j--;
            }
        }
        cout<<endl;
    }

    int Stack_C::add(){
        if (stk->get_size()<2){
                throw runtime_error("Not Enough Arguments"); 
        }
            int num1 = this->pop();
            int num2 = this->pop();
            int sum = num1 + num2;
            // this->pop();
            // this->pop();
            this->push(sum);
            return sum;
    }

    int Stack_C::subtract(){
        if (stk->get_size()<2){
                throw runtime_error("Not Enough Arguments"); 
        }
        else{
            int num1 = this->pop();
            int num2 = this->pop();
            int diff = num2 - num1;
            // this->pop();
            // this->pop();
            this->push(diff);
            return diff;
        }
    }

    int Stack_C::multiply(){
        if (stk->get_size()<2){
                throw runtime_error("Not Enough Arguments"); 
        }
        else{
            int num1 = this->pop();
            int num2 = this->pop();
            int product = num1*num2;
            // this->pop();
            // this->pop();
            this->push(product);
            return product;
        }
    }
    int Stack_C::divide(){
        if (stk->get_size()<2){
                throw runtime_error("Not Enough Arguments"); 
        }
        else {
            if (this->get_element_from_top(0) == 0){
                throw runtime_error("Divide by Zero Error");
            }
            int num1 = this->pop();
            int num2 = this->pop();
            int quotient = num2/num1;
            if (quotient<=0 && num2%num1 != 0){
                quotient--;
            }
            // this->pop();
            // this->pop();
            this->push(quotient);
            return quotient;
        }
    }
    List* Stack_C::get_stack(){
        return stk;
    } // Get a pointer to the linked list representing the stack

    int Stack_C::get_size(){
        return stk->get_size();
    }