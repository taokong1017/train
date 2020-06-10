#include <queue>
#include "graph.h"

static int *prevList = nullptr;

template<typename T>
static T *distList = nullptr;

template<typename T>
//vertex, and Accumulate weight 
using vertexPair = std::pair<int, T>;

template<typename T>
struct greater
{
    bool operator()(const vertexPair<T>& left, const vertexPair<T>& right) {
        return left.second > right.second;
    }
};

template<typename T>
void singleSourceShortest(Graph<T>g, int s)
{
    // 初始化列表
    for(size_t i = 0; i < g.vertexNumber(); i++) {
        prevList[i] = -1;
        distList<T>[i] = std::numeric_limits<T>::max();
    }

    // 升序优先队列
    std::priority_queue<vertexPair<T>, std::vector<vertexPair<T>>, greater<T>> q;
    distList<T>[s] = 0;
    q.push(std::pair<int, T>(0, distList<T>[0]));

    while(!q.empty()) {
        vertexPair<T> mp = q.top();
        int u = mp.first;
        size_t nw = 0;
        for(const auto& ai : g.findAdjInfoList(u)) {
            int v = ai.first;
            T w = ai.second;
            nw = mp.second + w;
            if(nw < distList<T>[v]) {
                q.push(std::pair<int, T>(v, nw));
                prevList[v] = u;
                distList<T>[v] = nw;
            }
        }
        q.pop();
    }
}

template<typename T>
std::vector<vertexPair<T>> path(Graph<T>g, int s, int d)
{
    std::vector<vertexPair<T>> sdp;
    if (d >= static_cast<int>(g.vertexNumber())) {
        return sdp;
    }

    if(distList<T>[d] == std::numeric_limits<T>::max()) {
        return sdp;
    }

    int v = d;
    for(;;) {
        sdp.push_back(std::pair<int, T>(v, distList<T>[v]));
        if(v == s) break;
        v = prevList[v];
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
    Graph<size_t> g;
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 6, 1);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 7, 1);
    g.addEdge(7, 0, 2);
    int vNum = g.vertexNumber();
    prevList = new int[vNum];
    distList<size_t> = new size_t[vNum];
    singleSourceShortest<size_t>(g, 0);
    std::vector<vertexPair<size_t>> p = path(g, 0, 5);
    while(!p.empty()) {
        std::cout << "vertex: " << p.back().first 
            << ", len: " <<  p.back().second << std::endl;
        p.pop_back();
    }
    delete[] prevList;
    delete[] distList<int>;
    return 0;
}


