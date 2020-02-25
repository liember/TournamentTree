#include "tourn_tree.hpp"

int main()
{
    int arr[] = {61, 6, 100, 9, 10, 12, 17, 32, 23, 1, 234, 7, 56, 534}; // массовка
    int n = sizeof(arr) / sizeof(arr[0]);                                // определяем размер массовки
    find_second_min(arr, n);                                             // ебашим
    return 0;
}