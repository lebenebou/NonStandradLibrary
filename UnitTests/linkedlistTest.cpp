
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "../LinkedList.cpp"
using namespace std;

string to_string(LinkedList<int> l){

    if(l.is_empty()) return "";
    
    string answer = "";
    while(!l.is_empty()){

        answer += to_string(l[0]);
        l.pop_front();
    }
    return answer;
}

void basicTest(){

    LinkedList<int> l;
    assert(l.length()==0 && "Initialized list is not empty");

    int i=5;
    while(i--) l.push_front(i);
    assert(to_string(l)=="01234" && "push front order is wrong");

    l.clear();
    assert(l.length()==0 && "Initialized list is not empty");

    i=5;
    while(i--) l.push_back(i);
    assert(to_string(l)=="43210" && "push back order is wrong");

    l.pop_back();
    assert(to_string(l)=="4321" && "pop back order is wrong");

    l.pop_front();
    assert(to_string(l)=="321" && "pop front order is wrong");
}

void lengthTest(){

    LinkedList<int> l;
    assert(l.is_empty() &&  "Initialized list is not empty");
    assert(l.length()==0 &&  "Initialized list is not empty");

    int i=5;
    while(i--) l.push_front(i);

    assert(l.length()==5 && "Incorrect list length, should be 5.");

    i=3;
    while(i--) l.pop_front();
    assert(l.length()==2 && "Incorrect list length, should be 2.");
    
    i=2;
    while(i--) l.pop_back();
    assert(l.length()==0 && "Incorrect list length, should be 0.");
}

void operatorTest(){

    
}

int main(int argc, char const *argv[]){

    basicTest();
    lengthTest();

    cout << "Passed all tests." << endl;
    return 0;
}
