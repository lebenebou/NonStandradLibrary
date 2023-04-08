
#include <iostream>
#include <vector>
#include <cassert>

#ifndef ABSTRACT_LINKED_LIST_CPP
#define ABSTRACT_LINKED_LIST_CPP
#endif

using namespace std;

template<typename Type>
class DoublyLinkedList : public LinkedList<Type> {

private:
    struct Node{

        Type value;
        Node* next;
        Node* previous;

        Node(const Type& v, Node* p = nullptr, Node* n = nullptr)
        : value(v), previous(p), next(n){

            if(p) p->next = this;
            if(n) n->previous = this;
        }
    };

    Node* node_at_index(size_t index) const {

        assert(index < size && "Index out of bounds");

        Node* jumper = nullptr;

        if(index < size/2){

            jumper = head;
            while(--index + 1) jumper = jumper->next;
        }
        else { // index >= size/2

            index = size - index;
            jumper = tail;
            while(--index) jumper = jumper->previous;
        }
        return jumper;
    }

    size_t size;
    Node* head;
    Node* tail;

    template<typename T>
    friend void swap(DoublyLinkedList<T>& l1, DoublyLinkedList<T>& l2);

public:
    DoublyLinkedList(const vector<Type>& v = {}) : head(nullptr), tail(nullptr), size(0) {

        for(auto it = v.rbegin(); it!=v.rend(); ++it) this->push_front(*it);
    }

    DoublyLinkedList(const DoublyLinkedList<Type>& other) : head(nullptr), tail(nullptr), size(other.size) {

        if(other.is_empty()) return;
        
        head = new Node(other.head->value);

        Node* j1 = head;
        Node* j2 = other.head->next;

        while(j2){

            j1->next = new Node(j2->value);

            j1 = j1->next;
            j2 = j2->next;
        }
        tail = j1;
    }

    DoublyLinkedList(DoublyLinkedList<Type>&& other) : head(other.head), tail(other.tail), size(other.size) {

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    DoublyLinkedList<Type>& operator=(const DoublyLinkedList<Type>& other){

        if(this == &other) return *this;

        DoublyLinkedList<Type> temp(other);
        swap(*this, temp);
        return *this;
    }

    DoublyLinkedList<Type>& operator=(DoublyLinkedList<Type>&& other){

        if(this == &other) return *this;

        swap(*this, other);
        other.clear();

        return *this;
    }

    DoublyLinkedList<Type>& operator+=(DoublyLinkedList<Type> other){

        if(this->is_empty()) return *this = other;
        if(other.is_empty()) return *this;

        size += other.size;
        tail->next = other.head;
        other.head = nullptr;
        return *this;
    }

    DoublyLinkedList<Type> operator+(const DoublyLinkedList<Type>& other){

        return DoublyLinkedList(*this) += other;
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(Node* jumper = head; jumper; jumper = jumper->next){
            output << jumper->value << " ";
        }
        output << "]";
        return output;
    }

    void push_back(const Type& new_value) override {

        if(is_empty()) return push_front(new_value);
        
        tail->next = new Node(new_value, tail, nullptr);
        tail = tail->next;
        ++size;
    }

    void push_front(const Type& new_value) override {
        
        head = new Node(new_value, nullptr, head);
        if(++size == 1) tail = head;
    }

    bool pop_back() override {
        
        if(size < 2) return pop_front();

        tail = tail->previous; // definitely not nullptr, possibly == head
        delete tail->next;
        tail->next = nullptr;
        --size;
        return true;
    }

    bool pop_front() override {
        
        if(is_empty()) return false;

        Node* trash = head;
        head = head->next; // could become nullptr
        delete trash;
        if(--size != 0) head->previous = nullptr;
        // if size became 0, head is nullptr; no need for fix
        return true;
    }

    bool insert(const Type& new_value, size_t index) override {
        
        if(index>size) return false;
        if(index==0) { push_front(new_value); return true; }
        if(index==size) { push_back(new_value); return true; }

        // index is somewhere in the middle
        Node* jumper = node_at_index(index-1);
        jumper->next = new Node(new_value, jumper, jumper->next);
        ++size;
        return true;
    }
    
    bool remove(size_t index) override {

        if(index>=size) return false;
        if(index==0) return pop_front();
        if(index==size-1) return pop_back();

        // index is somewhere in the middle
        Node* trash = node_at_index(index);
        trash->previous->next = trash->next;
        trash->next->previous = trash->previous;
        delete trash;
        --size;
        return true;
    }

    Type& operator[](const size_t& index) override {
        return node_at_index(size-1)->value;
    }
    Type operator[](const size_t& index) const override {
        return node_at_index(size-1)->value;
    }

    bool is_empty() const { return !head; }
    size_t length() const { return size; }

    void clear(){
        while(pop_front());
    }

    ~DoublyLinkedList(){
        this->clear();
    }
};

template<typename Type>
void swap(DoublyLinkedList<Type>& l1, DoublyLinkedList<Type>& l2){

    using std::swap;
    swap(l1.head, l2.head);
    swap(l1.tail, l2.tail);
    swap(l1.size, l2.size);
}