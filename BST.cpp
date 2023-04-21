
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
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

        if(isEmpty()) return (++count && (root = new Node(new_value)));
        
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

    typedef function<void(Node*)> processor;

    void bfs(Node* start, const processor& process){

        if(!start) return;

        queue<Node*> q;
        q.push(start);

        while(!q.empty()){

            Node* current = q.front();
            q.pop();

            process(current);
            if(current->right) q.push(current->right);
            if(current->left) q.push(current->left);
        }
    }

    void preOrder(Node* start, const processor& process) const {

        if(!start) return;

        process(start);
        preOrder(start->left, process);
        preOrder(start->right, process);
    }

    void inOrder(Node* start, const processor& process) const {

        if(!start) return;

        inOrder(start->left, process);
        process(start);
        inOrder(start->right, process);
    }

    void postOrder(Node* start, const processor& process) const {

        if(!start) return;

        postOrder(start->left, process);
        postOrder(start->right, process);
        process(start);
    }

public:
    BST() : root(nullptr), count(0) {}

    bool insert(const Type& new_value){ return insert(new_value, root); }

    bool find(const Type& elt){ return find(elt, root); }

    bool isEmpty() const { return !root; }

    void display(short type = 1){

        const auto toCout = [](Node* n) -> void { cout << n->value << " "; };

        cout << "[ ";

        switch (type){
        
            case 1:
                preOrder(root, toCout);
                break;
                
            case 2:
                inOrder(root, toCout);
                break;
            
            case 3:
                postOrder(root, toCout);
                break;
            
            default:
                bfs(root, toCout);
                break;
        }

        cout << "] of size " << count << endl;
    }
};

int main(int argc, char const *argv[])
{
    BST<int> myTree;

    myTree.insert(1);
    myTree.display(4);
    
    return 0;
}
