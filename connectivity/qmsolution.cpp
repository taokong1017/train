#include <iostream>
#include "qmsolution.h"

QuickMergeSolution::QuickMergeSolution(int pointNumber)
{
    for (int i = 0; i < pointNumber; i++) {
        mDataPints.push_back(i);
    }
    dumpData( );
}

void QuickMergeSolution::setPointsConnected(ConnectedPointList list) {
    for (auto& line : list) {
        int p = line.first;
        int q = line.second;
        findModifyTarget(p, q);
        dumpData( );
    }
}

void QuickMergeSolution::findModifyTarget(int p, int q) {
    int len = mDataPints.size( );
    if (p > len || q > len) {
        return;
    }

    int qr = getRoot(q);
    int pr = getRoot(p);
    mDataPints[pr] = qr;
}

bool QuickMergeSolution::checkPointsConnected(ConnectedPoints points) {
    int len = mDataPints.size( );
    int p = points.first;
    int q = points.second;
    if (p > len || q > len) {
        std::cout << "invald data" << std::endl;
        return false;
    } else {
        bool ret = getRoot(p) == getRoot(q);
        std::cout << p << " and " << q << " is" << (ret ? " connected" : " not connected") << std::endl;
        return ret;
    }
}


int QuickMergeSolution::getRoot(int p) {
    int i = p;
    while (i != mDataPints[i]) {
        i = mDataPints[i];
    }
    return i;
}

void QuickMergeSolution::dumpData( ) {
    std::cout << "dump data: " << std::endl;
    for (auto& data : mDataPints) {
        std::cout << data << "\t";
    }
    std::cout << std::endl;
}


