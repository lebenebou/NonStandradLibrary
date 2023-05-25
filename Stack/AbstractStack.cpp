
#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
class Stack{

public:
    virtual void push(const Type& new_value) = 0;
    virtual Type top() const = 0;
    virtual void pop() = 0;

    virtual void display() const = 0;

    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;

    virtual ~Stack(){}
};