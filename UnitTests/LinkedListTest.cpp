
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <memory>
#include "../LinkedLists.cpp"
using namespace std;

string to_string(LinkedList<int>& l){

    stringstream answer;
    answer << l;
    return answer.str();
}

void basicTest(LinkedList<int>& l){

    assert(l.is_empty() && l.length()==0 && "list is not empty on intialization");

    for(int i=1; i<=5; ++i) l.push_back(i);
    assert(to_string(l)=="[ 1 2 3 4 5 ]" && "pushBack order is wrong");
    
    for(int i=1; i<=2; ++i) l.pop_front();
    assert(to_string(l)=="[ 3 4 5 ]" && "popFront order is wrong");
    
    for(int i=1; i<=2; ++i) l.pop_back();
    assert(to_string(l)=="[ 3 ]" && "popBack order is wrong");

    assert(!l.is_empty() && l.length()==1 && "list length is incorrect, should be 1");

    l.remove(0);
    assert(l.is_empty() && l.length()==0 && "list length is incorrect, should be 0");
    
    for(int i=1; i<=5; ++i) l.push_front(i);
    assert(to_string(l)=="[ 5 4 3 2 1 ]" && "push_front order is wrong");

    l.insert(13, 2);
    assert(to_string(l)=="[ 5 4 13 3 2 1 ]" && "insert order is wrong");

    l.remove(2);
    assert(to_string(l)=="[ 5 4 3 2 1 ]" && "remove order is wrong");

    l.clear();
}

template<typename ConcreteLinkedList>
void copyTest(LinkedList<int>* l){

    l->clear();
    for(int i=1; i<=5; ++i) l->push_back(i);

    ConcreteLinkedList listCopy(*static_cast<ConcreteLinkedList*>(l));

    assert(l->length() == listCopy.length() && "list copy does not have same size");
    assert(to_string(*l)==to_string(listCopy) && "list copy does not have same content");

    for(int i=0; i<l->length(); ++i){
        assert(&l->operator[](i) != &listCopy[i] && "list copy element has same address");
    }

    l->pop_front();
    assert(l->length() < listCopy.length() && "copy size changed when original size changed");

    listCopy = *static_cast<ConcreteLinkedList*>(l);

    assert(l->length() == listCopy.length() && "list copy does not have same size (op=)");
    assert(to_string(*l)==to_string(listCopy) && "list copy does not have same content (op=)");
    
    for(int i=0; i<l->length(); ++i){
        assert(&l->operator[](i) != &listCopy[i] && "list copy element has same address (op=)");
    }
}

int main(int argc, char const *argv[]){

    LinkedList<int>* myList = new SinglyLinkedList<int>();
    
    basicTest(*myList);
    copyTest<SinglyLinkedList<int>>(myList);

    cout << "Passed all tests." << endl;

    return 0;
}