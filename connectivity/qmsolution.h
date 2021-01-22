#ifndef QUICK_MERGE_SOLUTION_H
#define QUICK_MERGE_SOLUTION_H

#include "commondata.h"

class QuickMergeSolution {
public:
    QuickMergeSolution(int pointNumber);
    virtual ~QuickMergeSolution( ) {}
    void setPointsConnected(ConnectedPointList list);
    bool checkPointsConnected(ConnectedPoints points);

private:
    void findModifyTarget(int q, int p);
    int getRoot(int p);
    void dumpData( );

private:
    std::vector<int> mDataPints;
};

#endif