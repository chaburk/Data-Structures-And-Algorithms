#ifndef __MYBINARYHEAP_H__
#define __MYBINARYHEAP_H__

#include <iostream>
#include <cstdlib>

#include "MyVector_c747b428.h"

// ComparableType should be comparable (<, >, ==, >=, <= operators implemented)
// ComparableType should also have +, +=, -, -= operators implemented to support priority adjustment

template <typename ComparableType>
class MyBinaryHeap 
{
  private:
	MyVector<ComparableType> data;  // the array that holds the data elements

    // moves the data element at the pth position of the array up
    void percolateUp(const size_t p) 
    {
        ComparableType x = std::move(data[p]);
        size_t hole = p;
        while (hole > 1 && x > data[hole / 2]) {
            data[hole] = std::move(data[hole / 2]);
            hole /= 2;
        }
        data[hole] = std::move(x);
    }

    // moves the data element at the pth position of the array down
    void percolateDown(const size_t p) 
    {
        size_t child;
        size_t hole = p;
        ComparableType tmp = std::move(data[hole]);
        for(; hole * 2 <= size(); hole = child){
            child = hole * 2;
            if(child != size() && data[child + 1] > data[child]){
                ++child;
            }
            if(data[child] > tmp){
                data[hole] = std::move(data[child]);
            } else {
                break;
            }
        }
        data[hole] = std::move(tmp);
    }

    // reorders the data elements in the array to ensure heap property
    void buildHeap() 
    {
        for(int i = size() / 2; i > 0; --i){
            percolateDown(i);
        }
    }	

  public: 

    // default constructor
    explicit MyBinaryHeap() :
        data(1)     // reserve data[0]
    {
    }

    // constructor from a set of data elements
    MyBinaryHeap(const MyVector<ComparableType>& items) : 
        data(1)     // reserve data[0]
    {
        data.reserve(items.size()+10);
        for(int i = 0; i < items.size(); ++i){
            data[i+1] = items[i];
        }
        buildHeap();
    }

    // copy constructor
    MyBinaryHeap(const MyBinaryHeap<ComparableType>& rhs)
    {
        data = rhs.data;
    }

    // move constructor
    MyBinaryHeap(MyBinaryHeap<ComparableType> && rhs)
    {
        data = std::move(rhs.data);
    }

    // copy assignment
    MyBinaryHeap& operator=(const MyBinaryHeap<ComparableType>& rhs)   
    {
        if(this != &rhs){
            data = rhs.data;
        }
        return *this;
    }

    // move assignment
    MyBinaryHeap& operator=(MyBinaryHeap<ComparableType> && rhs)
    {
        if(this != &rhs){
            data = std::move(rhs.data);
        }
        return *this;
    }

    // inserts x into the priority queue (copy)
	void enqueue(const ComparableType& x)
    {
        data.push_back(x);
        percolateUp(data.size() - 1);
    } 

    // inserts x into the priority queue (move)
    void enqueue(ComparableType && x)
    {
        data.push_back(std::move(x));
        percolateUp(data.size() - 1);
    }

    // accesses the data element with the highest priority
	const ComparableType& front()
    {
        return data[1];
    } 

    // deletes the data element with the highest priority from the queue
    void dequeue()
    {
        if(!empty()){
            std::swap(data[1], data[size()]);
            data.pop_back();
            percolateDown(1);
        }
    }

    // verifies whether the array satisfies the heap property
    bool verifyHeapProperty(void)
    {
        for (size_t i = 1; i < data.size(); ++i) {
            size_t parent = i / 2;
            if (parent >= 1 && data[i] > data[parent]) {
                return false;
            }
        }
        return true;
    }

    // disrupts heap property by random shuffling
    void disruptHeapProperty(void)
    {
        if(data.size() <= 3)
            return;
        for(size_t i = 0; i < 1000; ++ i)
        {
            size_t p = 1 + ((int) rand()) % (data.size() - 1);
            size_t q = 1 + ((int) rand()) % (data.size() - 1);
            std::swap(data[p], data[q]);
        }
        return;
    }

    // merges two heaps; the second heap can be destructed after the merge
    MyBinaryHeap& merge(MyBinaryHeap<ComparableType> && rhs) 
    {
        //if i increase the size by one then it shows up but i have one to many items
        for(int k = 1; k < rhs.size() + 1; k++){
            data.push_back(rhs.data[k]);
        }
        buildHeap();
        return *this;
    }

    // increases the priority measure of an element at a specific position and reorder the heap
	void increaseKey(const size_t p, const unsigned int d)
    {   
        data[p] += d;
        percolateUp(p);
    }

    // decreases the priority measure of an element at a specific position and reorder the heap
    // if the current priority is smaller than the requested decrement, assign priority 0
	void decreaseKey(const size_t p, const unsigned int d) 
    {
        if(data[p] < d){
            data[p] = 0;
        } else {
            data[p] -= d;
        }
        percolateDown(p);
    }

    // checks whether the heap is empty
    bool empty()
    {
        return data.size() == 1;
    }

    // removes all data elements from the heap
    void clear()
    {
        while(!empty()){
            data.pop_back();
        }
    }

    // returns the size of the heap
    size_t size()
    {
        return data.size() - 1;
    }

    // prints the data in the array
    void print() 
    {
        const char delim = '\t';
        for (size_t i = 1; i < data.size(); ++ i) {
            std::cout << data[i] << delim;
        }
        std::cout << std::endl;
        return;
    }

};

#endif // __MYBINARYHEAP_H__