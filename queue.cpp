
#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
class Queue{

public: // interface for a queue
    virtual void display() const = 0;

    virtual void push(const Type& new_value) = 0;
    virtual void dequeue() = 0;

    virtual Type front() const = 0;
    virtual Type back() const = 0;

    virtual size_t length() const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;

    virtual ~Queue(){}
};

template<typename Type>
class LinkedQueue : public Queue<Type> {

private:
    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n){}
    };

    Node* first;
    Node* last;
    size_t size;

public:
    LinkedQueue() : first(nullptr), last(nullptr), size(0){}

    LinkedQueue(const vector<Type>& v) : first(nullptr), last(nullptr), size(0){
        for(const Type& elt : v) push(elt);
    } 

    void push(const Type& new_value) override {

        if(is_empty()) first = last = new Node(new_value, nullptr);
        else{
            last = last->next = new Node(new_value, nullptr);
            // copyright Youssef Yammine
        }

        ++size;
    }

    Type front() const override {
        
        if(is_empty()) throw "Queue is empty, cannot return front";
        return first->value;
    }

    Type back() const override {
        
        if(is_empty()) throw "Queue is empty, cannot return back";
        return last->value;
    }

    void display() const override {
        
        cout << "[ ";
        for(Node* jumper = first; jumper; jumper = jumper->next){
            cout << jumper->value << " <- ";
        }
        cout << "]";
    }

    void dequeue() override {

        if(is_empty()) return;

        Node* trash = first;
        first = first->next;
        delete trash;
        --size;
    }

    size_t length() const override {
        return size;
    }

    bool is_empty() const override {
        return !first;
    }

    void clear() override {
        while(!is_empty()) dequeue();
    }

    ~LinkedQueue(){
        clear();
    }
};

template<typename Type>
class ArrayQueue : public Queue<Type> {

private:

    Type* q;
    const size_t capacity;
    size_t size;

    size_t first;
    size_t last;

    // const static size_t MAX_SIZE = 1000;

    void increment(size_t& index) const {
        if(++index == capacity) index = 0;
    }

public:
    ArrayQueue(const size_t& cap) : q(new Type[cap]), capacity(cap), size(0), first(0), last(0) {}

    ArrayQueue(const vector<Type>& v) : q(new Type[v.size()*2]), capacity(v.size()*2), size(0), first(0), last(0) {
        for(const Type& elt : v) push(elt);
    }

    void display() const override {

        cout << "Queue: [ ";
        for(size_t i = first; i!=last; increment(i)){
            cout << q[i] << " < ";
        }
        cout << "]\n" << endl;
        cout << "\t-Size: " << size << endl;
        cout << "\t-Front: " << front() << endl;
        cout << "\t-Back: " << back() << endl;
        cout << "\t-Capacity: " << capacity << endl;
    }

    void push(const Type& new_value) override {

        if(is_full()) throw "Queue capacity is full, cannot push element";

        q[last] = new_value;
        increment(last);
        ++size;
    }
    
    void dequeue() override {

        if(is_empty()) throw "Queue is empty, cannot dequeue";
        increment(first);
        --size;
    }

    Type front() const override {

        if(is_empty()) throw "Queue is empty, cannot return front";
        return q[first];
    }

    Type back() const override {

        if(is_empty()) throw "Queue is empty, cannot return back";
        if(last>0) return q[last-1];
        return q[capacity-1]; // last is 0
    }

    bool is_empty() const override {
        return first==last; // or size==0
    }

    bool is_full() const {
        return (size == capacity-1);
    }

    size_t length() const override {
        return size;
    }

    void clear() override {
        first = last;
        size = 0;
    }

    ~ArrayQueue(){
        delete[] q;
    }

};

int main(int argc, char* argv[]){

    Queue<int>* q = new LinkedQueue<int>({1, 2, 3, 4});
    cout << "Linked Queue: ";

    while(!q->is_empty()){

        cout << q->front() << " ";
        q->dequeue();
    }

    delete q; cout << endl;

    q = new ArrayQueue<int>({5, 6, 7, 8});
    cout << "Array Queue: ";

    while(!q->is_empty()){

        cout << q->front() << " ";
        q->dequeue();
    }

    delete q; cout << endl;

    return 0;
}