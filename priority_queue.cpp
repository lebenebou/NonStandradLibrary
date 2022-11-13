
#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;

template<typename Type>
class PriorityQueue{

private:
    vector<Type> heap;
    size_t size;
    function<bool(const Type& e1, const Type& e2)> comparator;

    void traverse(function<void(const Type& elt)> treat) const {
        for(const Type& elt : heap) treat(elt);
    }

    void pre_order(const int& start, function<void(const Type& elt)> treat) const {

        if(start == -1) return;

        treat(heap[start]);
        pre_order(left(start), treat);
        pre_order(right(start), treat);
    }

    int left(const int& i) const {

        int answer = (i+1)*2 - 1;
        if(answer>=size || i>=size) return -1;
        return answer;
    }

    int right(const int& i) const {
        
        int answer = (i+1)*2;
        if(answer>=size || i>=size) return -1;
        return answer;
    }

    int parent(const int& i) const {

        if(i<=0 || i>=size) return -1;
        return (i-1)/2;
    }

    bool is_leaf(const int& i) const {
        return left(i)==-1 && right(i)==-1;
    }

    int last_elt() const {
        return size-1;
    }

    int find(const Type& elt) const {

        for(int i=0; i<size; ++i){
            if(heap[i] == elt) return i;
        }
        return -1;
    }

    int better_elt(const int& e1, const int& e2) const {
        
        if(e1>=size && e2>=size) return -1;
        if(e1 >= size) return e2;
        if(e2 >= size) return e1;

        if(comparator(heap[e1], heap[e2])) return e1;
        return e2;
    }

    void bubble_up(int i){

        if(parent(i) == -1) return;

        while(comparator(heap[i], heap[parent(i)])){

            swap(heap[i], heap[parent(i)]);
            i = parent(i);

            if(i==-1) return;
        }
    }

    void bubble_down(int i){

        int m = better_elt(left(i), right(i));
        if(m == -1) return; // i has no children

        while(comparator(heap[m], heap[i])){
            
            swap(heap[m], heap[i]);
            i = m;

            m = better_elt(left(i), right(i));
            if(m == -1) return; // i has no children
        }
    }

public:
    PriorityQueue(function<bool(const Type& e1, const Type& e2)> comp = [](const Type& e1, const Type& e2){ return e1 > e2; }) : heap({}), size(0), comparator(comp) {}

    PriorityQueue(const vector<Type>& v, function<bool(const Type& e1, const Type& e2)> comp = [](const Type& e1, const Type& e2){ return e1 > e2; }){

        heap = {};
        size = 0;
        comparator = comp;

        for(const Type& elt : v) push(elt);
        assert(size == heap.size() && "heap size not equal to queue size");
    }

    PriorityQueue(const PriorityQueue<Type>& other) = default;

    ostream& to_ostream(ostream& output) const {

        output << "[ ";
        traverse([&output](const Type& elt)->void { output << elt << " "; });
        output << "]";
        return output;
    }

    void push(const Type& elt){

        heap.push_back(elt);
        assert(++size == heap.size() && "heap size not equal to queue size");
        bubble_up(last_elt()); // size-1 which was just inserted
    }

    void pop(){

        assert(size>0 && "cannot pop from empty queue");

        swap(heap[0], heap[last_elt()]);
        heap.pop_back();
        assert(--size == heap.size() && "heap size is not equal to queue size");
        bubble_down(0);
    }
    
    Type top() const {
        return heap[0];
    }

    bool remove(const Type& value){

        int f = find(value);
        if(f == -1) return false;

        swap(heap[f], heap[last_elt()]);
        heap.pop_back();
        assert(--size == heap.size() && "heap size is not equal to queue size");
        
        if(is_leaf(f)) bubble_up(f);
        else bubble_down(f);
        return true;
    }

    size_t count() const {
        return size;
    }

    bool is_empty() const {
        return size==0;
    }

    ~PriorityQueue() = default;
};

template<typename Type>
ostream& operator<<(ostream& output, const PriorityQueue<Type>& pq){
    return pq.to_ostream(output);
}

int main(){

    PriorityQueue<int> q({1, 4, 100, -10, 101});
    cout << "Priority Queue: " << q << endl;

    while(!q.is_empty()){

        cout << q.top() << endl;
        q.pop();
    }

    return 0;
}