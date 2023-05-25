
#include <iostream>
#include <cassert>
#include "../PriorityQueue.cpp"
using namespace std;

void basicTest(PriorityQueue<int>& q){

    assert(q.size() == 0 && "size() should be 0");

    for(int i=1; i<=5; ++i) q.push(i);
    assert(q.size() == 5 && "size() should be 5");

    for(int i=5; i>=1; --i){
        assert(q.top() == i && "top() is not correct");
        q.pop();
    }

    assert(q.size() == 0 && "size() should be 0");

    for(int i=1; i<=5; ++i) q.push(i);
    q.clear();
    assert(q.size() == 0 && "size() should be 0");
}

int main(int argc, char const *argv[])
{
    PriorityQueue<int> q;
    basicTest(q);

    cout << "All tests passed." << endl;

    return 0;
}