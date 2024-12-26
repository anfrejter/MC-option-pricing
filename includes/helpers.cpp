#include <cmath>
#include <iostream>
#include "helpers.h"

double get_max(double a, double b)
{
    return (a > b) ? a : b;
}

double get_arr_mean(double* arr, unsigned int n)
{
    double running_sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        running_sum += arr[i];
    }
    return running_sum / double(n);
}
