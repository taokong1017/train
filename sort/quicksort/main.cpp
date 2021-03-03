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
void printList(vector<T> list)
{
    std::cout << count << ": ";
    for(const auto& ele : list)
        std::cout << ele << " ";
    std::cout << std::endl;
    count++;
}

template<typename T>
#if 0
void quickSort(vector<T>& list, int left, int right)
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
        printList<T>(list);
    }
    quickSort(list, left, front-1);
    quickSort(list, front+1, right);
}
#else
void quickSort(vector<T>& list, int left, int right)
{
    if (left >= right) {
        return;
    }

    int32_t lt = left;
    int32_t i = left + 1;
    int32_t gt = right;
    /* can not using reference */
    T key = list[left];

    while (i <= gt) {
        if (list[i] > key) {
            std::swap(list[i], list[gt--]);
        } else if (list[i] < key) {
            std::swap(list[lt++], list[i++]);
        } else {
            i++;
        }
    }

    quickSort(list, left, lt - 1);
    quickSort(list, gt + 1, right);
}
#endif

int main(int argc, char** argv)
{
    vector<float> data {30.0, 2, -1.0, 3, 10, 4, 8};
    printList<float>(data);
    quickSort<float>(data, 0, data.size()-1);
    printList<float>(data);
    printComplexity(data);
    return 0;
}