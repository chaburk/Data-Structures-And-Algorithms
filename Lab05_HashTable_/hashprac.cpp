#include <iostream>
#include "MyHashTable_c747b428.h"
#include <string>
//#include "MyVector_c747b428.h"
using namespace std;

int main(){
    string s = "hello";
    int k = 55;
    MyHashTable<string, int> h;
    HashedObj<string, int> data(s, k);
    cout << h.capacity() << endl;
    cout << h.insert(data) << endl;
    return 0;
}