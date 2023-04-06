
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
using namespace std;

template <typename Type>
class LinkedList{

    struct Node{

        Type value;
        unique_ptr<Node> next;

        Node(Type val, unique_ptr<Node> ptr) : value(val), next(move(ptr)) {}
    };

    Node* node_at_index(size_t index) const {

        Node* jumper = head.get();
        while(index--) jumper = jumper->next.get();
        return jumper;
    }

    unique_ptr<Node> head;
    size_t size;

    template <typename T>
    friend void swap(LinkedList<T>& l1, LinkedList<T>& l2);

public:
    LinkedList(const vector<Type>& v = {}) : head(nullptr), size(0) {
        for(auto it = v.rbegin(); it!=v.rend(); ++it) this->push_front(*it);
    }

    LinkedList(const LinkedList<Type>& other) : head(nullptr), size(other.size) {

        if(other.is_empty()) return;

        head = make_unique<Node>(other.head->value, nullptr);

        Node* j1 = head.get();
        Node* j2 = other.head->next.get();

        while(j2 != nullptr){

            j1->next = make_unique<Node>(j2->value, nullptr);

            j1 = j1->next.get();
            j2 = j2->next.get();
        }
    }

    LinkedList<Type>& operator=(LinkedList<Type> other){

        swap(*this, other);
        return *this;
    }

    LinkedList<Type>& operator+=(LinkedList<Type> other){

        if(this->is_empty()) return *this = other;

        node_at_index(size-1)->next = move(other.head);
        size = this->size + other.size;
        return *this;
    }

    LinkedList<Type> operator+(const LinkedList<Type>& other){

        return LinkedList<Type>(*this) += other;
    }

    bool push_front(const Type& new_value){

        head = make_unique<Node>(new_value, move(head));
        return ++size;
    }

    bool push_back(const Type& new_value){

        if(is_empty()) return push_front(new_value);

        node_at_index(size-1)->next = make_unique<Node>(new_value, nullptr);
        return ++size;
    }
    
    bool pop_front(){

        if(is_empty()) return false;

        head = move(head->next);
        return size--;
    }

    bool pop_back(){

        if(size < 2) return pop_front();

        node_at_index(size-2)->next = nullptr;
        return size--;
    }

    size_t length() const {
        return size;
    }

    bool is_empty() const {
        return head.get()==nullptr;
    }

    void debug() const {

        cout << "[ ";
        for(Node* jumper = head.get(); jumper; jumper = jumper->next.get()){

            cout << jumper->value << " ";
        }
        cout << "] of size " << size << endl;
    }

    Type& operator[](const size_t& index){

        Node* wanted = node_at_index(index);
        assert(wanted!=nullptr && "Index out of bounds");
        return node_at_index(index)->value;
    }

    Type operator[](const size_t& index) const {

        Node* wanted = node_at_index(index);
        assert(wanted!=nullptr && "Index out of bounds");
        return node_at_index(index)->value;
    }

    void clear(){

        head.release();
        head = nullptr;
        size = 0;
    }

    ~LinkedList() = default;
};

template <typename Type>
void swap(LinkedList<Type>& l1, LinkedList<Type>& l2){

    using std::swap;
    swap(l1.head, l2.head);
    swap(l1.size, l2.size);
}