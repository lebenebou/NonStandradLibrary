

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename Type>
class BST{

private:

    struct Node{

        Type value;
        Node* right;
        Node* left;

        Node(const Type& v, Node* r =nullptr, Node* l =nullptr)
        : value(v), right(r), left(l) {}
    };

    size_t count;
    Node* root;

    bool insert(const Type& new_value, Node* start){

        if(is_empty()) return (++count && (root = new Node(new_value)));
        
        if(new_value == start->value) return false; // duplicate value

        if(new_value > start->value){

            if(!start->right) return (++count && (start->right = new Node(new_value)));
            return insert(new_value, start->right);
        }
        else{

            if(!start->left) return (++count && (start->left = new Node(new_value)));
            return insert(new_value, start->left);
        }
        return false;
    }

    bool find(const Type& elt, Node* start) const {

        if(!start) return false;
        if(elt == start->value) return true;

        if(elt > start->value) return find(elt, start->right);
        return find(elt, start->left);
    }

public:
    BST() : root(nullptr), count(0) {}

    bool insert(const Type& new_value){ return insert(new_value, root); }

    bool find(const Type& elt){ return find(elt, root); }

    bool is_empty() const { return !root; }
};

int main(int argc, char const *argv[])
{
    BST<int> myTree;

    myTree.insert(1);
    cout << myTree.find(0) << endl;
    cout << myTree.find(1) << endl;
    
    return 0;
}
