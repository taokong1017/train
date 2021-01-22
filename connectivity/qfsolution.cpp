#include <iostream>
#include "qfsolution.h"

QuickFindSolution::QuickFindSolution(int pointNumber)
{
    for (int i = 0; i < pointNumber; i++) {
        mDataPints.push_back(i);
    }
    //dumpData( );
}

void QuickFindSolution::setPointsConnected(ConnectedPointList list) {
    for (auto& line : list) {
        int p = line.first;
        int q = line.second;
        findModifyTarget(p, q);
    }
    //dumpData( );
}

void QuickFindSolution::findModifyTarget(int p, int q) {
    int len = mDataPints.size( );
    if (p > len || q > len) {
        return;
    }

    int pd = mDataPints[p];
    int qd = mDataPints[q];
    for (auto& v : mDataPints) {
        if (v == pd) {
            v = qd;
        }
    }
}

bool QuickFindSolution::checkPointsConnected(ConnectedPoints points) {
    int len = mDataPints.size( );
    int p = points.first;
    int q = points.second;
    if (p > len || q > len) {
        std::cout << "invald data" << std::endl;
        return false;
    } else {
        bool ret = mDataPints[p] == mDataPints[q];
        std::cout << p << " and " << q << " is" << (ret ? " connected" : " not connected") << std::endl;
        return ret;
    }
}

void QuickFindSolution::dumpData( ) {
    std::cout << "dump data: " << std::endl;
    for (auto& data : mDataPints) {
        std::cout << data << "\t";
    }
    std::cout << std::endl;
}


