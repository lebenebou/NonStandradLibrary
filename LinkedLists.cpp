
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename Type>
class LinkedList{

protected:
    size_t size;

    template <typename T>
    friend void swap(LinkedList<T>& l1, LinkedList<T>& l2);

public:
    LinkedList() : size(0) {}

    virtual ostream& to_ostream(ostream& output) const = 0;

    virtual void push_back(const Type&) = 0;
    virtual void push_front(const Type&) = 0;
    virtual bool pop_back() = 0;
    virtual bool pop_front() = 0;

    virtual bool insert(const Type& new_value, size_t index) = 0;
    virtual bool remove(size_t index) = 0;

    virtual bool is_empty() const = 0;
    virtual size_t length() const final { return size; }

    virtual void clear() = 0;
    virtual ~LinkedList(){}
};

template<typename Type>
class SinglyLinkedList : public LinkedList<Type> {
    
private:
    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n){}
    };

    Node* node_at_index(size_t index) const {

        if(index >= this->size) return nullptr;
        
        Node* jumper = head;
        while(index--) jumper = jumper->next;
        return jumper;
    }

    Node* head;
    
public:
    SinglyLinkedList() : LinkedList<Type>(), head(nullptr) {}

    SinglyLinkedList(const SinglyLinkedList<Type>& other) : head(nullptr) {

        this->size = other.size;
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

    SinglyLinkedList& operator=(SinglyLinkedList<Type> other){

        swap(*this, other);
        return *this;
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

        if(is_empty()){
            head = new Node(new_value);
            ++this->size;
            return;
        }
        
        node_at_index(this->size-1)->next = new Node(new_value);
        ++this->size;
    }

    void push_front(const Type& new_value) override {

        head = new Node(new_value, head);
        ++this->size;
    }

    bool pop_back() override {

        if(this->size < 2) return pop_front();

        Node* second_last = node_at_index(this->size-2);
        delete second_last->next;
        second_last->next = nullptr;
        --this->size;

        return true;
    }

    bool pop_front() override {

        if(is_empty()) return false;

        Node* trash = head;
        head = head->next;
        delete trash;
        --this->size;

        return true;
    }

    bool insert(const Type& new_value, size_t index) override {

        if(index > this->size) return false;
        if(index==0){
            push_front(new_value);
            return true;
        }
        if(index==this->size){
            push_back(new_value);
            return true;
        }

        Node* temp = node_at_index(index-1);
        temp->next = new Node(new_value, temp->next);
        return ++this->size;
    }

    bool remove(size_t index) override {

        if(index >= this->size) return false;
        if(index==0){
            pop_front();
            return true;
        }
        if(index==this->size-1){
            pop_back();
            return true;
        }

        Node* temp = node_at_index(index-1);
        Node* trash = temp->next;
        temp->next = temp->next->next;
        delete trash;
        return this->size--;
    }

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

template<typename Type>
ostream& operator<<(ostream& output, const LinkedList<Type>& l){
    return l.to_ostream(output);
}