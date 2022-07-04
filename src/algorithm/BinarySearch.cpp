#include <iostream>
#include "BinarySearch.h"
/**
 * @brief 二分查找
 *
 * @param list 有序数组
 * @param target 目标值
 * @return int
 */
int BinarySearch::allInclude(int *list, int length, int target)
{
    int left = 0;
    int right = length - 1;
    int middle = -1;
    while (left <= right)
    {
        middle = left + ((right - left) / 2);
        if (list[middle] > target)
        {
            right = middle - 1;
        }
        else if (list[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}