
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class LinkedList{

    struct Node{

        short value;
        unique_ptr<Node> next;

        Node(short val, unique_ptr<Node> ptr) : value(val), next(move(ptr)) {}
    };

    Node* node_at_index(size_t index) const {

        Node* jumper = head.get();
        while(index--) jumper = jumper->next.get();
        return jumper;
    }

    unique_ptr<Node> head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    bool push_front(const short& new_value){

        head = make_unique<Node>(new_value, move(head));
        return ++size;
    }

    bool push_back(const short& new_value){

        if(is_empty()) return push_front(new_value);

        node_at_index(size-1)->next = make_unique<Node>(new_value, nullptr);
        return ++size;
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

    ~LinkedList() = default;
};

int main(int argc, char const *argv[]){

    LinkedList l;
    for(int i=1; i<=10; ++i) l.push_front(i);

    l.debug();
    return 0;
}