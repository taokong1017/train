#include <iostream>
#include <vector>

static int count(0);
using namespace std;

template<typename T>
void printList(vector<T> list)
{
    std::cout << count << ": ";
    for(const auto& ele : list) 
        std::cout << ele << " ";
    std::cout << std::endl;
    count++;
}

template<typename T>
void quickSort(vector<T> list, int left, int right)
{
    if (left >= right) {
        return;
    }

    int front = left;
    int back = right;
    T key = list[left];
    while(front < back) {
        while(front < back && list[front] > key) {
            front++;
        }
        while(front < back && list[back] < key) {
            back--;
        }
        std::swap(list[front], list[back]);
        printList(list);
    }
    quickSort(list, left, front-1);
    quickSort(list, front+1, right);
}

int main(int argc, char** argv)
{
    vector<float> data {30.0, 2, -1.0, 3, 10, 4, 8};
    printList<float>(data);
    quickSort<float>(data, 0, data.size()-1);
    return 0;
}