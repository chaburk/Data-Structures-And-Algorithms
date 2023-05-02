#include <iostream>
#include "MyLinkedList_c747b428.h"

int main(){
    MyLinkedList<int> l1;
    MyLinkedList<int> l2;

    for(int i = 0; i < 5; ++i){
        l1.push_back(i);
        std::cout << l1.back() << std::endl;
    }
    std::cout << std::endl;
    for(int i = 0; i < 10; i+=2){
        l2.push_back(i);
        std::cout << l2.back() << std::endl;
    }


    //Intersection
    MyLinkedList<int> intersection;
    MyLinkedList<int>::iterator itr = l1.begin();
    MyLinkedList<int>::iterator itr2 = l2.begin();
    while( itr != l1.end() || itr2 != l2.end()){
        if(*){
            ++itr;
        }
        else if(l1.size() > l2.size()){
            ++itr2;
        }
        else{
            if(*itr == *itr2){
                intersection.push_back(*itr);
                ++itr;
                ++itr2;
            }
        }
    }

    std::cout << std::endl;

    for(int i = 0; i < intersection.size(); ++i){
        std::cout << intersection.front() << std::endl;
        intersection.pop_front();
    }

    return 0;
}