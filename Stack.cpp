
#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
class Stack{

public: // interface for a stack
    virtual void push(const Type& new_value) = 0;
    virtual Type top() const = 0;
    virtual void pop() = 0;

    virtual void display() const = 0;

    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;

    virtual ~Stack(){}
};

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
    
    ~LinkedStack(){
        while(count) pop();
    }
};

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
};