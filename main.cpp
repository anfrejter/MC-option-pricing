#include "includes/options.h"
#include "includes/helpers.h"
#include <iostream>

using std::cout;

int main()
{
    Option default_option;

    default_option.print_details();
    cout<<std::endl;

    float base_barrier = 90;
    int range = 10;

    default_option.print_barrier_sensitivity(90,
                                            20,
                                            Option::OptionType::put,
                                            Option::OptionStyle::barrier,
                                            Option::BarrierType::down_in);
    default_option.print_stddev_sensitivity(7,
                                            Option::OptionType::put,
                                            Option::OptionStyle::barrier,
                                            Option::BarrierType::down_in,
                                            90);
    return 0;
}