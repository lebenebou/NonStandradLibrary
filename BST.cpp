
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>
using namespace std;

// this cpp file is not for the faint of heart

template<typename Type>
class BST{

private:

    struct Node {

        Node(const Type& v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r){}

        Type value;
        Node* left;
        Node* right;
    };

    Node* root;
    size_t size;

    template<typename T>
    friend void swap(BST<T>& t1, BST<T>& t2);

    bool insert(const Type& elt, Node* start){

        if(!start){
            root = new Node(elt);
            return size=1;
        }

        if(elt > start->value){

            if(start->right) return insert(elt, start->right);
            else {
                start->right = new Node(elt);
                ++size;
                return true;
            }
        }

        else if(elt < start->value) {

            if(start->left) return insert(elt, start->left);
            else {
                start->left = new Node(elt);
                ++size;
                return true;
            }
        }
        return false;
    }

    bool contains(const Type& elt, Node* start) const {

        if(!start) return false;
        if(start->value == elt) return true;

        if(elt > start->value) return contains(elt, start->right);
        else return contains(elt, start->left);
    }

    size_t height(Node* start) const {

        if(!start) return 0;

        return 1 + std::max(height(start->left), height(start->right));
    }

    Node* node_of_max_value(Node* start) const {

        if(!start) return nullptr;

        while(start->right) start = start->right;
        return start;
    }

    Node* node_of_min_value(Node* start) const {

        if(!start) return nullptr;

        while(start->left) start = start->left;
        return start;
    }

    void in_order(Node* start, function<void(Node*&, const int&, const int&)> treat, const int& depth = 0, const int& offset = 0) const {

        if(!start) return;

        in_order(start->left, treat, depth+1, offset-1);
        treat(start, depth, offset);
        in_order(start->right, treat, depth+1, offset+1);
    }

    void pre_order(Node* start, function<void(Node*&, const int&, const int&)> treat, const int& depth = 0, const int& offset = 0) const {

        if(!start) return;

        treat(start, depth, offset);
        pre_order(start->left, treat, depth+1, offset-1);
        pre_order(start->right, treat, depth+1, offset+1);
    }

    void post_order(Node* start, function<void(Node*&, const int&, const int&)> treat, const int& depth = 0, const int& offset = 0) const {

        if(!start) return;

        post_order(start->left, treat, depth+1, offset-1);
        post_order(start->right, treat, depth+1, offset+1);
        treat(start, depth, offset);
    }

    void bfs(Node* start, function<void(Node*&)> treat) const {

        if(!start) return;

        queue<Node*> q;
        q.push(start);

        while(!q.empty()){

            Node* current_node = q.front();
            treat(current_node);
            q.pop();

            if(current_node->left) q.push(current_node->left);
            if(current_node->right) q.push(current_node->right);
        }
    }

    priority_queue<pair<int, Type>> get_priority_queue(const bool& depth_based = false, const bool& upside_down = false) const {

        const short sign = (upside_down ? 1:-1); // this inverts the priority in the queue (priority is for larger values by default)

        priority_queue<pair<int, Type>> q;
        pre_order(root, [&q, sign, depth_based, upside_down](Node*& n, const int& depth, const int& offset) -> void

        { q.push({sign * (depth_based ? depth:offset), sign * n->value }); });

        return q;
    }

public:

    BST(){
        root = nullptr;
        size = 0;
    }

    BST(const vector<Type>& v) : root(nullptr), size(0){
        for(const Type& elt : v) insert(elt);
    }

    BST(const BST& other) : root(nullptr), size(0){

        bfs(other.root, [this](Node*& n)->void { this->insert(n->value); });
    }

    BST& operator=(BST<Type> other) const {

        swap(other, *this);
        return *this;
    }

    ostream& to_ostream(ostream& output) const {

        output << "[ ";
        bfs(root, [&output](Node*& n)->void { output << n->value << " "; });
        output << "]";
        return output;
    }

    bool insert(const Type& elt){

        return insert(elt, root);
    }

    bool contains(const Type& elt) const {
        return contains(elt, root);
    }

    size_t height() const {

        if(is_empty()) return 0;
        
        priority_queue<int> heights;
        pre_order(root, [&heights](Node*&, const int& depth, const int&)->void { heights.push(depth); });
        return heights.top()+1;
    }

    Type max_value() const {
        return node_of_max_value(root)->value;
    }

    Type min_value() const {
        return node_of_min_value(root)->value;
    }

    Type full_sum() const {

        Type answer = 0;
        bfs(root, [&answer](Node*& n){ answer += n->value; });
        return answer;
    }

    Type full_product() const {

        Type answer = 1;
        bfs(root, [&answer](Node*& n){ answer *= n->value; });
        return answer;
    }

    void display(const short& type = 1) const {

        function<void(Node*& n, const int&, const int&)> print =
        [](Node*& n, const int&, const int&){ cout << n->value << " "; };
        
        cout << "[ ";
        switch(type){

            case 1:
                in_order(root, print);
                break;
            case 2:
                pre_order(root, print);
                break;
            case 3:
                post_order(root, print);
                break;
            default:
                bfs(root, [](Node*& n)->void { cout << n->value << " ";} );
                break;
        }
        cout << "]" << endl;
    }

    void vertical_display(bool right_to_left = true) const {

        auto q = get_priority_queue(false, right_to_left);
        const short sign = (right_to_left ? 1:-1);

        cout << "[ ";
        while(!q.empty()){

            cout << sign * q.top().second << " ";
            q.pop();
        }
        cout << "]" << endl;
    }

    void horizontal_display(bool upside_down = true) const {

        auto q = get_priority_queue(true, upside_down);
        const short sign = (upside_down ? 1:-1);

        cout << "[ ";
        while(!q.empty()){

            cout << sign * q.top().second << " ";
            q.pop();
        }
        cout << "]" << endl;
    }

    map<Type, int> levels() const {

        map<Type, int> answer;
        if(size<2) return answer;

        pre_order(root, [&answer](Node*& n, const int& depth, const int&) -> void {

            answer[n->value] = depth;
        });

        return answer;
    }

    size_t node_count() const {
        return size;
    }

    size_t count_nodes() const {

        size_t answer = 0;
        pre_order(root, [&answer](Node*& n)->void { ++answer; });
        return answer;
    }

    bool is_empty() const {
        return !root;
    }

    ~BST(){
        post_order(root, [](Node*& n, const int&, const int&)-> void { delete n; });
    }
};

template<typename Type>
void swap(BST<Type>& t1, BST<Type>& t2){

    std::swap(t1.root, t2.root);
    std::swap(t1.size, t2.size);
}

template<typename Type>
ostream& operator<<(ostream& output, const BST<Type>& tree){

    return tree.to_ostream(output);
}

int main(int argc, char* argv[]){

    BST<int> tree({25, 20, 36, 30, 40, 10, 22, 5, 12, 28, 38, 48});
    cout << endl << "Link to view this tree: https://www.gatevidyalay.com/wp-content/uploads/2018/07/Binary-Search-Tree-Example.png" << endl << endl;

    short bfs;
    cout << "BFS Display:\t\t";
    tree.display(bfs = 4);

    short in_order;
    cout << "InOrder Display:\t";
    tree.display(in_order = 3);

    bool right_to_left;
    cout << "Right to left:\t\t";
    tree.vertical_display(right_to_left = true);

    cout << "Left to right:\t\t";
    tree.vertical_display(right_to_left = false);

    bool upside_down;
    cout << "Upside down display:\t";
    tree.horizontal_display(upside_down = true);

    cout << endl << "Levels (depth):" << endl;

    for(const auto& duo : tree.levels()){ // this is a map

        cout << duo.first << " at level " << duo.second << endl;
    }

    auto t2 = tree;

    return 0;
}