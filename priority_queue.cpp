
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

template<typename Type>
class PriorityQueue{

private:
    typedef function<bool(const Type&, const Type&)> comp_type;
    typedef function<void(const Type&)> element_processor;

    vector<Type> heap;
    comp_type comparator;

    void traverse(const element_processor& process) const {
        
        for(const Type& elt : heap) process(elt);
    }

    void pre_order(const int& start, const element_processor& process) const {
        
        if(start == -1 || is_empty()) return;

        process(heap[start]);
        pre_order(left(start), process);
        pre_order(right(start), process);
    }

    int validate(const size_t& index) const {
        
        if(index >= size()) return -1;
        return index;
    }

    int left(const size_t& index) const {
        return validate((index+1)*2 - 1);
    }

    int right(const size_t& index) const {
        return validate((index+1)*2);
    }

    int parent(const size_t& index) const {
        
        if(index==0 || index>=size()) return -1;
        return (index+1)/2 - 1;
    }

    // returns last element index
    int last_elt() const {
        return size()-1;
    }

    // returns index of higher priority
    int better_elt(const size_t& e1, const size_t& e2) const {

        if(e1 >= size() && e2>=size()) return -1;
        if(e1 >= size()) return e2;
        if(e2 >= size()) return e1;

        if(comparator(heap[e1], heap[e2])) return e1;
        return e2;
    }

    void bubble_up(size_t index){

        if(parent(index) == -1) return;

        while(comparator(heap[index], heap[parent(index)])){

            swap(heap[index], heap[parent(index)]);
            index = parent(index);

            if(parent(index) == -1) return;
        }
    }

    void bubble_down(size_t index){

        int m = better_elt(left(index), right(index));
        if(m == -1) return; // index is at a leaf (no children)

        while(comparator(heap[m], heap[index])){

            swap(heap[m], heap[index]);

            index = m;
            m = better_elt(left(index), right(index));

            if(m == -1) return; // index reached a leaf
        }
    }

public:
    PriorityQueue(const comp_type& comp = [](const Type& e1, const Type& e2){ return e1 > e2; }) : heap({}), comparator(comp) {}
    
    PriorityQueue(const vector<Type>& v, const comp_type& comp = [](const Type& e1, const Type& e2){ return e1 > e2; }) : heap({}), comparator(comp) {
        for(const Type& elt : v) this->push(elt);
    }

    void push(const Type& value){

        heap.push_back(value);
        bubble_up(last_elt());
    }

    void pop(){

        if(is_empty()) throw "Cannot pop from empty queue";

        swap(heap[0], heap[last_elt()]);
        heap.pop_back();
        bubble_down(0);
    }

    Type top() const {
        return heap[0];
    }

    void display() const {
        
        cout << "[ ";
        traverse([](const Type& elt){ cout << elt << " "; });
        cout << "]" << endl;
    }

    size_t size() const {
        return heap.size();
    }

    bool is_empty() const {
        return size()==0;
    }
};

int main(int argc, char* argv[]){

    PriorityQueue<int> pq({10, 11, 13, -2, 200});

    pq.display();

    while(!pq.is_empty()){

        cout << pq.top() << endl;
        pq.pop();
    }

    return 0;
}