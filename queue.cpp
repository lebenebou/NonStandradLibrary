
#include <iostream>
#include <vector>
using namespace std;

class Queue{

public:
    virtual void push(const short& elt) = 0;
    virtual void pop() = 0;
    virtual short front() const = 0;

    virtual size_t length() const = 0;
    
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;

    virtual ostream& to_ostream(ostream& output) const = 0;
};

class ArrayQueue : public Queue{

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

ostream& operator<<(ostream& output, const Queue& q){
    return q.to_ostream(output);
}

int main(int argc, char const *argv[]){

    ArrayQueue q(10);
    for(int i=1; i<=10; ++i) q.push(i);
    for(int i=1; i<=5; ++i) q.pop();
    for(int i=1; i<=3; ++i) q.push(17);

    cout << q << endl;

    return 0;
}