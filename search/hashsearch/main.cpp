#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

template<typename T>
using HashTable= vector<vector<T>>;

template<typename T>
size_t hashValue(const T& data, size_t module)
{
    return ((3*data)%module);
}

template<typename T>
void insertHashTable(HashTable<T>& table, const T& data)
{
    size_t index = hashValue<T>(data, table.size());
    if (index >= table.size()) {
        return;
    }
    table[index].push_back(data);
}

template<typename T>
HashTable<T> loadHashTable(const vector<T>& data, float factor)
{
    HashTable<T> table;
    if (data.empty() || factor <= 0 || factor >= 1){
        return table;
    }
    size_t dataSize = data.size();
    size_t tableSize = dataSize/factor;
    for(size_t i = 0; i < tableSize; i++) {
        vector<T> list;
        table.emplace_back(list);
    }
    for(const auto& e : data) {
        insertHashTable<T>(table, e);
    }
    return table;
}

template<typename T> 
pair<int, int> searchHashTable(const HashTable<T>& table, const T& target)
{
    pair<int, int> result(-1, -1);
    size_t index_first = hashValue<T>(target, table.size());
    size_t index_second(0);
    for(const auto& data : table[index_first]) {
        if (data == target) {
            result.first = index_first;
            result.second = index_second;
            return result;
        }
        index_second++;
    }
    return result;
}

int main(int argc, char** argv)
{
    vector<int> data {1, 2, 3, 4, 7, 7, 8, 3, 5};
    int target = 7;
    HashTable<int> table = loadHashTable<int>(data, 0.7);
    pair<int, int> result = searchHashTable<int>(table, target);
    std::cout << "first: " << result.first << ", second: " << result.second << std::endl;
    return 0;
}