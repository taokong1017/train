#include "qfsolution.h"
#include "qmsolution.h"

// #define QuickFindDebug
#define QuickMergeDebug

int main(int argc, char** argv)
{
    ConnectedPointList list{ {1,2}, {4,5}, {3,7}, {2,3}, {5, 7}, {6,8}, {9, 5}, {0, 1} };
    int n = 10;
    ConnectedPoints tp1{ 6, 7 };
    ConnectedPoints tp2{ 1, 4 };

#ifdef QuickFindDebug
    QuickFindSolution qfs(n);
    qfs.setPointsConnected(list);
    qfs.checkPointsConnected(tp1);
    qfs.checkPointsConnected(tp2);
#endif

#ifdef QuickMergeDebug
    QuickMergeSolution qms(n);
    qms.setPointsConnected(list);
    qms.checkPointsConnected(tp1);
    qms.checkPointsConnected(tp2);
#endif
    return 0;
}

