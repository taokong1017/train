#include <iostream>
#include <vector>
#include <cmath>

static int count(0);
using namespace std;

template<typename T>
void printComplexity(vector<T>& list)
{
    size_t size = list.size();
    std::cout << "\nO(n) = " << size*std::log2(size) << std::endl;
}

template<typename T>
void printList(vector<T>& list)
{
    std::cout << count << ": ";
    for(const auto& ele : list) 
        std::cout << ele << " ";
    std::cout << std::endl;
    count++;
}

//降序排序
template<typename T>
void minHeapify(vector<T>& list, int index, int max)
{
    int parent = index;
    int smallest = parent;
    int leftChild = 2*parent + 1;
    int rightChild = 2*parent + 2;

    if (leftChild < max && list[leftChild] < list[smallest]) {
        smallest = leftChild;
    }

    if (rightChild < max && list[rightChild] < list[smallest]) {
        smallest = rightChild;
    }

    if(smallest != parent) {
        std::swap(list[smallest], list[parent]);
        minHeapify<T>(list, smallest, max);
    }
    printList<T>(list);
}

template<typename T>
void buildMinHeap(vector<T>& list)
{
    for(int index = list.size()/2 - 1; index >= 0; index--) {
        minHeapify<T>(list, index, list.size());
    }
}

template<typename T>
void heapDecendSort(vector<T>& list)
{
    printList<T>(list);
    buildMinHeap(list);
    for(int index = list.size() - 1; index > 0; index--) {
        std::swap(list[0], list[index]);
        minHeapify<T>(list, 0, index);
    }
    printList<T>(list);
}


//升序排序
template<typename T>
void maxHeapify(vector<T>& list, int index, int max)
{
    int parent = index;
    int largest = parent;
    int leftChild = 2*parent + 1;
    int rightChild = 2*parent + 2;

    if (leftChild < max && list[leftChild] > list[largest]) {
        largest = leftChild;
    }

    if (rightChild < max && list[rightChild] > list[largest]) {
        largest = rightChild;
    }

    if(largest != parent) {
        std::swap(list[largest], list[parent]);
        maxHeapify<T>(list, largest, list.size());
    }
    printList<T>(list);
}

template<typename T>
void buildMaxHeap(vector<T>& list)
{
    for(int index = list.size()/2 - 1; index >= 0; index--) {
        maxHeapify<T>(list, index, list.size());
    }
}

template<typename T>
void heapAscendSort(vector<T>& list)
{
    printList<T>(list);
    buildMaxHeap(list);
    for(int index =list.size() - 1; index > 0; index--) {
        std::swap(list[0], list[index]);
        maxHeapify<T>(list, 0, index);
    }
    printList<T>(list);
}

int main(int argc, char** argv)
{
    vector<int> data{30, 2, 0, 3, 10, 4, 8};
    heapAscendSort<int>(data);
    std::cout << std::endl;
    heapDecendSort<int>(data);
    printComplexity(data);
    return 0;
}