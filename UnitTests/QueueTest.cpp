
#include <iostream>
#include <cassert>
#include "../Queue/AbstractQueue.cpp"
#include "../Queue/ArrayQueue.cpp"
#include "../Queue/LinkedQueue.cpp"
using namespace std;

void lengthTest(const bool& isArrayQueue){

    AbstractQueue<int>* q = nullptr;
    if(isArrayQueue) q = new ArrayQueue<int>(10);
    else q = new LinkedQueue<int>();

    assert(q->is_empty() && "queue is_empty() is false on construction");
    assert(q->length()==0 && "queue length() is not 0 on construction");

    for(int i=0; i<10; ++i) q->push(i);
    
    const size_t actual = q->length();
    delete q;
    assert(actual == 10 && "queue size is not equal to number of elements pushed");
}

void pushTest(const bool& isArrayQueue){

    AbstractQueue<int>* q = nullptr;
    if(isArrayQueue) q = new ArrayQueue<int>(10);
    else q = new LinkedQueue<int>();
    
    string expected = "";
    for(int i=0; i<10; ++i) {
        q->push(i);
        expected += to_string(i);
    }

    string actual = "";
    while(!q->is_empty()){

        actual += to_string(q->front());
        q->pop();
    }

    delete q;
    assert(expected==actual && "pop sequence does not match push sequence");
}

void pushPopTest(const bool& isArrayQueue){

    AbstractQueue<int>* q = nullptr;
    if(isArrayQueue) q = new ArrayQueue<int>(10);
    else q = new LinkedQueue<int>();

    for(int i=0; i<10; ++i) q->push(i);
    for(int i=0; i<10; ++i) q->pop();
    assert(q->is_empty() && "queue is not empty after pushing and popping 10 elements");
    
    // to be continued...
}

int main(int argc, char const *argv[]){

    pushTest(true);
    pushTest(false);

    lengthTest(true);
    lengthTest(false);

    pushPopTest(true);
    pushPopTest(false);

    cout << "All tests passed." << endl;
    return 0;
}