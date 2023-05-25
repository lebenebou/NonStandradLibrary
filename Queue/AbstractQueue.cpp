
#include <iostream>
using namespace std;

template <typename Type>
class AbstractQueue{

public:
    virtual ostream& to_ostream(ostream& output) const = 0;

    virtual void push(const Type& elt) = 0;
    virtual void pop() = 0;
    virtual Type front() const = 0;

    virtual size_t length() const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
};

template <typename Type>
ostream& operator<<(ostream& output, const AbstractQueue<Type>& q){
    return q.to_ostream(output);
}