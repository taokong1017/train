#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

template<typename T>
int binaryRecursionRsearch(vector<T>& list, T& target, int low, int high)
{
    int middle = (low + high)/2;
    T data = list[middle];

    if(list[low] == target) return low;
    if (list[high] == target) return high;

    if (data < target) {
        return binaryRecursionRsearch<T>(list, target, middle, high);
    } else if (data > target) {
        return binaryRecursionRsearch<T>(list, target, low, middle);
    } else {
        return middle;
    }
    return -1;
}

template<typename T>
int binaryIterationSearch(vector<T>& list, T& target)
{
    int low = 0;
    int high = list.size()-1;
    if(list[low] == target) return low;
    if(list[high] == target) return high;

    while(low <= high) {
        int middle = (low + high)/2;
        T data = list[middle];
        if (data > target) {
            high = middle;
        } else if (data < target) {
            low = middle;
        } else {
            return middle;
        }
    }

    return -1;
}

int main(int argc, char** argv)
{
    vector<int> data {1, 2, 3, 4, 5, 7, 8, 9, 10};
    int target = 5;
    std::cout << binaryRecursionRsearch(data, target, 0, data.size()-1) << std::endl;
    std::cout << binaryIterationSearch(data, target) << std::endl;
    return 0;
}