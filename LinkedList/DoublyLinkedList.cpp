
#include <iostream>
#include <vector>
#include <cassert>
#include "./AbstractLinkedList.cpp"
using namespace std;

template<typename Type>
class DoublyLinkedList : public LinkedList<Type> {

private:
    struct Node{

        Type value;
        Node* next;
        Node* previous;

        Node(const Type& v, Node* p = nullptr, Node* n = nullptr)
        : value(v), next(n), previous(p) {}
    };

    Node* node_at_index(size_t index) const {

        assert(index < size && "Index out of bounds");
        return nullptr;
    }

    size_t size;
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    virtual ostream& to_ostream(ostream& output) const = 0;

    void push_back(const Type& new_value){

        if(is_empty()) return push_front(new_value);
        
        tail->next = new Node(new_value, tail, nullptr);
        ++size;
    }

    void push_front(const Type&){
        
        head = new Node(new_value, nullptr, head);
        if(++size == 1) tail = head;
    }

    bool pop_back() = 0;
    bool pop_front() = 0;

    bool insert(const Type& new_value, size_t index) = 0;
    bool remove(size_t index) = 0;

    Type& operator[](const size_t& index) = 0;
    Type operator[](const size_t& index) const = 0;

    bool is_empty() const { return !head; }
    size_t length() const { return size; }

    void clear(){
        while(pop_front());
    }

    ~DoublyLinkedList(){
        this->clear();
    }
};

int main(int argc, char const *argv[])
{
    DoublyLinkedList<int> dl;
    return 0;
}
