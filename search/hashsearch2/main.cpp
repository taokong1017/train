#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

template<typename T>
using HashTable= vector<T>;

template<typename T>
size_t hashValue(const T& data, size_t module)
{
    return ((3*data)%module);
}

template<typename T>
void insertHashTable(HashTable<T>& table, const T& data)
{
    size_t tbLen = table.size();
    size_t index = hashValue<T>(data, tbLen);
    /* open address menthod */
    while(index < tbLen) {
        if(table[index] == -1) {
            table[index] = data;
            break;
        } else {
            index++;
        }
    }
}

template<typename T>
HashTable<T> loadHashTable(const vector<T>& data, float factor)
{
    HashTable<T> table;
    size_t ts = data.size()/factor;
    table.assign(ts, T(-1));
    for(auto& d : data) {
        insertHashTable<T>(table, d);
    }
    return table;
}

template<typename T> 
size_t searchHashTable(const HashTable<T>& table, const T& target)
{
    size_t result(-1);
    size_t tbLen = table.size();
    size_t index = hashValue<T>(target, tbLen);
    /* open address menthod */
    while(index < tbLen) {
        if(table[index] == target) {
            result = index;
            break;
        } else {
            index++;
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    vector<int> data {1, 2, 3, 4, 7, 7, 8, 3, 5};
    int target = 1;
    HashTable<int> table = loadHashTable<int>(data, 0.7);
    size_t result = searchHashTable<int>(table, target);
    std::cout << hex << -1 << std::endl;
    std::cout << hex <<"result: " << result << std::endl;
    return 0;
}