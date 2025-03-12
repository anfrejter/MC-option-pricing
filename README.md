# Barrier Option Pricing  

## Project Overview  
This project implements Monte Carlo simulations in C++ to price a **down-and-in barrier put option**. The underlying asset follows **Geometric Brownian Motion (GBM)**, and option pricing is based on simulated price paths.  

## Assumptions  
- The stock price follows **GBM**:  
  \[
  dS_t = \mu S_t dt + \sigma S_t dW_t
  \]
- Discretized form used for simulations:  
  \[
  \log S_{t+\Delta t} = \log S_t + (r - \frac{1}{2} \sigma^2) \Delta t + \sigma \sqrt{\Delta t} x, \quad x \sim N(0,1)
  \]
- **100 time steps**, **time to maturity: 0.75 years** (~2 days per step).  

## Option Characteristics  
| Parameter         | Value  |  
|------------------|--------|  
| Spot Price      | 100    |  
| Strike Price    | 110    |  
| Volatility      | 25%    |  
| Risk-Free Rate  | 5%     |  
| Barrier Price   | 90     |  
| Time to Maturity | 0.75  |  

## Code Structure  
```
/project_root
│── main.cpp         # Executes core functionality  
│── options.cpp      # Option class implementation  
│── helpers.cpp      # Utility functions  
│── gen_rand.cpp     # Random number generation  
```  

## Key Features  
- **Monte Carlo Simulation** for pricing path-dependent options.  
- **Option class** supporting **European & Barrier options**.  
- **Barrier sensitivity analysis** – studying price impact of barrier levels.  

## Results  
- **Baseline price** for a **down-and-in put (barrier = 90):** **11.0687**  
- **Higher barriers → More likely to activate, behaves like a European put.**  
- **Standard deviation for 10,000 simulations:** **13.76** (high, requiring variance reduction).  

## Next Steps  
- Implement **variance reduction techniques** (e.g., antithetic variates).  
- Extend to other **barrier option types** (down-and-out, up-and-in, etc.). 
