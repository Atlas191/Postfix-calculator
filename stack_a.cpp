#include<iostream>
#include<stdexcept>
#include "stack_a.h"
using namespace std;

Stack_A :: Stack_A(){
        size = 0;
        }
void Stack_A :: push(int data){
            if (size<1024){
                stk[size] = data;
                size += 1;
            }
            else{
                throw runtime_error("Stack Full");
            }
        }
int Stack_A :: pop(){
            if (size>0){
                size -= 1;
                return stk[size];
            }
            else{
                throw runtime_error("Empty Stack");
            }
        }

        int Stack_A ::get_element_from_top(int idx){
            if (idx>size-1){
                throw runtime_error("Index out of range");
            }
            else{
                return stk[size - idx - 1];
            }
        }

        int Stack_A ::get_element_from_bottom(int idx){
            if (idx>=size){
                throw runtime_error("Index out of range");
            }
            else {
                return stk[idx];
            }
        }

        void Stack_A ::print_stack(bool top_or_bottom){
            if (top_or_bottom == 0){
                for (int i = 0;i<size ;i++){
                    cout<<stk[i]<<endl;
                }
            }
            else{
                for (int i = size - 1;i>=0;i-=1){
                    cout<<stk[i]<<endl;
                }
            }
        }

        int Stack_A ::add(){
            if (size<2){
                throw runtime_error("Not Enough Arguments"); 
            }
            else {
                int sum;
                sum = stk[size - 1] + stk[size - 2];
                size -= 2;
                this->push(sum);
                return sum;
            }
        }

        int Stack_A ::subtract(){
            if (size<2){
                throw runtime_error("Not Enough Arguments"); 
            }
            else {
                int diff;
                diff = stk[size - 2] - stk[size - 1];
                size -= 2;
                this->push(diff);
                return diff;
            }
        }

        int Stack_A ::multiply(){
            if (size<2){
                throw runtime_error("Not Enough Arguments"); 
            }
            else {
                int product;
                product = stk[size - 1]*stk[size - 2];
                size -= 2;
                this->push(product);
                return product;
            }
        }

        int Stack_A ::divide(){
            if (size<2){
                throw runtime_error("Not Enough Arguments"); 
            }
            else {
                if (stk[size - 1] == 0){
                    throw runtime_error("Divide by Zero Error");
                }
                int dividend = stk[size - 2];
                int divisor = stk[size - 1];
                int quotient = dividend / divisor;
                size -= 2;
                if(quotient<=0 && dividend % divisor != 0){
                    quotient--;
                }
                this->push(quotient);

                return quotient;
            }
        }

        int* Stack_A ::get_stack(){ // Get a pointer to the array
            return stk;
        }

        int Stack_A ::get_size(){ // Get the size of the stack
            return size;
        }


