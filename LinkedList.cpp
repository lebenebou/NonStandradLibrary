
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename Type>
class LinkedList{

private:
    struct Node{

        Type value;
        Node* next;

        Node(const Type& v, Node* n = nullptr) : value(v), next(n) {}
    };

    Node* head;
    size_t size;

    Node* node_at_index(size_t index) const {

        if(index >= size) return nullptr;
        Node* jumper = head;
        while(index--) jumper = jumper->next;
        return jumper;
    }

    template<typename T>
    friend void swap(LinkedList<T>& l1, LinkedList<T>& l2);

public:
    LinkedList() : head(nullptr), size(0) {}

    LinkedList(const vector<Type>& v) : head(nullptr), size(0) {

        for(auto it=v.rbegin(); it!=v.rend(); ++it) push_front(*it);
    }

    LinkedList(const LinkedList& other) : head(new Node(other.head->value)), size(1) {

        Node* jumper = head;
        for(Node* o=other.head->next; o!=nullptr; o = o->next){

            jumper->next = new Node(o->value);
            ++size;
            jumper = jumper->next;
        }
    }

    LinkedList& operator=(LinkedList other){

        swap(*this, other);
        return *this;
    }

    ostream& to_ostream(ostream& output) const {

        output << "[ ";
        for(Node* jumper = head; jumper; jumper = jumper->next){
            output << jumper->value << " ";
        }
        output << "]";
        return output;
    }

    bool push_back(const Type& new_value){

        if(is_empty()) return push_front(new_value);

        node_at_index(size-1)->next = new Node(new_value, nullptr);
        return ++size; 
    }

    bool push_front(const Type& new_value) {
        
        // HEAD node is node a new node which the node after is the old HEAD
        // in case of empty list, old HEAD is nullptr and this line still works
        
        return (++size && (head = new Node(new_value, head)));
    }

    bool pop_front(){

        if(is_empty()) return false;

        Node* trash = head; // node to be deleted
        head = head->next;  // move head one node forward
        delete trash;       // delete old head
        return size--;
    }

    bool pop_back(){

        if(size<2) return pop_front();

        Node* second_last = node_at_index(size-2);
        delete second_last->next;
        second_last->next = nullptr;
        --size;
        return true;
    }

    bool remove(const size_t& index){

        if(index>=size) return false; // invalid index
        if(index==0) return pop_front(); // first index
        if(index==size-1) return pop_back(); // last index

        // index is in the middle
        Node* jumper = node_at_index(index-1);
        Node* trash = jumper->next;
        jumper->next = jumper->next->next;
        delete trash;
        return size--;
    }

    bool insert(const Type& new_value, const size_t& index){

        if(index<0 || index>size) return false;
        if(index==0) return push_front(new_value);
        if(index==size) return push_back(new_value);

        // index is in the middle
        Node* jumper = node_at_index(index-1);
        jumper->next = new Node(new_value, jumper->next);
        
        return ++size; 
    }

    bool replace(const size_t& index, const Type& new_value){

        Node* to_replace = node_at_index(index);

        if(to_replace) to_replace->value = new_value;
        return to_replace; // false if invalid index
    }

    bool contains(const Type& elt) const {

        for(Node* jumper = head; jumper; jumper = jumper->next){
            if(jumper->value == elt) return true;
        }
        return false;
    }

    Type& operator[](const size_t& index){

        Node* wanted = node_at_index(index);
        assert(wanted!=nullptr && "Index out of bounds");
        return wanted->value;
    }

    Type operator[](const size_t& index) const {

        Node* wanted = node_at_index(index);
        assert(wanted!=nullptr && "Index out of bounds");
        return wanted->value;
    }

    bool is_empty() const {
        return !head;
    }

    ~LinkedList(){
        while(pop_front());
    }
};

template<typename Type>
ostream& operator<<(ostream& output, const LinkedList<Type>& l){
    return l.to_ostream(output);
}

template<typename Type>
void swap(LinkedList<Type>& l1, LinkedList<Type>& l2){

    using std::swap;
    swap(l1.head, l2.head);
    swap(l1.size, l2.size);
}

int main(int argc, char* argv[]){

    LinkedList<int> l({1, 2, 3});

    cout << l << endl;

    return 0;
}