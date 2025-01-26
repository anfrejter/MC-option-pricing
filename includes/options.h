#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>
#include <vector>

using std::vector;

class Option
{
    private:
        double strike; // strike price
        double spot; // spot price
        double vol; // volatility
        double r; // risk-free rate
        double expiry; // time to expiry
        unsigned int n_intervals; // number of intervals for the simulation
        vector<double> this_path; // path of the underlying
        vector<double> this_payout; // payout of the option for each simulation
        unsigned int n_sim; // number of simulations
        double price=-1.0; // price of the option (default -1)

    public:
        // constructor
        Option();
        Option(double _strike,
               double _spot,
               double _vol,
               double _r,
               double _expiry,
               unsigned int _n_intervals);

        enum OptionType { call, put };
        enum OptionStyle { european, barrier };
        enum BarrierType { down_in, down_out, up_in, up_out };

        // methods
        void print_details(); // print details of the option
        void generate_path(); // generate path of the underlying with n_intervals
        void generate_path(int n); // generate path of the underlying with n intervals
        void print_path(); // print the last path of the underlying
        void print_payout(); // print the last payouts of the simulation
        double get_payout(OptionType type, double end_price); // get payout for a given option type and end price
        bool is_barrier_touched(double barrier_price, BarrierType type); // check if barrier is touched
        double get_price(int n_sim, OptionType type, OptionStyle style); // get price of the option
        double get_price(int n_sim, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price); // get price of the option with barrier
        double get_price(); // get price of the option if already calculated
        double get_stddev(); // get standard deviation of the option price
        void print_barrier_sensitivity(float _base_barrier, int _range, OptionType type, OptionStyle style, BarrierType b_type); // print the sensitivity of the option price to the barrier
        void print_stddev_sensitivity(int _range, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price);
};

#endif