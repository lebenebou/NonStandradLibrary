
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

        Node(const Type& v, Node* r = nullptr, Node* l = nullptr)
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

    // Traversals using a processor
    typedef function<void(Node*)> processor;

    void bfs(Node* start, const processor& process) const {

        if(!start) return;

        queue<Node*> q;
        q.push(start);

        while(!q.empty()){

            Node* current = q.front();
            q.pop();

            process(current);
            if(current->left) q.push(current->left);
            if(current->right) q.push(current->right);
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

    template<typename T>
    friend void swap(BST<T>&, BST<T>&);

public:
    BST(const vector<Type>& v = {}) : root(nullptr), count(0) {
        for(const auto& elt : v) this->insert(elt);
    }
    
    BST(const BST<Type>& other) : BST() {
        other.bfs(other.root, [this](Node* n) -> void { this->insert(n->value); });
    }
    
    BST<Type>& operator=(const BST<Type>& other){

        if(this == &other) return *this;

        BST<Type> treeCopy = BST(other);
        swap(*this, treeCopy);
        return *this;
    }

    ostream& toOstream(ostream& output) const {
        
        output << "[ ";
        inOrder(root, [&output](Node* n) -> void{ output << n->value << " "; });
        output << ']';
        return output;
    }

    void display(short type = 1){

        const auto toCout = [](Node* n) -> void { cout << n->value << " "; };

        cout << "[ ";

        switch (type){
        
            case 1:
                inOrder(root, toCout);
                break;
                
            case 2:
                preOrder(root, toCout);
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

    bool insert(const Type& new_value){ return insert(new_value, root); }

    bool find(const Type& elt){ return find(elt, root); }

    bool isEmpty() const { return !root; }

    ~BST(){
        postOrder(root, [](Node* n) -> void{ delete n; });
    }
};

template<typename Type>
ostream& operator<<(ostream& output, const BST<Type>& tree){ return tree.toOstream(output); }

template<typename Type>
void swap(BST<Type>& tree1, BST<Type>& tree2){

    using std::swap;
    swap(tree1.root, tree2.root);
    swap(tree1.count, tree2.count);
}

int main(int argc, char const *argv[]){

    BST<int> myTree({2, 1, 3});

    cout << myTree << endl;
    
    return 0;
}
