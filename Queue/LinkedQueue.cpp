
#include <iostream>
#include <vector>

#ifndef AbstractQueue_CPP
#define AbstractQueue_CPP
#endif

using namespace std;

template <typename Type>
class LinkedQueue : public AbstractQueue<Type> {

private:
    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n){}
    };

    size_t size;
    Node* first;
    Node* last;

public:
    LinkedQueue() : size(0), first(nullptr), last(nullptr) {}
    
    LinkedQueue(const vector<Type>& v) : LinkedQueue() {
        for(const Type& elt : v) this->push(elt);
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(Node* jumper = first; jumper; jumper = jumper->next) output << jumper->value << " ";
        output << "]";
        return output;
    }

    void push(const Type& new_value) override {

        if(is_empty()) first = last = new Node(new_value);
        else last = last->next = new Node(new_value); // copyright Youssef Yammine
        ++size;
    }

    void pop() override {

        if(is_empty()){
            cerr << "Cannot pop from empty queue" << endl;
            return;
        }

        Node* trash = first;
        first = first->next;
        delete trash;
        --size;
    }

    Type front() const override {
        return first->value;
    }

    size_t length() const override {
        return size;
    }

    bool is_empty() const override {
        return !first;
    }

    void clear() override {

        while(!is_empty()) pop();
    }

    ~LinkedQueue(){
        clear();
    }
};