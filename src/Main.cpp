#include <iostream>
#include "algorithm/BinarySearch.h"
int main()
{
    // BinarSearch
    int *list = new int[6]{1, 5, 30, 33, 45, 201};
    BinarySearch *binarySearch = new BinarySearch();
    int index = binarySearch->allInclude(list, 6, 12);
    std::cout << index << std::endl;
    delete binarySearch;
    delete[] list;
}