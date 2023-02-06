
#include <iostream>
#include <memory>
using namespace std;

class LinkedList{

    struct Node{

        short value;
        unique_ptr<Node> next;

        Node(const short& v, unique_ptr<Node> n = nullptr) : value(v), next(move(n)) {}
    };

    unique_ptr<Node> head;
    size_t size;

    Node* node_at_index(size_t index){

        if(index >= size) return nullptr;

        Node* jumper = head.get();
        while(index--) jumper = jumper->next.get();
        return jumper;
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    void push_back(const short& new_val){

        if(is_empty()){

            head = make_unique<Node>(new_val);
            size = 1;
            return;
        }

        node_at_index(size-1)->next = make_unique<Node>(new_val);
        ++size;
    }

    void push_front(const short& new_val){

        head = make_unique<Node>(new_val, move(head));
        ++size;
    }

    void debug() const {

        cout << "[ ";
        for(Node* jumper = head.get(); jumper != nullptr; jumper = jumper->next.get()){
            cout << jumper->value << " ";
        }
        cout << "] of size " << size << endl;
    }

    bool is_empty() const {
        return !head;
    }

    ~LinkedList() = default;
};

int main(){

    LinkedList l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(3);
    l.push_front(4);
    l.debug();    

    return 0;
}
