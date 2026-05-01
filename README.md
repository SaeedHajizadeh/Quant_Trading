# C++ for Quantitative Finance

A structured journey learning modern C++ with a focus on options pricing,
derivatives, and low-latency trading systems.

## Goals

- Master modern C++ (C++17/20) fundamentals with emphasis on performance
- Implement core options pricing models from first principles
- Build a working limit order book and market data infrastructure
- Develop intuition for the trade-offs that matter in trading systems:
  latency, memory layout, cache behavior, and numerical accuracy

## Roadmap

### Phase 1: Foundations
- [ ] Language fundamentals (syntax, types, control flow)
- [ ] Functions, references, and scope
- [ ] Pointers and memory management
- [ ] Classes, RAII, and the rule of five
- [ ] Templates and generic programming
- [ ] STL containers and algorithms

### Phase 2: Modern C++ and Systems
- [ ] Move semantics and perfect forwarding
- [ ] Smart pointers and ownership models
- [ ] Concurrency: threads, atomics, lock-free structures
- [ ] Performance: profiling, cache effects, branch prediction

### Phase 3: Quant Projects
- [ ] Black-Scholes pricer with full Greeks
- [ ] Monte Carlo simulator (European, Asian, barrier options)
- [ ] Binomial and trinomial tree models
- [ ] Implied volatility solver
- [ ] Limit order book with price-time priority
- [ ] FIX protocol parser
- [ ] Backtesting framework

## Repository Structure

- `notes/` — Topic-by-topic learning notes with example code
- `exercises/` — Small problems and language drills
- `projects/` — Standalone projects, each with its own build system and tests
- `benchmarks/` — Performance experiments and microbenchmarks

## Environment

See [SETUP.md](./SETUP.md) for toolchain details.

## References

- *Effective Modern C++* — Scott Meyers
- *C++ Concurrency in Action* — Anthony Williams
- *Options, Futures, and Other Derivatives* — John Hull
- *C++ Design Patterns and Derivatives Pricing* — Mark Joshi
