
#include <iostream>
#include <vector>
#include <cassert>

#ifndef ABSTRACT_LINKED_LIST_CPP
#define ABSTRACT_LINKED_LIST_CPP
#endif

using namespace std;

template<typename Type>
class SinglyLinkedList : public LinkedList<Type> {
    
private:
    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n){}
    };

    Node* node_at_index(size_t index) const {

        assert(index < size && "Index out of bounds");
        
        Node* jumper = head;
        while(index--) jumper = jumper->next;
        return jumper;
    }

    Node* head;
    size_t size;

    template<typename T>
    friend void swap(SinglyLinkedList<T>& l1, SinglyLinkedList<T>& l2);
    
public:
    SinglyLinkedList(const vector<Type>& v = {}) : size(0), head(nullptr) {

        for(auto it = v.rbegin(); it!=v.rend(); ++it) this->push_front(*it);
    }

    SinglyLinkedList(const SinglyLinkedList<Type>& other) : head(nullptr), size(other.size) {

        if(other.is_empty()) return;
        
        head = new Node(other.head->value);

        Node* j1 = head;
        Node* j2 = other.head->next;

        while(j2){

            j1->next = new Node(j2->value);
            j1 = j1->next;
            j2 = j2->next;
        }
    }

    SinglyLinkedList(SinglyLinkedList<Type>&& other) noexcept : head(other.head), size(other.size) {

        other.head = nullptr;
        other.size = 0;
    }

    SinglyLinkedList<Type>& operator=(const SinglyLinkedList<Type>& other){

        if(this == &other) return *this;

        SinglyLinkedList<Type> temp(other);
        swap(*this, temp);
        return *this;
    }

    SinglyLinkedList<Type>& operator=(SinglyLinkedList<Type>&& other) noexcept {

        if(this == &other) return *this;

        swap(*this, other);
        other.clear();

        return *this;
    }

    SinglyLinkedList<Type>& operator+=(SinglyLinkedList<Type> other){

        if(this->is_empty()) return *this = other;
        if(other.is_empty()) return *this;

        node_at_index(size-1)->next = other.head;
        this->size += other.size;
        other.head = nullptr; // to avoid destruction at the end of this scope
        return *this;
    }

    SinglyLinkedList<Type> operator+(const SinglyLinkedList<Type>& other){
        return SinglyLinkedList(*this) += other;
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
        
        node_at_index(size-1)->next = new Node(new_value);
        ++size;
    }

    void push_front(const Type& new_value) override {

        head = new Node(new_value, head);
        ++size;
    }

    bool pop_back() override {

        if(size < 2) return pop_front();

        Node* second_last = node_at_index(size-2);
        delete second_last->next;
        second_last->next = nullptr;
        --size;

        return true;
    }

    bool pop_front() override {

        if(is_empty()) return false;

        Node* trash = head;
        head = head->next;
        delete trash;
        --size;

        return true;
    }

    bool insert(const Type& new_value, size_t index) override {

        if(index > size) return false;
        if(index==0){
            push_front(new_value);
            return true;
        }
        if(index==size){
            push_back(new_value);
            return true;
        }

        Node* temp = node_at_index(index-1);
        temp->next = new Node(new_value, temp->next);
        return ++size;
    }

    bool remove(size_t index) override {

        if(index >= size) return false;
        if(index==0){
            pop_front();
            return true;
        }
        if(index==size-1){
            pop_back();
            return true;
        }

        Node* temp = node_at_index(index-1);
        Node* trash = temp->next;
        temp->next = temp->next->next;
        delete trash;
        return size--;
    }

    Type& operator[](const size_t& index) override {
        
        return node_at_index(index)->value;
    }

    Type operator[](const size_t& index) const override {
        
        return node_at_index(index)->value;
    }

    size_t length() const override { return size; }

    bool is_empty() const override {
        return !head;
    }

    void clear(){
        while(pop_front());
    }

    ~SinglyLinkedList(){
        this->clear();
    }
};

template <typename Type>
void swap(SinglyLinkedList<Type>& l1, SinglyLinkedList<Type>& l2){

    using std::swap;
    swap(l1.head, l2.head);
    swap(l1.size, l2.size);
}