#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "options.h"
#include "gen_rand.h"
#include "helpers.h"

using std::vector, std::cout, std::cerr, std::endl;

// constructors
// default constructor
Option::Option()
{
    strike = 110;
    spot = 100;
    vol = 0.25;
    r = 0.05;
    expiry = 0.75;
    n_intervals = 75;
    price=-1.0;
}
// constructor with parameters
Option::Option(double _strike,
               double _spot,
               double _vol,
               double _r,
               double _expiry,
               unsigned int _n_intervals)
{
    strike = _strike;
    spot = _spot;
    vol = _vol;
    r = _r;
    expiry = _expiry;
    n_intervals = _n_intervals;
    price=-1.0;
}

// methods
void Option::generate_path()
{
    this_path.resize(n_intervals);
	double this_drift = (r * expiry - 0.5 * vol * vol * expiry) / double(n_intervals);
	double cumShocks = 0.0;

	for (int i = 0; i < this_path.size(); i++)
	{
		cumShocks += (this_drift + vol * sqrt(expiry / double(n_intervals)) * generate_rand_norm());
		this_path[i] = spot * exp(cumShocks); //first element of this_path is spot
	}
}

// generate path with n intervals, overloading the method with defined
// number of n_intervals
void Option::generate_path(int n)
{
    this_path.resize(n); // create a vector of size n
	double this_drift = (r * expiry - 0.5 * vol * vol * expiry) / double(n);
	double cumShocks = 0.0;

	for (int i = 0; i < this_path.size(); i++)
	{
		cumShocks += (this_drift + vol * sqrt(expiry / double(n)) * generate_rand_norm());
		this_path[i] = spot * exp(cumShocks);
	}
}

void Option::print_path()
{
    if (this_path.size() == 0) {
        cerr << "Path not generated yet. Call generate_path first.\n";
        return;
    }
    else
    {
        for (int i = 0; i < this_path.size(); i++)
        {
            cout << "price for interval # " << i << " = " << this_path[i] << "\n";
        }
    }
}
void Option::print_payout()
{
    if (this_payout.size() == 0) {
        cerr << "Payouts not generated yet. Call get_price first.\n";
        return;
    }
    else
    {
        for (int i = 0; i < this_payout.size(); i++)
        {
            cout << "Payout for simulation # " << i << " = " << this_payout[i] << "\n";
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
        break;

    case OptionType::put:
        return get_max(strike - end_price, 0.0);
        break;

    default:
        cout << "Invalid option type" << endl;
        return 0;
        break;
    }
}
// check if barrier is touched
bool Option::is_barrier_touched(double barrier_price, BarrierType type)
{
    if (this_path.size() == 0) {
        cerr << "Path not generated yet. Call generate_path first.\n";
        return false;
    }
    double min_price = -1;
    double max_price = -1;

    switch (type)
    {
    case BarrierType::down_in:
        min_price = *min_element(this_path.begin(), this_path.end());
        if (min_price <= barrier_price)
            return true;
        else
            return false;
        break;

    case BarrierType::down_out:
        cout << "Down and out barrier not implemented yet" << endl;
        return false;
        break;

    case BarrierType::up_in:
        cout << "Up and in barrier not implemented yet" << endl;
        return false;
        break;

    case BarrierType::up_out:
        cout << "Up and outbarrier not implemented yet" << endl;
        return false;
        break;

    default:
        cout << "Invalid barrier type" << endl;
        return false;
        break;
    }
}
// get price of the option
double Option::get_price(int _n_sim, OptionType type, OptionStyle style)
{
    double running_sum = 0.0;
    double end_price = 0.0;
    n_sim = _n_sim;

    this_payout.resize(n_sim);

    switch (style)
    {
    case OptionStyle::european:
            for (int i = 0; i < n_sim; i++)
            {
                generate_path(1);
                // generate a single path - for European options, we only need the end price
                end_price = this_path.back();
                double current_payout = get_payout(type, end_price);
                // save the payout for each simulation
                this_payout[i] = current_payout * exp(-r * expiry);
                running_sum += current_payout;
            }
            price = (running_sum / n_sim) * exp(-r * expiry);
            return price;
            break;
    case OptionStyle::barrier:
            cerr << "Barrier tpe, price not provided" << endl;
            return 0;
            break;
    default:
            cerr << "Invalid option style" << endl;
            return 0;
            break;
    }
}

// get price of the option with barrier
double Option::get_price(int _n_sim, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price)
{
    double running_sum = 0.0;
    double end_price = 0.0;
    n_sim = _n_sim;

    this_payout.resize(n_sim);

    switch (style)
    {
    case OptionStyle::european:
        {return get_price(n_sim, type, style);} // reuse the previous function

    case OptionStyle::barrier:
        for (int i = 0; i < n_sim; i++)
        {
            generate_path();
            bool barrier_touched = is_barrier_touched(barrier_price, b_type);
            if (barrier_touched)
            {
                end_price = this_path[n_intervals - 1];
                double current_payout = get_payout(type, end_price);
                // save the payout for each simulation
                this_payout[i] = current_payout * exp(-r * expiry);
                running_sum += current_payout;
            }
            else {running_sum += 0.0; this_payout[i]=0.0;}
        }
        price = (running_sum / n_sim) * exp(-r * expiry);
        return price;
        break;

    default:
        cerr << "Invalid option style" << endl;
        return 0;
        break;
    }
}
double Option::get_price()
{
    if (price == -1.0)
    {
        cerr << "Price not calculated yet. Call get_price first.\n";
        return 0;
    }
    return price;
}

double Option::get_stddev()
{
    if (price == -1.0)
    {
        cerr << "Price not calculated yet. Call get_price first.\n";
        return 0;
    }
    return get_arr_stddev(this_payout, price);
}

void Option::print_details(){
    cout << "Spot price: " << spot << endl;
    cout << "Strike price: " << strike << endl;
    cout << "Volatility: " << vol << endl;
    cout << "Risk-free rate: " << r << endl;
    cout << "Expiry: " << expiry << endl;
    cout << "Number of intervals: " << n_intervals << endl;
}