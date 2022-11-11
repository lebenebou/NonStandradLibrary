
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

public:
    PriorityQueue() : heap({}), size(0), comparator([](const Type& e1, const Type& e2){ return e1 > e2; }) {}

    void push(const Type& elt){

        assert(size == heap.size());
    }

    void display() const {

        cout << "[ ";
        for(const Type& elt : heap) cout << elt << " ";
        cout << "]";
    }

    size_t count() const {
        return size;
    }

    bool is_empty() const {
        return size==0;
    }
};

int main(){

    PriorityQueue<int> q;
    q.push(1);
    q.push(2);

    q.display();

    return 0;
}