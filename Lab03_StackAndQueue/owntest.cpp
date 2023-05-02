#include <iostream>
//#include "MyStack_c747b428.h"
#include "MyQueue_c747b428.h"

int main(){

    MyQueue<int> q;
    for(int i = 0; i < 8; ++i){
        q.enqueue(i);
        std::cout << "this is i: " << i << std::endl;
        std::cout << "this is value enqueuing: " << q.back() << std::endl;
        std::cout << "this is size: " << q.size() << std::endl;
        std::cout << "this is capactiy: " << q.capacity() << std::endl;
    }
    for(int i = 0; i < 3; ++i){
        q.dequeue();
        std::cout << "is dequeuing " << q.front() << std::endl;
        std::cout << "dequeuing size" << q.size() << std::endl;
        std::cout << std::endl;
    }
    for(int i = 0; i < 10; ++i){
        q.enqueue(i);
        std::cout << "this is i: " << i << std::endl;
        std::cout << "this is value enqueuing: " << q.back() << std::endl;
        std::cout << "this is size: " << q.size() << std::endl;
        std::cout << "this is capactiy: " << q.capacity() << std::endl;
        std::cout << "this is dataEnd outside queue:" << q.printEnd() << std::endl;
    }

    return 0;
}