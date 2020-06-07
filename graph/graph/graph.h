#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>


template<typename T>
class Graph
{
public:
    enum VertexColor
    {
        White,
        Gray,
        Black,
    };
    enum EdgeType
    {
        Tree,
        Backward,
        Forward,
        Cross,
    };
    //对于每个顶点u，将权值为w的边(u, v)的信息(v, w)存放于此
    using AdjInfo = std::pair<int, T>;
    //顶点的邻接表
    using AdjInfoList = std::vector<AdjInfo>;
    using VertexAdjList = std::pair<int, AdjInfoList>;

public:
    Graph(){}
    virtual ~Graph(){}
    inline const int& vertexNumber() const {return mAdjList.size();}
    bool isEdge(int u, int v)
    {
        for(auto & adjList : mAdjList) {
            if(adjList.first == u) {
                for(auto& adjInfo : adjList.second) {
                    if (adjInfo.first == v)
                        return true;
                }
            }
        }
        return false;
    }

    bool isEdge(int u, int v, T& weight) 
    {
        for(auto & adjList : mAdjList) {
            if(adjList.first == u) {
                for(auto& adjInfo : adjList.second) {
                    if (adjInfo.first == v) {
                        weight = adjInfo.second;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void addEdge(int u, int v, T weight = 1) {
        auto uIter = std::find_if(mAdjList.begin(), mAdjList.end(), [&](VertexAdjList Iu){return Iu.first == u;});
        if(uIter != mAdjList.end()){
           auto vIter = std::find_if(uIter->second.begin(), uIter->second.end(), [&](AdjInfo Iv){return Iv.first == v;});
           if(vIter != uIter->second.end()) {
               vIter->second = weight;
           } else {
               uIter->second.emplace_back(v, weight);
           }
        } else {
            AdjInfoList ail{{v, weight}};
            mAdjList.emplace_back(u, ail);
        }
    }

    void removeEdge(int u, int v) {
        auto uIter = std::find_if(mAdjList.begin(), mAdjList.end(), [&](VertexAdjList Iu){return Iu.first == u;});
        if(uIter != mAdjList.end()){
            auto vIter = std::find_if(uIter->second.begin(), uIter->second.end(), [&](AdjInfo Iv){return Iv.first == v;});
            if(vIter != uIter->second.end()) {
                uIter->second.erase(vIter);
            }
            if(uIter->second.empty()) {
                mAdjList.erase(uIter);
            }
        }
    }

    AdjInfoList findAdjInfoList(int u){
        auto uIter = std::find_if(mAdjList.begin(), mAdjList.end(), [&](VertexAdjList Iu){return Iu.first == u;});
        if(uIter != mAdjList.end()){
            return uIter->second;
        } else {
            return AdjInfoList();
        }
    }

    int adjVertexNumber(int u) const {
        auto uIter = std::find_if(mAdjList.begin(), mAdjList.end(), [&](VertexAdjList Iu){return Iu.first == u;});
        if(uIter != mAdjList.end()){
            return uIter->second.size();
        } else {
            return 0;
        }
    }

private:
    std::vector<VertexAdjList> mAdjList;
};


#endif
