
#include <iostream>
#include <vector>
#include "./AbstractLinkedList.cpp"
using namespace std;

template<typename Type>
class DoublyLinkedList : public LinkedList<Type> {

private:
    struct Node{

        Type value;
        Node* next;
        Node* previous;

        Node(const Type& v, Node* n = nullptr, Node* p = nullptr)
        : value(v), next(n), previous(p) {}
    }

    size_t size;
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
};