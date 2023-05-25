
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class UnionFind{

private:
    vector<int> parent;
    size_t comps;

public:
    UnionFind(const size_t& n) : parent(vector<int>(n, -1)), comps(n) {}

    bool join(size_t x, size_t y){

        size_t bx = find(x);
        size_t by = find(y);

        if(bx == by) return false; // cycle detected
        
        if(parent[bx] < parent[by]){ // x has more elements in its component

            parent[bx] += parent[by];
            parent[by] = bx;
        }
        else{ // y has more elements in his component

            parent[by] += parent[bx];
            parent[bx] = by;
        }

        --comps;
        return true;
    }

    size_t find(size_t x){

        size_t boss = x;
        while(parent[boss] > -1) boss = parent[boss];

        while(x != boss){
            
            if(parent[x]!=boss) parent[parent[x]] = boss;
            x = parent[x];
        }
        return boss;
    }

    size_t connected_comps() const {
        return comps;
    }

    void display() const {
        
        // display vector with brackets
        cout << "[";
        for(size_t i=0; i<parent.size(); ++i){
            cout << parent[i];
            if(i != parent.size()-1) cout << ", ";
        }
        cout << "]" << endl;
    }

    vector<int> content() const {
        return parent;
    }
};