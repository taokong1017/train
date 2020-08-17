#ifndef TEST_H
#define TEST_H

namespace Train
{

class Test
{
public:
    Test(int data = 0);
    inline int getData() const {return mData;}
    void setData(int data);
    inline int selfAdd() {mData++; return mData;}

private:
    int mData;
};

}


#endif
