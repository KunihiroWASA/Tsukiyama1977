#include <iostream>
#include <map>
#include <vector>

typedef int                     Node;
typedef std::vector<Node>       AdjList;
typedef std::map<Node, AdjList> Graph;

class MIS {
    std::map<Node, int> IS; 
    std::map<Node, std::vector<Node>> Bucket; 
    int n; 
    Graph __g; 

    void BACKTRACK(Node i); 
    void OUTPUT(); 
    public:
        void MAIN(Graph & g); 
};



int main(int argc, char const* argv[])
{
    // Adjacent lists must be sorted. 
    Graph g = {
        {1, {}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {2, 3}}
    };

    MIS m; 
    m.MAIN(g);  

    return 0;
}

void MIS::MAIN(Graph & g) {
    __g = g;
    n   = g.size();
    for (Node j = 1; j <= n; ++j) {
        IS[j] = 0; 
        Bucket[j].clear(); 
    }
    BACKTRACK(1); 
}

void MIS::BACKTRACK(Node i)
{
    Node c, x;
    bool f; 

    if (i < n) {
        x = i + 1; 
        c = 0; 

        for (auto& y : __g[x]) {
            if (y <= i) {
                if (IS[y] == 0) {
                    c = c + 1; 
                }
            }
        }
        if (c == 0) {
            for (auto& y: __g[x]) {
                if (y <= i) {
                    IS[y] = IS[y] + 1; 
                }
            }
            BACKTRACK(x); 
            for (auto& y: __g[x]) {
                if (y <= i) {
                    IS[y] = IS[y] - 1; 
                }
            }
        } else {
            IS[x] = c; 
            BACKTRACK(x); 
            IS[x] = 0; 
            f = true; 
            for (auto& y : __g[x]) { // increasing ordering
                if (1 <= y and y <= i) {
                    if (IS[y] == 0) {
                        Bucket[x].push_back(y); 
                        for (auto& z : __g[y]) {
                            if (z <= i) {
                                IS[z] = IS[z] - 1;
                                if (IS[z] == 0) {
                                    f = false;
                                }
                            }
                        }
                    }
                    IS[y] = IS[y] + 1;
                }
            }
            if (f == true) {
                BACKTRACK(x); 
            }
            for (auto& y: __g[x]) {
                if (y <= i) {
                    IS[y] = IS[y] - 1; 
                }
            }
            for (auto& y : Bucket[x]) {
                for (auto& z : __g[y]) {
                    if (z <= i) {
                        IS[z] = IS[z] + 1;
                    }
                }
            }
            Bucket[x].clear(); 
        }
    } else {
        OUTPUT(); 
    }
    return; 
}

void MIS::OUTPUT() 
{
    std::cout << "IS: "; 
    for (auto& i: IS) {
        if (i.second == 0) {
            std::cout << i.first  << " "; 
        }
    } 
    std::cout << std::endl; 
    return; 
}
