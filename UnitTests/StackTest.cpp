
#include <iostream>
#include <cassert>
#include "../Stack.cpp"
using namespace std;

void basicTest(Stack<int>& s){

    assert(s.is_empty() && s.size()==0 && "stack is not empty on intialization");

    for(int i=1; i<=5; ++i) s.push(i);
    assert(s.top()==5 && "top is not 5");
    assert(s.size()==5 && "size is not 5");

    for(int i=1; i<=2; ++i) s.pop();
    assert(s.top()==3 && "top is not 3");
    assert(s.size()==3 && "size is not 3");

    assert(!s.is_empty() && "stack is empty");

    assert(s.size()==3 && "size is not 3");

    s.clear();
    assert(s.is_empty() && s.size()==0 && "stack is not empty after clear");
}

int main(int argc, char const *argv[])
{
    LinkedStack<int> s;
    basicTest(s);
    
    ArrayStack<int> as;
    basicTest(as);

    std::cout << "All tests passed." << endl;
}