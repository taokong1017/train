#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template<typename T>
void printList(std::vector<T> list)
{
    std::cout << std::string("list: ");
    for(const auto& ele : list)
        std::cout << ele << std::string(" ");
    std::cout << std::endl;
}

template<typename T>
void merge(std::vector<T>& list, int low, int mid, int high)
{
    int i = low, j = mid + 1;
    std::vector<T> tList;

    for (int i = low; i <= high; i++) {
        tList.push_back(list[i]);
    }

    for (int k = low; k <= high; k++) {
        if (i > mid) {
            list[k] = tList[j - low];
            j++;
        } else if (j > high) {
            list[k] = tList[i - low];
            i++;
        } else if (tList[i - low] > tList[j -low]) {
            list[k] = tList[j - low];
            j++;
        } else {
            list[k] = tList[i - low];
            i++;
        }
    }
}


template<typename T>
void sort(std::vector<T>& list, int low, int high)
{
    if (low >= high) {
        return;
    }

    int mid = low + (high - low) / 2;

    sort(list, low, mid);
    sort(list, mid+1, high);
    merge(list, low, mid, high);
}

#if 1
template<typename T>
void sort(std::vector<T>& list)
{
    int len = list.size( );
    for (int sz = 1; sz < len; sz = 2 * sz) { //子数组大小
        for (int low = 0; low < len - sz; low += (2 * sz)) { //low 子数组索引
            merge(list, low, low + sz - 1, std::min(low + sz + sz - 1, len - 1));
        }
    }
}
#else
template<typename T>
void sort(std::vector<T>& list)
{
    if (list.empty( )) {
        std::cout << std::string("list is empty!\n");
        return;
    }

    sort(list, 0, list.size( ) - 1);
}
#endif

int main(int argc, char** argv)
{
    std::vector<int> data = { 10, 9, 8, 7, 6, 5, 4};
    printList(data);
    sort(data);
    printList(data);
     return 0;
}