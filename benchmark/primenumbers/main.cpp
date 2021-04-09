#include <benchmark/benchmark.h>

#include "ctk/math/prime_numbers.h"

static void BM_CountPrimeNumbersBfInt(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfInt)->Range(8, 1000);

static void BM_CountPrimeNumbersEsInt(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsInt)->Range(8, 1000);

static void BM_CountPrimeNumbersBfUnsInt(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfUnsInt)->Range(8, 1000);

static void BM_CountPrimeNumbersEsUnsInt(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsUnsInt)->Range(8, 1000);

static void BM_CountPrimeNumbersBfLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfLong)->Range(8, 1000);

static void BM_CountPrimeNumbersEsLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsLong)->Range(8, 1000);

static void BM_CountPrimeNumbersBfUnsLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfUnsLong)->Range(8, 1000);

static void BM_CountPrimeNumbersEsUnsLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsUnsLong)->Range(8, 1000);

static void BM_CountPrimeNumbersBfLongLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfLongLong)->Range(8, 1000);

static void BM_CountPrimeNumbersEsLongLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsLongLong)->Range(8, 1000);

static void BM_CountPrimeNumbersBfUnsLongLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbersBf(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersBfUnsLongLong)->Range(8, 1000);

static void BM_CountPrimeNumbersEsUnsLongLong(benchmark::State& state) {
  for (auto _ : state)
    ctk::countPrimeNumbers(state.range(0));
}
BENCHMARK(BM_CountPrimeNumbersEsUnsLongLong)->Range(8, 1000);


BENCHMARK_MAIN();
