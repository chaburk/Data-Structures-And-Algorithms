#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <utility>
#include <vector>

using namespace std;

template <typename DataType>
class MyVector
{
  protected:
    /* data */
    size_t theSize;                         // the number of data elements the vector is currently holding
    size_t theCapacity;                     // maximum data elements the vector can hold
    DataType *data;                         // address of the data storage

  public:
    
    static const size_t SPARE_CAPACITY = 16;   // initial capacity of the vector

    // default constructor
    explicit MyVector(size_t initSize = 0) : 
        theSize{initSize},
        theCapacity{initSize + SPARE_CAPACITY}
    {
        data = new DataType[theCapacity]; 
    }

    // copy constructor
    MyVector(const MyVector & rhs) : 
        theSize{rhs.theSize},
        theCapacity{rhs.theCapacity}
    {
        data = new DataType[theCapacity];
        for(int k = 0; k < theSize; ++k){
            data[k] = rhs.data[k];
        }
    }

    // move constructor
    MyVector(MyVector&& rhs):
        theSize{rhs.theSize},
        theCapacity{rhs.theCapacity},
        data{rhs.data}
    {
        rhs.data = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    // copy constructor from STL vector implementation
    MyVector(const std::vector<DataType> & rhs) :
        theSize{rhs.size()},
        theCapacity{rhs.size() + SPARE_CAPACITY}
    {
        data = new DataType[theCapacity];
        for(int k =0; k < theSize; ++k){
            data[k] = rhs[k];
        }
    }

    // destructor
    ~MyVector(){
        delete [] data;
    };

    // copy assignment
    MyVector & operator= (const MyVector& rhs)
    {
        MyVector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // move assignment
    MyVector & operator= (MyVector && rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(data, rhs.data);

        return *this;
    }

    // change the size of the array
    void resize(size_t newSize, size_t start, size_t end)
    {
        if(newSize > theCapacity){
            reserve(newSize * 2, start, end);
        }
        theSize = newSize;
    }

    // void reserve(size_t newCapacity)
    // {
    //     if(newCapacity < theSize){
    //         return;
    //     }  
    //     DataType *newArray = new DataType[newCapacity];
    //     for(int k = 0; k < theSize; ++k){
    //         newArray[k] = std::move(data[k]);
    //     }

    //     theCapacity = newCapacity;
    //     std::swap(data, newArray);
    //     delete [] newArray;
    // }

    // allocate more memory for the array
    void reserve(size_t newCapacity, size_t start, size_t end)
    {
        //std::cout << "in the reserve" << std::endl;
        if(newCapacity < theSize){
            return;
        } 
        DataType *newArray = new DataType[newCapacity];
        if(end < start){
            //td::cout << "in the reserve end < start" << std::endl;
            int temp = start;
            for(int k = 0; k < theSize; ++k){
                std::cout << "this is temp: " << temp << std::endl;
                newArray[k] = std::move(data[temp++]);
            }
            for(int k = 0; k <= end; ++k){
                std::cout << "this is start: "<< start << std::endl;
                newArray[start++] = std::move(data[k]);
            }

        }
        else {
            //std::cout << "in the reserve end > start" << std::endl;
            for(int k = start; k < theSize; ++k){
                newArray[k] = std::move(data[k]);
            }
        }

        theCapacity = newCapacity;
        std::swap(data, newArray);
        delete [] newArray;
    }

    // data access operator (without bound checking)
    DataType & operator[] (size_t index)
    {
        return data[index];
    }

    const DataType & operator[](size_t index) const
    {
        return data[index];
    }

    // check if the vector is empty; return TURE if the vector is empty
    bool empty() const
    {
        return size() == 0;
    }

    // returns the size of the vector
    size_t size() const 
    {
        return theSize;
    }

    // returns the capacity of the vector
    size_t capacity() const 
    {
        return theCapacity;
    }

    // insert an data element to the end of the vector
    void push_back(const DataType & x)
    {
        if(theSize == theCapacity){
            reserve(2 * theCapacity + 1);
        }
        data[theSize++] = x;
    }

    void push_back(DataType && x)
    {
        if(theSize == theCapacity){
            reserve(2 * theCapacity + 1);
        }
        data[theSize++] = std::move(x);
    }

    // append a vector as indicated by the parameter to the current vector
    MyVector<DataType>& append(MyVector<DataType> && rhs)
    {
        if(theSize + rhs.size() > theCapacity){
            reserve(10 * theCapacity + 1);
        }
        for(int k = 0; k < rhs.size(); k++){
            data[theSize++] = std::move(rhs.data[k]);
        }
        return *this;
    }

    // remove the last data element from the array
    void pop_back()
    {
        --theSize;
    }

    void pop_front(){
        for(int i = 0; i < theSize; ++i){
            data[i] = data[i + 1];
        }
        --theSize;
    }

    // returns the last data elemtn from the array
    const DataType& back() const 
    {
        return data[theSize - 1];
    }

    const DataType& front() const 
    {
        return data[0];
    }

    // iterator implementation

    typedef DataType* iterator;
    typedef const DataType* const_iterator;

    iterator begin()
    {
        return &data[0];
    }

    const_iterator begin() const
    {
        return &data[0];
    }

    iterator end()
    {
        return &data[size()];
    }

    const_iterator end() const 
    {
        return &data[size()];
    }

};


#endif // __MYVECTOR_H__