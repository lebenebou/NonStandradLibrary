
#include <iostream>
#include <vector>

#ifndef ABSTRACT_STACK
#define ABSTRACT_STACK
#endif

using namespace std;

template<typename Type>
class LinkedStack : public Stack<Type> {

    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n){}
    };

    Node* last;
    size_t count;

public:
    LinkedStack() : last(nullptr), count(0){}

    LinkedStack(const vector<Type>& v) : last(nullptr), count(0){
        for(const Type& elt : v) this->push(elt);
    }

    void display() const override {

        cout << "LinkedStack: [[ ";
        for(Node* jumper = last; jumper; jumper = jumper->next){
            cout << jumper->value << " -> ";
        }
        cout << "<]";
    }

    Type top() const override {
        return last->value;
    }

    void pop() override {

        if(is_empty()) throw "Cannot pop from empty stack";

        Node* trash = last;
        last = last->next;
        delete trash;
        --count;
    }

    void push(const Type& new_value) override {

        last = new Node(new_value, last);
        ++count;
    }

    size_t size() const override {
        return count;
    }

    bool is_empty() const override {
        return !last;
    }
    
    void clear() override {
        while(count) pop();
    }

    ~LinkedStack(){
        while(count) pop();
    }
};
