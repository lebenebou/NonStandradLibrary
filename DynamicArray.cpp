
#include <iostream>
using namespace std;

template<typename Type>
class DynamicArray{

private:
    Type* p;
    size_t count;
    size_t cap;

    void double_capacity(){

        Type* new_p = new Type[cap*=2];
        for(size_t i=0; i<count; ++i) new_p[i] = p[i];
        std::swap(new_p, p);
        delete new_p;
    }

public:
    DynamicArray() : count(0), cap(8), p(new Type[10]){}

    void display() const {
        
        cout << "[ ";
        for(size_t i=0; i<count; ++i) cout << p[i] << " ";
        cout << "]";
    }

    void push_back(const Type& new_value){

        if(count == cap) double_capacity();
        p[count++] = new_value;
    }

    void push_front(const Type& new_value){
        insert(new_value);
    }

    bool insert(const Type& new_value, const size_t& index = 0){

        if(index<0 || index>count) return false;
        if(count == cap) double_capacity();

        for(size_t i=count; i>=index+1; --i) p[i] = p[i-1];

        p[index] = new_value;
        ++count;
        return true;
    }

    bool pop_back(){
        
        if(count==0) return false;
        return count--;
    }

    bool pop_front(){
        return remove(0);
    }

    bool remove(const size_t& index){

        if(index<0 || index>=count) return false;
        if(count<2) return pop_back();

        for(size_t i=index; i<count; ++i) p[i] = p[i+1];
        --count;
        return true;
    }

    Type& operator[](const size_t& index){
        return p[index];
    }

    Type operator[](const size_t& index) const {
        return p[index];
    }

    size_t capacity() const {
        return cap;
    }

    size_t size() const {
        return count;
    }

    bool is_empty() const {
        return count==0;
    }

    void clear(){
        count = 0;
    }

    ~DynamicArray(){
        delete[] p;
    }
};

int main(int argc, char* argv[]){

    DynamicArray<int> v;

    int i = 10;
    while(--i + 1) v.push_back(10-i);

    v.display(); cout << endl;

    while(v.pop_front()) v.display(); cout << endl;
    
    
    return 0;
}