
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include "../LinkedLists.cpp"
using namespace std;

string to_string(LinkedList<int>& l){

    stringstream answer;
    answer << l;
    return answer.str();
}

void basicTest(LinkedList<int>& l){

    l.clear();
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
}

void copyTest(LinkedList<int>* l){

    
}

int main(int argc, char const *argv[]){

    SinglyLinkedList<int> l;
    basicTest(l);


    cout << "Passed all tests." << endl;

    return 0;
}