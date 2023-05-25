
#include <iostream>
#include <vector>

#ifndef ABSTRACT_STACK
#define ABSTRACT_STACK
#endif

using namespace std;
template<typename Type>
class ArrayStack : public Stack<Type> {

private:
    vector<Type> v;

public:
    ArrayStack(const size_t& capacity = 10) : v({}) {
        v.reserve(capacity);
    }

    ArrayStack(const vector<Type>& v2) : v(v2) {
        v.reserve(v2.size()*2);
    }

    void display() const override {

        cout << "[ ";
        for(const Type& elt : v) cout << elt << " ";
        cout << "]";
    }

    void push(const Type& new_value) override {
        v.push_back(new_value);
    }

    void pop() override {

        if(is_empty()) throw "Cannot pop from empty stack";
        v.pop_back();
    }

    Type top() const override {
        return *(v.end()-1);
    }

    Type bottom() const {
        return *v.begin();
    }

    size_t size() const override {
        return v.size();
    }

    bool is_empty() const override {
    
    
        return v.size()==0;
    }

    void clear() override {
        v.clear();
    }
};