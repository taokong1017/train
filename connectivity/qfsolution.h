#ifndef QUICK_FIND_SOLUTION_H
#define QUICK_FIND_SOLUTION_H

#include "commondata.h"

class QuickFindSolution {
public:
    QuickFindSolution(int pointNumber);
    virtual ~QuickFindSolution( ) {}
    void setPointsConnected(ConnectedPointList list);
    bool checkPointsConnected(ConnectedPoints points);

private:
    void findModifyTarget(int q, int p);
    void dumpData( );

private:
    std::vector<int> mDataPints;
};

#endif