#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>

#include "MyVector_c747b428.h"

template <typename DataType>
class MyQueue : protected MyVector<DataType>
{  
  private:
    size_t dataStart = 0, dataEnd = 0;

    // changes the size of the array to newSize
    void resize(size_t newSize, size_t start, size_t end)
    {
        MyVector<DataType>::resize(newSize, start, end);
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity, size_t start, size_t end)
    {
        MyVector<DataType>::reserve(newCapacity, start, end);
    }

  public:

    // default constructor
    explicit MyQueue(size_t initSize = 0)
    {
        // this->theSize = initSize;
        // this->theCapacity = initSize + this->SPARE_CAPACITY;
        // dataStart = 0;
        // dataEnd = 0;
        // this->data = new DataType[this->theCapacity];
    }

    // // copy constructor
    MyQueue(const MyQueue & rhs)
    {
        // this->theSize = rhs.theSize;
        // this->theCapacity = rhs.theCapacity;
        // this->data = new DataType[this->theCapacity];
        // for(int k = 0; k < this->theSize; ++k){
        //     this->data[k] = rhs.data[k];
        // }
        // dataStart = 0;
        // dataEnd = 0;
    }

    // // move constructor
    MyQueue(MyQueue && rhs)
    {
        // this->theSize =  rhs.theSize;
        // this->theCapacity = rhs.theCapacity;
        // this->data = rhs.data;
        // dataStart = 0;
        // dataEnd = 0;
        // rhs.data = nullptr;
        // rhs.theSize = 0;
        // rhs.theCapacity = 0;
    }

    // // destructor
    ~MyQueue()
    {
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs)
    {
        MyVector<DataType>::operator=(rhs);
        return *this;
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs)
    {
        MyVector<DataType>::operator=(std::move(rhs));
        return *this;
    }

    // insert x into the queue
    void enqueue(const DataType & x)
    {
        if(empty()){
            dataStart = 0;
            dataEnd = 0;
        }
        std::cout << "this is dataEnd in basic enqueue: " << dataEnd << std::endl;
        if(isFull()){
            std::cout << "isfull" << std::endl;
            dataEnd = size();
            resize(size() + 1, dataStart, dataEnd);
            std::cout << "this is dataStart in full enqueue: " << dataStart << std::endl;
            std::cout << "this is dataEnd in full enqueue: " << dataEnd << std::endl;
            MyVector<DataType>::operator[](dataEnd) = x;
            dataStart = 0;
            dataEnd += 1;
            this->theSize += 1;
        }
        else if(dataEnd > capacity() && !isFull()){
            std::cout << "wrap around" << std::endl;
            dataEnd = 0;
            std::cout << "this is dataStart in wrap around: " << dataStart << std::endl;
            std::cout << "this is dataEnd in wrap around: " << dataEnd << std::endl;
            MyVector<DataType>::operator[](dataEnd) = x;
            dataEnd += 1;
            this->theSize += 1;
            std::cout << "this is dataEnd in wrap around after: " << dataEnd << std::endl;
            std::cout << "this is size in wrap around after: " << size() << std::endl;
        }
        else{
            std::cout << "this is dataStart in normal enqueue: " << dataStart << std::endl;
            std::cout << "this is dataEnd in normal enqueue: " << dataEnd << std::endl;
            MyVector<DataType>::operator[](dataEnd) = x;
            dataEnd += 1;
            this->theSize += 1;
        }
        std::cout << std::endl;

    }

    int printEnd(void){
        return dataEnd;
    }

    // insert x into the queue
    void enqueue(DataType && x)
    {
        std::cout << "something" << std::endl;
        if(empty()){
            dataStart = 0;
            dataEnd = 0;
        }
        if(isFull()){
            dataEnd = size() + 1;
            resize(size() + 1, dataStart, dataEnd);
            MyVector<DataType>::operator[](dataEnd) = std::move(x);
            dataStart = 0;
            dataEnd += 1;
        }
        else if(dataEnd > capacity() && !isFull()){
            dataEnd = 0;
            MyVector<DataType>::operator[](dataEnd) = std::move(x);
            this->theSize += 1;
        }
        else{
            MyVector<DataType>::operator[](dataEnd) = std::move(x);
            dataEnd += 1;
            this->theSize += 1;
        }

    }

    // remove the first element from the queue
    void dequeue(void)
    {
        if(!empty()){
            if(dataStart == (size() - 1)){
                dataStart = 0;
                if(dataEnd > capacity()){
                    dataEnd = 0;
                }
                this->theSize--;
            }else {
                dataStart += 1;
                this->theSize--;
            }
        }
    }

    // access the first element of the queue
    const DataType & front(void) const
    {
        return MyVector<DataType>::operator[](dataStart);
    }

    const DataType & back(void) const
    {
        return MyVector<DataType>::back();
    }

    // check if the queue is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        if(MyVector<DataType>::empty()){
            return true;
        }
        return false;
    }

    bool isFull(void) const{
        if(size() == capacity()){
            return true;
        }
        return false;
    }

    // access the size of the queue
    size_t size() const
    {
        return MyVector<DataType>::size();
    }

    // access the capacity of the queue
    size_t capacity(void) const 
    {
        return MyVector<DataType>::capacity();
    }

};


#endif // __MYQUEUE_H__