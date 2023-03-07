
#include <iostream>
#include <vector>
using namespace std;

template <typename Type>
class Queue{

public:
    virtual ostream& to_ostream(ostream& output) const = 0;

    virtual void push(const Type& elt) = 0;
    virtual void pop() = 0;
    virtual short front() const = 0;

    virtual size_t length() const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
};

template <typename Type>
ostream& operator<<(ostream& output, const Queue<Type>& q){
    return q.to_ostream(output);
}

template <typename Type>
class ArrayQueue : public Queue<Type> {

private:
    vector<short> q;
    size_t size;

    int start;
    int end;

    void increment(int& index) const {
        index = index+1 % q.size();
    }

    int incremented(const int& index) const {
        return ((index+1) % q.size());
    }

public:
    ArrayQueue(const size_t& cap) : start(0), end(0), size(0) {
        
        this->q = vector<short>(cap+1);
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(int i=start; i!=end; increment(i)) output << q[i] << " ";
        output << "]";
        return output;
    }

    void push(const short& new_value) override {

        if(is_full()) {
            cerr << "cannot push if queue is full" << endl;
            return;
        }

        q[end] = new_value;
        ++size;
        increment(end);
    }

    void pop() override {
        
        if(is_empty()) {
            cerr << "cannot pop if queue is empty" << endl;
            return;
        }

        increment(start);
        --size;
    }

    short front() const override {
        return q[start];
    }

    size_t length() const override {
        return size;
    }

    bool is_empty() const override {
        return start==end;
    }

    bool is_full() const {
        return incremented(end) == start;
    }

    void clear() override {
        start = end = size = 0;
    }

    ~ArrayQueue() = default;
};

template <typename Type>
class LinkedQueue : public Queue<Type> {

private:
    struct Node{

        short value;
        Node* next;

        Node(const short& v, Node* n = nullptr) : value(v), next(n){}
    };

    size_t size;
    Node* first;
    Node* last;

public:
    LinkedQueue() : size(0), first(nullptr), last(nullptr) {}
    
    LinkedQueue(const vector<short>& v) : LinkedQueue() {
        for(const short& elt : v) this->push(elt);
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(Node* jumper = first; jumper; jumper = jumper->next) output << jumper->value << " ";
        output << "]";
        return output;
    }

    void push(const short& new_value) override {

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

    short front() const override {
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
