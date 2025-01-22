#include "includes/options.h"
#include "includes/helpers.h"
#include <iostream>
int main()
{
    Option default_option;

    default_option.print_details();
    // Option my_option(100, 100, 0.2, 0.05, 1, 252);
    // my_option.generate_path(3);
    std::cout << default_option.get_price(10000,
                                         Option::OptionType::call,
                                         Option::OptionStyle::barrier,
                                         Option::BarrierType::down_in,
                                         100)
                                         <<'\n';
    return 0;
}