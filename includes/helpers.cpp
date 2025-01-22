#include <cmath>
#include <iostream>
#include "helpers.h"
#include <vector>

using std::vector;

double get_max(double a, double b)
{
    return (a > b) ? a : b;
}

double get_arr_mean(vector <double> arr)
{
    double running_sum = 0.0;
    for (int i = 0; i < arr.size(); i++)
    {
        running_sum += arr[i];
    }
    return running_sum / double(arr.size());
}

double get_arr_stddev(vector <double> arr)
{
    double mean = get_arr_mean(arr);
    double running_sum = 0.0;
    for (int i = 0; i < arr.size(); i++)
    {
        running_sum += pow(arr[i] - mean, 2);
    }
    return sqrt(running_sum / double(arr.size()));
}

double get_arr_stddev(vector <double> arr, double mean)
{
    double running_sum = 0.0;
    for (int i = 0; i < arr.size(); i++)
    {
        running_sum += pow(arr[i] - mean, 2);
    }
    return sqrt(running_sum / double(arr.size()));
}