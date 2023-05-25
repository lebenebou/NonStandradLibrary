
#include <iostream>
#include <cassert>
#include "../DynamicArray.cpp"
using namespace std;

void basicTest(DynamicArray<int>& arr){

    arr.clear();

    // unit tests for DynamicArray
    assert(arr.size()==0 && "size is not 0");

    for(int i=1; i<=5; ++i) arr.push_back(i);
    assert(arr.size()==5 && "size is not 5");

    for(int i=1; i<=2; ++i) arr.pop_back();
    assert(arr.size()==3 && "size is not 3");

    assert(arr.insert(10, 1) && "insertion failed");
    assert(arr.size()==4 && "size is not 4");
    assert(arr[1]==10 && "arr[1] is not 10");
}

int main(int argc, char const *argv[])
{
    DynamicArray<int> arr;
    basicTest(arr);

    cout << "All tests passed." << endl;

    return 0;
}