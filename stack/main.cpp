#include "stack.h"


int main(int argc, char** argv)
{
    Stack<double> stack;
    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    stack.dump( );

    for (int i = 0; i < 9; i++) {
        stack.pop();
    }

    stack.dump( );
    stack.~Stack( );

    return 0;
}
