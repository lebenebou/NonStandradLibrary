
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
        : value(v), right(r), left(l);
    }

    size_t count;
    Node* root;

public:
    BST() : root(nullptr), size(0) {}
};