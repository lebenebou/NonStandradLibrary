
#include <iostream>
#include <vector>
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

        // list is not empty
        node_at_index(size-1)->next = new Node(new_value, nullptr);
        ++size;
        return true;
    }

    bool push_front(const Type& new_value) {
        
        head = new Node(new_value, head);
        ++size;
        return true;
    }

    bool pop_front(){

        if(is_empty()) return false;

        Node* trash = head;
        head = head->next;
        delete trash;
        --size;
        return true;
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

        if(index<0 || index>=size) return false;
        if(index==size-1) return pop_back();
        if(index==0) return pop_front();

        // index is in the middle
        Node* jumper = node_at_index(index-1);
        Node* trash = jumper->next;
        jumper->next = jumper->next->next;
        delete trash;
        --size;
        return true;
    }

    bool insert(const Type& new_value, const size_t& index){

        if(index<0 || index>size) return false;
        if(index==0) return push_front(new_value);
        if(index==size) return push_back(new_value);

        // index is in the middle
        Node* jumper = node_at_index(index-1);
        jumper->next = new Node(new_value, jumper->next);
        
        ++size;
        return true;
    }

    bool replace(const size_t& index, const Type& new_value){

        Node* to_replace = node_at_index(index);

        if(to_replace) to_replace->value = new_value;
        return to_replace;
    }

    bool contains(const Type& elt) const {

        for(Node* jumper = head; jumper; jumper = jumper->next){
            if(jumper->value == elt) return true;
        }
        return false;
    }

    Type& operator[](const size_t& index){

        Node* wanted = node_at_index(index);
        if(wanted) return wanted->value;
        else throw "Index out of bounds";
    }

    Type operator[](const size_t& index) const {

        Node* wanted = node_at_index(index);
        if(wanted) return wanted->value;
        else throw "Index out of bounds";
    }

    bool is_empty() const {
        return !head;
    }

    void display() const {

        cout << "Linked List: [ ";
        for(Node* jumper = head; jumper!=nullptr; jumper = jumper->next){
            cout << jumper->value << " ";
        }
        cout << "] of size " << size << endl;
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

    LinkedList<int> numbers({1, 12, 3, 5});

    if(numbers.insert(4, 3)) cout << "List of integers: " << numbers << endl;

    while(numbers.pop_front()) cout << "PopFront: " << numbers << endl;
    
    cout << endl;

    LinkedList<double> values({3.14, 2.71});

    if(values.push_back(1.61)) cout << "List of doubles: " << values << endl;

    while(values.pop_back()) cout << "PopBack: " << values << endl;

    return 0;
}