#include <iostream>
#include "graph.h"

int main(int argc, char**argv)
{
    Graph<int> g;
    g.addEdge(0, 1, 2);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.removeEdge(0, 2);
    Graph<int>::AdjInfoList adjList = g.findAdjInfoList(0);

    return 0;
}