#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
class PriorityQueue{
private:
    vector<Type> heap;

    int left(const int& index) const {

        int answer = index*2 + 1;
        return answer>=size() ? -1:answer;
    }

    int right(const int& index) const {

        int answer = index*2 + 2;
        return answer>=size() ? -1:answer;
    }

    int parent(const int& index) const {
        return index==0 ? -1 : (index-1)/2;
    }

    int better_child(const int& current) const {

        if(left(current)==-1 && right(current)==-1) return -1;
        if(left(current)==-1) return right(current);
        if(right(current)==-1) return left(current);

        return heap[right(current)] < heap[left(current)] ? left(current):right(current);
    }

public:
    PriorityQueue() = default;
    PriorityQueue(const vector<Type>& v) : PriorityQueue() {

        heap.reserve(v.size());
        for(const Type& elt : v) this->push(elt);
    }

    void push(const Type& new_value){

        heap.push_back(new_value);
        if(size() == 1) return; // queue was emtpy
        
        int p = parent(size()-1);
        int current = size()-1;

        while(p!=-1 && heap[p] < heap[current]){

            swap(heap[current], heap[p]);
            current = p;
            p = parent(current);
        }
    }

    void pop(){

        if(is_empty()) return;
        if(size() == 1) return heap.pop_back();

        swap(*heap.begin(), *heap.rbegin());
        heap.pop_back();

        int current = 0;
        int c = better_child(current);

        while(c!=-1 && heap[current] < heap[c]){

            swap(heap[current], heap[c]);
            current = c;
            c = better_child(current);
        }
    }

    Type top() const {
        return *heap.begin();
    }

    bool is_empty() const {
        return heap.begin() == heap.end();
    }

    int size() const {
        return this->heap.size();
    }
};

int main(int argc, char const *argv[])
{   
    PriorityQueue<string> q({"c", "a", "b"});

    while(!q.is_empty()){

        cout << q.top() << endl;
        q.pop();
    }

    return 0;
}