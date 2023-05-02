#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <iostream>
#include <algorithm>

#include "MyVector_c747b428.h"

template <typename DataType>
class MyStack : private MyVector<DataType> 
{  
  public:

    // // default constructor
    explicit MyStack(size_t initSize = 0) 
    {
    }

    // // copy constructor
    MyStack(const MyStack & rhs)
    {

    }

    // // move constructor
    MyStack(MyStack && rhs)
    {
        this->theSize = rhs.theSize;
        this->theCapacity = rhs.theCapacity;
        this->data = std::move(rhs.data);
        rhs.data = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    // destructor
    ~MyStack()
    {
        ;    
    }

    // copy assignment
    MyStack & operator= (const MyStack & rhs)
    {
        MyVector<DataType>::operator=(rhs);
        return *this;
    }


    // move assignment
    MyStack & operator= (MyStack && rhs)
    {
        MyVector<DataType>::operator=(std::move(rhs));
        return *this;
    }

    // insert x to the stack
    void push(const DataType & x)
    {
        MyVector<DataType>::push_back(x);
    }

    // insert x to the stack
    void push(DataType && x)
    {
        std::cout << x << std::endl;
        MyVector<DataType>::push_back(std::move(x));
    }

    // remove the last element from the stack
    void pop(void)
    {
        if(!empty()){
            MyVector<DataType>::pop_back();
        }
    }

    // access the last element of the stack
    const DataType & top(void) const
    {
       return MyVector<DataType>::back();
    }

    // check if the stack is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        if(MyVector<DataType>::empty()){
            return true;
        }
        return false;
    }

    // access the size of the stack
    size_t size() const
    {
        return MyVector<DataType>::size();
    }

    // access the capacity of the stack
    size_t capacity(void) const 
    {
        return MyVector<DataType>::capacity();
    }

};


#endif // __MYSTACK_H__