
#include <iostream>
#include <vector>
using namespace std;

class UnionFind{

    vector<signed int> parent;
    bool collapsed;

    public:
        UnionFind(const size_t& n){

            vector<signed int> tmp(n, -1);
            parent = tmp;
            collapsed = false;
        }

        signed int find(size_t elt){

            if(collapsed){
                cout << "Cannot find " << elt << ", this instance is collapsed" << endl;
                return 0;
            }

            while(parent[elt] >= 0){

                if(parent[parent[elt]] >= 0) parent[elt] = parent[parent[elt]]; // for optimization
                elt = parent[elt];
            }
            return elt;
        }

        bool join(const size_t& e1, const size_t& e2){
            
            if(collapsed){
                cout << "Cannot perform join operation, this instance is collapsed" << endl;
                return false;
            }

            const int& p1 = find(e1);
            const int& p2 = find(e2);

            if(p1 == p2) return false;
            // cycle detected

            if(parent[p1] > parent[p2]){
                parent[p2] += parent[p1];
                parent[p1] = p2;
            }

            else{
                parent[p1] += parent[p2];
                parent[p2] = p1;
            }           
            
            return true;
        }

        void collapse(){

            vector<int> roots;
            for(size_t i=0; i<parent.size(); i++){
                
                const auto& elt = parent[i];
                if(elt >=0) roots.push_back(find(elt));
                if(elt < 0) roots.push_back(i);
            }
            parent = roots;
            collapsed = true;
        }

        size_t size() const {
            return parent.size();
        }

        vector<signed int> contents() const {
            return parent;
        }

        void display() const {

            for(const auto& elt : parent) cout << elt << " ";
            cout << endl;
        }
};

int main(){

    const size_t N = 4;
    UnionFind uf(N+1);

    if(uf.join(1, 2)) cout << "Joined" << endl;
    if(uf.join(2, 3)) cout << "Joined" << endl;

    uf.display();    

    return 0;
}