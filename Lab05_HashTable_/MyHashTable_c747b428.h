#ifndef __MYHASHTABLE_H__
#define __MYHASHTABLE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>

#include "MyVector_c747b428.h"
#include "MyLinkedList_c747b428.h"

static const long long uh_param_a = 53;       // universal hash function parameter a
static const long long uh_param_b = 97;       // universal hash function parameter b
static const long long prime_digits = 19;     // parameter used for finding a Mersenne prime
static const long long mersenne_prime = (1 << prime_digits) - 1;  // the Mersenne prime for universal hashing

// fast calculation of (n modulo mersenne_prime)
long long fastMersenneModulo(const long long n)
{
    return n % mersenne_prime ;
}

// definition of the template hash function class
template <typename KeyType>
class HashFunc
{
  public:
    long long univHash(const KeyType key, const long long table_size) const;
};

// the hash function class that supports the hashing of the "long long" data type
template <>
class HashFunc<long long>
{
  public:
    long long univHash(const long long key, const long long table_size) const
    {
        long long hv = fastMersenneModulo(static_cast<long long>(uh_param_a * key + uh_param_b));
        hv = hv % table_size;
        return hv;
    }
};

// the has function class that supports the hashing of the "std::string" data type
template <>
class HashFunc<std::string>
{
  private:
    const int param_base = 37;      // the base used for inflating each character
  public:    
    long long univHash(const std::string& key, const long long table_size) const
    {
        long long hv = 0;
        for(size_t i = 0; i < key.length(); ++ i)
        {
            hv = param_base * hv + static_cast<long long>(key[i]);
        }
        hv = fastMersenneModulo(static_cast<long long>(uh_param_a * hv + uh_param_b));
        hv = hv % table_size;
        return hv;
    }
};

// definition of the template hashed object class
template <typename KeyType, typename ValueType>
class HashedObj
{
  public:

    KeyType key;
    ValueType value;

    HashedObj()
    {
        return;
    }

    HashedObj(const KeyType& k, const ValueType& v) :
        key(k),
        value(v)
    {
        return;
    }
  
    HashedObj(KeyType && k, ValueType && v) :
        key(std::move(k)),
        value(std::move(v))
    {
        return;
    }

    bool operator==(const HashedObj<KeyType, ValueType>& rhs)
    {
        return (key == rhs.key);
    }    

    bool operator!=(const HashedObj<KeyType, ValueType>& rhs)
    {
        return !(*this == rhs);
    }   

};

template <typename KeyType, typename ValueType>
class MyHashTable
{ 
  private:
    size_t theSize; // the number of data elements stored in the hash table
    MyVector<MyLinkedList<HashedObj<KeyType, ValueType> >* > hash_table;    // the hash table implementing the separate chaining approach
    MyVector<size_t> primes;    // a set of precomputed and sorted prime numbers

    // pre-calculate a set of primes using the sieve of Eratosthenes algorithm
    // will be called if table doubling requires a larger prime number for table size
    // expected to update the private member "primes"
    void preCalPrimes(const size_t n)
    {
        MyVector<size_t> integers;
        size_t max_current_prime = primes.size() ? primes.back() : 0;

        for(size_t i = 0; i <= n; ++i){
            integers.push_back(0);
        }

        size_t cur_prime = 2;
        while (cur_prime <= n){
            if(cur_prime > max_current_prime)
                primes.push_back(cur_prime);
            size_t marker = cur_prime;
            while (marker <= n){
                integers[marker] = 1;
                marker += cur_prime;
            }
            while(cur_prime <= n && integers[++cur_prime] == 1){;}
        }
        // MyVector<int> prePrimes;  
        // prePrimes.resize(n);
        // for(int i = 0; i < prePrimes.size(); i++){
        //     prePrimes[i] = true;
        // }
        // for (int p = 2; p * p <= n; p++) {
        //     if (prePrimes[p] == true) {
        //         for (int i = p * p; i <= n; i += p)
        //             prePrimes[i] = false;
        //     }
        // }
        // for(size_t i = 0; i < prePrimes.size(); i++){
        //     if(prePrimes[i]){
        //         primes.push_back(i);
        //     }
        // }
    }

    // finding the smallest prime that is larger than or equal to n
    // should perform binary search against the private member "primes"
    size_t nextPrime(const size_t n)
    {
        size_t left = 0;
        size_t right = primes.size() - 1;
        
        while(left <= right){
            size_t mid = (left + right) / 2;
            if(n == primes[mid]){
                return n;
            }
            else if(n > primes[mid]){
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        //std::cout << "End binary search" << std::endl;
        return primes[left];
        // size_t lo = 0, hi = primes.size() - 1;
        // size_t mid;
        // while (hi - lo > 1) {
        //     size_t mid = (hi + lo) / 2;
        //     if (primes[mid] < n) {
        //         lo = mid + 1;
        //     }
        //     else {
        //         hi = mid;
        //     }
        // }
        // if(n > primes[lo]){
        //     return primes[hi];
        // }
        // else{
        //     return primes[lo];
        // }
    }

    // finds the MyLinkedList itertor that corresponds to the hashed object that has the specified key
    // returns the end() iterator if not found
    typename MyLinkedList<HashedObj<KeyType, ValueType> >::iterator find(const KeyType& key)
    {
        HashFunc<KeyType> myHash;
        size_t hash_val = myHash.univHash(key, hash_table.size());
        auto bucket = hash_table[hash_val];
        for(auto itr = bucket->begin(); itr != bucket->end(); itr++){
            if((*itr).key == key){
                return itr;
            }
        }
        return bucket->end(); 
    }

    // rehashes all data elements in the hash table into a new hash table with new_size
    // note that the new_size can be either smaller or larger than the existing size
    void rehash(const size_t new_size)
    {
        MyLinkedList<HashedObj<KeyType, ValueType>> temp;
        for(size_t i = 0; i < capacity(); i++){
            for(auto itr = hash_table[i]->begin(); itr != hash_table[i]->end(); itr++){
                temp.push_back(std::move(*itr));
            }
        }

        size_t cur_cap = capacity();

        for(size_t i = 0; i < capacity(); i++){
            hash_table[i]->clear();
        }
        if(new_size > cur_cap){
            for(int i = 0; i < new_size - cur_cap; i++){
                hash_table.push_back(new MyLinkedList<HashedObj<KeyType, ValueType>>);
            }
        }
        else {
            for(int i = 0; i < cur_cap - new_size; i++){
                delete hash_table.back();
                hash_table.pop_back();
            }
        }
        theSize = 0;
        for(auto &temp_item : temp){
            insert(std::move(temp_item));
        }
    }

    // doubles the size of the table and perform rehashing
    // the new table size should be the smallest prime that is larger than the expected new table size (double of the old size)
    void doubleTable()
    {
        if (2 * hash_table.size() >= primes.back()) {
            preCalPrimes(5 * primes.back());
        }
        size_t new_size = nextPrime(2 * hash_table.size());
        if(new_size < 17) new_size = 17;
        this->rehash(new_size);
        return;
    }

    // halves the size of the table and perform rehahsing
    // the new table size should be the smallest prime that is larger than the expected new table size (half of the old size)
    void halveTable()
    {
        size_t new_size = nextPrime(ceil(hash_table.size() / 2));
        this->rehash(new_size);
        return;
    }

  public:

    // the default constructor; allocate memory if necessary
    explicit MyHashTable(const size_t init_size = 3)
    {
        preCalPrimes(init_size);
        theSize = 0;
        for(int i = 0; i < init_size; i++){
            hash_table.push_back(new MyLinkedList<HashedObj<KeyType, ValueType>>);
        }
    }

    // the default destructor; collect memory if necessary
    ~MyHashTable()
    {
        for(int i = 0; i < capacity(); i++){
            delete hash_table[i];
        }
    }

    // checks if the hash table contains the given key
    bool contains(const KeyType& key)
    {
        HashFunc<KeyType> myHash;
        auto & bucket = hash_table[myHash.univHash(key, hash_table.size())];
        return find(key) != bucket->end();
    }

    // retrieves the data element that has the specified key
    // returns true if the key is contained in the hash table
    // return false otherwise
    bool retrieve(const KeyType& key, HashedObj<KeyType, ValueType>& data)
    {
        HashFunc<KeyType> myHash;
        auto & bucket = hash_table[myHash.univHash(key, hash_table.size())];

        auto itr = find(key);
        if(itr == bucket->end()){
            return false;
        }

        data.key = (*itr).key;
        data.value = (*itr).value;
        return true;

    }

    // inserts the given data element into the hash table (copy)
    // returns true if the key is not contained in the hash table
    // return false otherwise
    bool insert(const HashedObj<KeyType, ValueType>& x)
    {
        if(contains(x.key)){
            return false;
        }
        HashFunc<KeyType> myHash; 
        auto & bucket = hash_table[myHash.univHash(x.key, hash_table.size())];
        bucket->push_back(x);
        if((++theSize) * 2 >= hash_table.size()){
            doubleTable();
        }
        return true;
    }

    // inserts the given data element into the hash table (move)
    // returns true if the key is not contained in the hash table
    // return false otherwise
    bool insert(HashedObj<KeyType, ValueType> && x)
    {
        if(contains(x.key)){
            return false;
        }
        HashFunc<KeyType> myHash; 
        auto & bucket = hash_table[myHash.univHash(x.key, hash_table.size())];
        bucket->push_back(std::move(x));
        if((++theSize) * 2 >= hash_table.size()){
            doubleTable();
        }
        return true;
    }

    // removes the data element that has the key from the hash table
    // returns true if the key is contained in the hash table
    // returns false otherwise
    bool remove(const KeyType& key)
    {
        if(!contains(key)){
            return false;
        }
        HashFunc<KeyType> myHash; 
        auto & bucket = hash_table[myHash.univHash(key, hash_table.size())];
        auto itr = find(key);
        bucket->erase(itr);
        if(--theSize * 8 <= hash_table.size()){
            halveTable();
        }
        return true;
    }

    // returns the number of data elements stored in the hash table
    size_t size()
    {
        return theSize;
    }

    // returns the capacity of the hash table
    size_t capacity()
    {
        return hash_table.size();
    }

};


#endif // __MYHASHTABLE_H__
