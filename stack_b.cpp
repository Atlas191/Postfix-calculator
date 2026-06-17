#include<iostream>
#include<stdexcept>
#include "stack_b.h"
using namespace std;

Stack_B ::Stack_B(){
            capacity = 1024;
            stk = new int[1024];
            size = 0;
        }
        // void Grow(){
        //     int *newarr = new int[2*capacity];//creating a new array
        //         //copying elements:-
        //         for(int i = 0;i<capacity;i++){
        //             newarr[i] = stk[i];
        //         }
        //         delete [] stk;
        //         stk = newarr;
        //         newarr = NULL;
        //         capacity = capacity*2;
        // }
        // void Shrink(){
        //     int *newarr2 = new int [capacity/2];
        //         for (int i = 0;i<size;i++){
        //             newarr2[i] = stk[i];
        //         }
        //         delete [] stk;
        //         stk = newarr2;
        //         newarr2 = NULL;
        //         capacity = capacity/2;
        // }
        // Destructor
        Stack_B ::~Stack_B(){
            delete [] stk;
        }

        void Stack_B ::push(int data){
            if (size>capacity-1){
                int *newarr = new int[2*capacity];//creating a new array
                //copying elements:-
                for(int i = 0;i<capacity;i++){
                    newarr[i] = stk[i];
                }
                delete [] stk;
                stk = newarr;
                newarr = NULL;
                capacity = capacity*2;
            }
            stk[size] = data;
            size += 1;
        }
        int Stack_B ::pop(){
            if (capacity>=2048 && size<=capacity/4){
              
                int *newarr2 = new int [capacity/2];
                for (int i = 0;i<size;i++){
                    newarr2[i] = stk[i];
                }
                delete [] stk;
                stk = newarr2;
                newarr2 = NULL;
                capacity = capacity/2;
        
            }
            
                if (size>0){
                    size -= 1;
                    return stk[size];
                }
                else{
                    throw runtime_error("Empty Stack");
                }
            
        }
        int Stack_B ::get_element_from_top(int idx){
            if (idx>size-1){
                throw runtime_error("Index out of range");
            }
            else{
                return stk[size - idx - 1];
            }
        }
        int Stack_B ::get_element_from_bottom(int idx){
            if (idx>=size){
                throw runtime_error("Index out of range");
            }
            else {
                return stk[idx];
            }
        }
        void Stack_B ::print_stack(bool top_or_bottom){
            if (size == 0){
                return ;
            }
            else{
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
        }
        int Stack_B :: add(){
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
        int Stack_B ::subtract(){
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
        int Stack_B ::multiply(){
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
        int Stack_B ::divide(){
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
        int* Stack_B ::get_stack(){
            return stk;
        }
        int Stack_B ::get_size(){
            return size;
        }