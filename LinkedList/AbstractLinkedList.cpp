
#include <iostream>
using namespace std;

template<typename Type>
class LinkedList{

public:
    virtual ostream& to_ostream(ostream& output) const = 0;

    virtual void push_back(const Type&) = 0;
    virtual void push_front(const Type&) = 0;
    virtual bool pop_back() = 0;
    virtual bool pop_front() = 0;

    virtual bool insert(const Type& new_value, size_t index) = 0;
    virtual bool remove(size_t index) = 0;

    virtual Type& operator[](const size_t& index) = 0;
    virtual Type operator[](const size_t& index) const = 0;

    virtual bool is_empty() const = 0;
    virtual size_t length() const = 0;

    virtual void clear() = 0;
    virtual ~LinkedList(){}
};