#include "queue.h"


int main(int argc, char** argv)
{
    Queue<int> queue;
    for (int i = 0; i < 10; i++) {
        queue.enqueue( i );
    }
    queue.dump( );
    queue.dequeue( );
    std::cout << "\n";
    queue.dump( );
    std::cout << "\n" << queue.size( ) << std::endl;
    queue.~Queue( );

    return 0;
}
