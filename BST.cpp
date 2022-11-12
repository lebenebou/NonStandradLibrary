
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template<typename Type>
class BST{

private:

    struct Node{

        Type value;
        Node* left;
        Node* right;

        Node(const Type& v) : value(v), left(nullptr), right(nullptr){}
    };

    typedef function<void(Node*&)> node_processor;
    typedef function<bool(const Type&, const Type&)> comp_type;

    Node* root;
    size_t size;

    comp_type comparator;
    comp_type equalizer;
    
    bool insert(Node*& start, const Type& new_value){

        if(equalizer(new_value, start->value)) return false;

        if(comparator(new_value, start->value)){

            if(!start->left){
                start->left = new Node(new_value);
                return ++size;
            }

            return insert(start->left, new_value);
        }

        else { // !comparator(new_value, start->value)

            if(!start->right){
                start->right = new Node(new_value);
                return ++size;
            }

            return insert(start->right, new_value);
        }
    }

    bool contains(Node* start, const Type& elt) const {

        if(!start) return false;
        if(equalizer(elt, start->value)) return true;

        if(comparator(elt, start->value)) return contains(start->left, elt);
        return contains(start->right, elt);
    }

    void in_order(Node* start, node_processor process) const {

        if(!start) return;

        in_order(start->left, process);
        process(start);
        in_order(start->right, process);
    }

    void pre_order(Node* start, node_processor process) const {

        if(!start) return;

        process(start);
        pre_order(start->left, process);
        pre_order(start->right, process);
    }

    void post_order(Node* start, node_processor process) const {

        if(!start) return;

        post_order(start->left, process);
        post_order(start->right, process);
        process(start);
    }

public:
    BST(comp_type comp = [](const Type& a, const Type& b)->bool { return a < b; }, comp_type equ = [](const Type& a, const Type& b)->bool { return a == b; }){
        
        root = nullptr;
        size = 0;
        comparator = comp;
        equalizer = equ;
    }

    BST(const vector<Type>& v, comp_type comp = [](const Type& a, const Type& b)->bool { return a < b; }, comp_type equ = [](const Type& a, const Type& b)->bool { return a == b; }){
        
        root = nullptr;
        size = 0;
        comparator = comp;
        equalizer = equ;

        for(const Type& elt : v) insert(elt);
    }

    bool insert(const Type& new_value){

        if(is_empty()){

            ++size;
            return root = new Node(new_value);
        }

        return insert(root, new_value);
    }

    bool contains(const Type& elt) const {
        return contains(root, elt);
    }

    bool is_empty() const {
        return !root;
    }

    void display(const short& traversal_type = 1) const {

        cout << "[ ";

        switch (traversal_type){
            
            case 1:
                in_order(root, [](Node*& n)->void { cout << n->value << " "; });
                break;

            case 2:
                pre_order(root, [](Node*& n)->void { cout << n->value << " "; });
                break;

            default:
                post_order(root, [](Node*& n)->void { cout << n->value << " "; });
                break;
        }

        cout << "]" << endl;
    }

    ~BST(){
        post_order(root, [](Node*& n)->void { delete n; });
    }
};

int main(){

    BST<int> tree({2, 1, 3});
    
    cout << tree.contains(1) << endl;

    return 0;
}