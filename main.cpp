#include "includes/options.h"

int main()
{
    Option my_option(100, 100, 0.2, 0.05, 1);
    // my_option.generate_path(10);
    my_option.print_path();
    return 0;
}