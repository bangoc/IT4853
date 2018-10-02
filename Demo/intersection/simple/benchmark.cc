#include <benchmark/benchmark.h>

#include "data.h"
#include "naive.h"
#include "sorted.h"

static void BM_IntesectNaive(benchmark::State& state) {
  for (auto _: state) {
    std::set<std::int32_t> out;
    IntersectNaive(rand_list1, rand_list2, out);
  }
}
BENCHMARK(BM_IntesectNaive);

static void BM_IntersectSorted(benchmark::State& state) {
  for (auto _: state) {
    std::vector<std::int32_t> out;
    IntersectSorted(sorted_list1, sorted_list2, out);
  }
}
BENCHMARK(BM_IntersectSorted);

BENCHMARK_MAIN();