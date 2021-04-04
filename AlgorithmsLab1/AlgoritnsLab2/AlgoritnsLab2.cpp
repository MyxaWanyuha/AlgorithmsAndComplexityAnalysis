#include <iostream>
#include "TreeSort.h"

int main()
{
    std::vector<int32_t> arr{ 5, 4, 11, 7, 2, 11 };

    TreeSort<int32_t>::treeSort(arr);

    for (auto& e : arr)
        std::cout << e << " ";

    return 0;
}