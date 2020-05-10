#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

static int times(0);
using namespace std;


template<typename T>
void printList(vector<T> list)
{
    std::cout << times << ": ";
    for(const auto& ele : list) 
        std::cout << ele << " ";
    std::cout << std::endl;
    times++;
}

template<typename T>
void bucketSort(vector<T>& list, int bucketNum)
{
    const auto [min, max] = std::minmax_element(list.cbegin(), list.cend());
    T minValue = *min, maxValue = *max;
    //+1防止溢出，非法访问容器
    T detaValue = (maxValue - minValue + 1)/bucketNum + 1;
    vector<vector<T>> bucketList;
    //创建桶
    for(int index = 0; index < bucketNum; index++) {
        vector<T> bucket;
        bucketList.push_back(bucket);
     }
    //将数据分组入桶
    for(auto iter : list) {
        int index = iter/detaValue;
        bucketList[index].push_back(iter);
    }
    //桶内数据排序
    for(int index = 0; index < bucketNum; index++) {
        vector<T>& bucket = bucketList[index];
        //采用标准库快排算法
        sort(bucket.begin(), bucket.end());
        printList(bucket);
    }
    //取回桶内数据
    auto iter = list.begin();
    for(int index = 0; index < bucketNum; index++) {
        vector<T>& bucket = bucketList[index];
        iter = copy(bucket.begin(), bucket.end(), iter);
    }
}

int main(int argc, char** argv)
{
    vector<int> data {30, 2, 1, 3, 10, 4, 8, 20, 25};
    printList<int>(data);
    bucketSort<int>(data, 3);
    printList<int>(data);
    return 0;
}