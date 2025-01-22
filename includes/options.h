#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>
#include <vector>

using std::vector;

class Option
{
    private:
        double strike;
        double spot;
        double vol;
        double r;
        double expiry;
        unsigned int n_intervals;
        vector<double> this_path;
        vector<double> this_payout;
        unsigned int n_sim;
        double price=-1.0;

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
        void print_details();
        void generate_path();
        void generate_path(int n);
        void print_path();
        void print_payout();
        double get_payout(OptionType type, double end_price);
        bool is_barrier_touched(double barrier_price, BarrierType type);
        double get_price(int n_sim, OptionType type, OptionStyle style);
        double get_price(int n_sim, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price);
        double get_price();
        double get_stddev();
};

#endif