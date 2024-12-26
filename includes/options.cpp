#include <cmath>
#include <iostream>
#include <string>
#include "options.h"
#include "gen_rand.h"
#include "helpers.h"

// constructor
Option::Option(double _strike, 
               double _spot, 
               double _vol,
               double _r,
               double _expiry)
{
    strike = _strike;
    spot = _spot;
    vol = _vol;
    r = _r;
    expiry = _expiry;
    this_path=nullptr; // initialize this_path to nullptr
}

// destructor
Option::~Option()
{
    if (this_path != nullptr)
        delete[] this_path; // free memory allocated for this_path, 
}

// methods
void Option::generate_path(unsigned int _n_intervals)
{
    n_intervals = _n_intervals;
    if (this_path != nullptr)
    {
        delete[] this_path;
    }
    this_path = new double[n_intervals]; // allocate memory for this_path

	double this_drift = (r * expiry - 0.5 * vol * vol * expiry) / double(n_intervals);
	double cumShocks = 0.0;

	for (int i = 0; i < n_intervals; i++)
	{
		this_path[i]=spot * exp(cumShocks); //first element of this_path is spot
		cumShocks += (this_drift + vol * sqrt(expiry / double(n_intervals)) * generate_rand_norm());
	}
}

void Option::print_path()
{   
    if (this_path == nullptr) {
        std::cerr << "Path not generated yet. Call generate_path first.\n";
        return;
    }
    else
    {
        for (int i = 0; i < n_intervals; i++)
        {
            std::cout << "price for interval # " << i << " = " << this_path[i] << "\n";
        }
    }
}
// get payout for a given option type and end price
double Option::get_payout(OptionType type, double end_price)
{
    switch (type)
    {
    case OptionType::call:
        return get_max(end_price - strike, 0.0);

    case OptionType::put:
        return get_max(strike - end_price, 0.0);

    default:
        std::cout << "Invalid option type" << std::endl;
        return 0;
    }
}
// check if barrier is touched
bool Option::is_barrier_touched(double barrier_price, BarrierType type)
{
    if (this_path == nullptr) {
        std::cerr << "Path not generated yet. Call generate_path first.\n";
        return false;
    }
    switch (type)
    {

    case BarrierType::down_in:
        for (int i = 0; i < n_intervals; i++)
        {
            if (this_path[i] <= barrier_price)
            {
                return true;
            }
        }
        return false;

    case BarrierType::down_out:
        std::cout << "Down and out barrier not implemented yet" << std::endl;
        return false;

    case BarrierType::up_in:
        std::cout << "Up and in barrier not implemented yet" << std::endl;
        return false;
    
    case BarrierType::up_out:
        std::cout << "Up and outbarrier not implemented yet" << std::endl;
        return false;
    
    default:
        std::cout << "Invalid barrier type" << std::endl;
        return false;
    }
}
// get price of the option
double Option::get_price(int n_sim, OptionType type, OptionStyle style)
{
    switch (style)
    {
        double running_sum = 0.0;
        double end_price = 0.0;

    case OptionStyle::european:
        
        for (int i = 0; i < n_sim; i++)
        {
            generate_path(n_intervals);
            end_price = this_path[n_intervals - 1];
            running_sum += get_payout(type, end_price);
        }
        return (running_sum / n_sim) * exp(-r * expiry);
    }
}
;
// get price of the option with barrier
double Option::get_price(int n_sim, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price)
{
    switch (style)
    {
        double running_sum = 0.0;
        double end_price = 0.0;

    case OptionStyle::european:
        return get_price(n_sim, type, style); // reuse the previous function

    case OptionStyle::barrier:

        for (int i = 0; i < n_sim; i++)
        {
            generate_path(n_intervals);
            bool barrier_touched = is_barrier_touched(barrier_price, b_type);
            if (barrier_touched)
            {
                end_price = this_path[n_intervals - 1];
                running_sum += get_payout(type, end_price);
            }
            else {running_sum += 0.0;}
        }
        return (running_sum / n_sim) * exp(-r * expiry);

    default:
        std::cout << "Invalid option style" << std::endl;
        return 0;
    }
}