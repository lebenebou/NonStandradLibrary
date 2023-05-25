
#include <iostream>
#include <vector>

#ifndef AbstractQueue_CPP
#define AbstractQueue_CPP
#endif

using namespace std;

template <typename Type>
class ArrayQueue : public AbstractQueue<Type> {

private:
    vector<Type> q;
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
        
        this->q = vector<Type>(cap+1);
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(int i=start; i!=end; increment(i)) output << q[i] << " ";
        output << "]";
        return output;
    }

    void push(const Type& new_value) override {

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

    Type front() const override {
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
