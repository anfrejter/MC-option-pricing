#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>

class Option
{
    private:
        double strike;
        double spot;
        double vol;
        double r;
        double expiry;
        unsigned int n_intervals;
        double* this_path; // pointer to dynamic array
        double* this_payout; // pointer to dynamic array, for calculating variance and avg payout

    public:
        // constructor
        Option(double _strike, 
               double _spot, 
               double _vol,
               double _r,
               double _expiry);
        
        enum class OptionType { call, put };
        enum class OptionStyle { european, barrier };
        enum class BarrierType { down_in, down_out, up_in, up_out };

        // destructor
        ~Option();

        // methods
        void generate_path(unsigned int _n_intervals);
        void print_path();
        double get_payout(OptionType type, double end_price);
        bool is_barrier_touched(double barrier_price, BarrierType type);
        double get_price(int n_sim, OptionType type, OptionStyle style);
        double get_price(int n_sim, OptionType type, OptionStyle style, BarrierType b_type, double barrier_price);
};

#endif