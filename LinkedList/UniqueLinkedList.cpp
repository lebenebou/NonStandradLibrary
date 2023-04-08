
#include <iostream>
#include <vector>
#include <cassert>
#include <memory>

#ifndef ABSTRACT_LINKED_LIST_CPP
#define ABSTRACT_LINKED_LIST_CPP
#endif

using namespace std;

template<typename Type>
class UniqueLinkedList : public LinkedList<Type> {
    
private:
    struct Node{

        Type value;
        unique_ptr<Node> next;

        Node(const Type& v, unique_ptr<Node> next_ptr = nullptr) : value(v), next(move(next_ptr)) {}
    };

    Node* node_at_index(size_t index) const {

        assert(index < size && "Index out of bounds");
        
        Node* jumper = head.get();
        while(index--) jumper = jumper->next.get();
        return jumper;
    }

    unique_ptr<Node> head;
    size_t size;

    template<typename T>
    friend void swap(UniqueLinkedList<T>& l1, UniqueLinkedList<T>& l2);
    
public:
    UniqueLinkedList(const vector<Type>& v = {}) : size(0), head(nullptr) {

        for(auto it = v.rbegin(); it!=v.rend(); ++it) this->push_front(*it);
    }

    UniqueLinkedList(const UniqueLinkedList<Type>& other) : head(nullptr), size(other.size) {

        if(other.is_empty()) return;
        
        head = make_unique<Node>(other.head->value, nullptr);

        Node* j1 = head.get();
        Node* j2 = other.head->next.get();

        while(j2){

            j1->next = make_unique<Node>(j2->value, nullptr);
            j1 = j1->next.get();
            j2 = j2->next.get();
        }
    }

    UniqueLinkedList(UniqueLinkedList<Type>&& other) noexcept {

        this->head = std::move(other.head);
        this->size = other.size;
        other.size = 0;
    }

    UniqueLinkedList<Type>& operator=(const UniqueLinkedList<Type>& other){

        if(this == &other) return *this;

        UniqueLinkedList<Type> temp(other);
        swap(*this, temp);
        return *this;
    }

    UniqueLinkedList<Type>& operator=(UniqueLinkedList<Type>&& other) noexcept {

        if(this == &other) return *this;

        swap(*this, other);
        other.clear();

        return *this;
    }

    UniqueLinkedList<Type>& operator+=(UniqueLinkedList<Type> other){

        if(this->is_empty()) return *this = other;
        if(other.is_empty()) return *this;

        node_at_index(size-1)->next = std::move(other.head);
        this->size += other.size;
        return *this;
    }

    UniqueLinkedList<Type> operator+(const UniqueLinkedList<Type>& other){
        return UniqueLinkedList(*this) += other;
    }

    ostream& to_ostream(ostream& output) const override {

        output << "[ ";
        for(Node* jumper = head.get(); jumper; jumper = jumper->next.get()){
            output << jumper->value << " ";
        }
        output << "]";
        return output;
    }

    void push_back(const Type& new_value) override {

        if(is_empty()) return push_front(new_value);
        
        node_at_index(size-1)->next = make_unique<Node>(new_value);
        ++size;
    }

    void push_front(const Type& new_value) override {

        head = make_unique<Node>(new_value, move(head));
        ++size;
    }

    bool pop_back() override {

        if(size < 2) return pop_front();

        node_at_index(size-2)->next.reset();
        return size--;
    }

    bool pop_front() override {

        if(is_empty()) return false;

        head = std::move(head->next);
        return size--;
    }

    bool insert(const Type& new_value, size_t index) override {

        if(index > size) return false;
        if(index==0){ push_front(new_value); return true; }
        if(index==size){ push_back(new_value); return true; }

        // index is in the middle
        Node* temp = node_at_index(index-1);
        temp->next = make_unique<Node>(new_value, move(temp->next));
        return ++size;
    }

    bool remove(size_t index) override {

        if(index >= size) return false;
        if(index==0){ pop_front(); return true; }
        if(index==size-1){ pop_back(); return true; }
        
        Node* just_before = node_at_index(index-1);
        unique_ptr<Node> trash = std::move(just_before->next);
        just_before->next = std::move(trash->next);
        trash.reset();
        return size--;
    }

    Type& operator[](const size_t& index) override {
        return node_at_index(index)->value;
    }

    Type operator[](const size_t& index) const override {
        return node_at_index(index)->value;
    }

    size_t length() const override { return size; }

    bool is_empty() const override { return !head; }

    void clear(){
        while(pop_front());
    }

    ~UniqueLinkedList(){
        this->clear();
    }
};

template <typename Type>
void swap(UniqueLinkedList<Type>& l1, UniqueLinkedList<Type>& l2){

    using std::swap;
    swap(l1.head, l2.head);
    swap(l1.size, l2.size);
}