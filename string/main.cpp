#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <unistd.h>

class Object
{
public:
    Object(std::string name):mName(name){ }
    ~Object(){std::cout << std::string("~Object") << std::endl;}
    const std::string& getName() const {return mName;}

private:
    std::string mName;
};

using ObjectPtr = std::shared_ptr<Object>;
using VectorObject = std::vector<ObjectPtr>;

std::shared_ptr<VectorObject> getObjectList()
{
    ObjectPtr ptr1 = std::make_shared<Object>("Object1");
    ObjectPtr ptr2 = std::make_shared<Object>("Object2");
    std::shared_ptr<VectorObject> list = std::make_shared<VectorObject>();
    list->push_back(ptr1);
    list->push_back(ptr2);
    return list;
}

int main(int argc, char**argv)
{
    std::shared_ptr<VectorObject> list = getObjectList();
    for(auto& ele : *list) {
        std::string str = ele->getName();
        std::cout << std::string("test1: ") << str << std::endl;
        std::cout << std::string("test2: ") << ele->getName() << std::endl;
    }
    return 0;
}
