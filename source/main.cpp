#include "RBTree.h"

int main()
{
    const clock_t begin_time = clock();

    RBTree S;
    for (int i = 0; i < 100000; ++i) S.insert(i);
    for (int i = 0; i < 100000; ++i) S.erase(i);

    std::cout << float( clock () - begin_time ) / CLOCKS_PER_SEC << '\n';
    return 0;
}