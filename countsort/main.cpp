#include <iostream>
#include <vector>
#include <cmath>

static int count(0);
using namespace std;

template<typename T>
T getMax(const vector<T>& list);

template<typename T>
T getMin(const vector<T>& list);

template<typename T>
void printComplexity(const vector<T>& list)
{
    size_t size = list.size();
    std::cout << "\nO(n) = " << size +
         getMax<T>(list) - getMin<T>(list) << std::endl;
}

//max_element
template<typename T>
void printList(const vector<T>& list)
{
    std::cout << count << ": ";
    for(const auto& ele : list) 
        std::cout << ele << " ";
    std::cout << std::endl;
    count++;
}

//max_element
template<typename T>
T getMax(const vector<T>& list)
{
    T value(0);
    for(const auto& element : list) {
        if(element > value) {
            value = element;
        }
    }
    return value;
}

//min_element
template<typename T>
T getMin(const vector<T>& list)
{
    T value(0);
    for(const auto& element : list) {
        if(element < value) {
            value = element;
        }
    }
    return value;
}

template<typename T>
void coutSort(vector<T>& list)
{
    //minmax_element
    T min = getMin<T>(list);
    T max = getMax<T>(list);
    T num = max - min + 1;

    vector<int> countList;
    countList.reserve(num);
    countList.assign(num, 0);
    for(const auto& element : list) {
        countList[element-min]++;
    }
    printList<int>(countList);

    int index(0);
    int count(0);
    for(auto& element : countList) {
        printList<T>(list);
        while (element > 0) {
            list[index] = min + count;
            index++;
            element--;
            printList<T>(list);
        }
        count++;
    }
}

int main(int argc, char** argv)
{
    vector<int> data {30, 2, -1, 3, 10, 4, 8, 2};
    printList<int>(data);
    coutSort<int>(data);
    printList<int>(data);
    printComplexity<int>(data);
    return 0;
}