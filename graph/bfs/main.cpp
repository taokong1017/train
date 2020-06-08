#include <queue>
#include "graph.h"

static int *prevList = nullptr;
static bool *visitedList = nullptr;

template<typename T>
void breadthFirstSearch(Graph<T>g, int u)
{
    // 初始化列表
    for(size_t i = 0; i < g.vertexNumber(); i++) {
        prevList[i] = -1;
        visitedList[i] = false;
    }

    std::queue<int> q;
    q.push(u);
    while(!q.empty()) {
        int h = q.front();
        visitedList[h] = true;
        auto l = g.findAdjInfoList(h);
        for(auto e : l) {
            int v = e.first;
            if(!visitedList[v]) {
                q.push(v);
                prevList[v] = h;
            }
        }
        q.pop();
    }
}

template<typename T>
std::vector<int> path(Graph<T>g, int s, int d)
{
    std::vector<int> sdp;
    bool fs = visitedList[s];
    bool fd = visitedList[d];
    bool found = false;
    int v = d;
    if(fs && fd) {
        while(visitedList[v]) {
            sdp.push_back(v);
            if (v == s) {
                found = true;
                break;
            }
            v = prevList[v];
        }
        if(!found) {
            sdp.clear();
        }
    }
    return sdp;
}

/*
*     0 ----> 1 -----> 2 -----> 4
*     |       \                  \
*     |        >                  >
*     |         3 ----> 5 -------> 6 ---> 7
*     |                                   |
*      ----------------------------------<
*/
int main(int argc, char**argv)
{
    Graph<int> g;
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 0);
    int vNum = g.vertexNumber();
    prevList = new int[vNum];
    visitedList = new bool[vNum];
    breadthFirstSearch(g, 0);
    std::vector<int> p = path(g, 0, 4);
    std::cout << "path 0 -> 4 : ";
    while(!p.empty()) {
        std::cout << p.back() << " ";
        p.pop_back();
    }
    std::cout << std::endl;
    delete[] prevList;
    delete[] visitedList;
    return 0;
}


