#ifndef SORTING_HPP
#define SORTING_HPP

#include <cstddef>
#include <cstdint>

namespace sorting {
enum class Task : int {
    kExit = 0,
    kStatic = 1,
    kDynamic = 2
};
enum class Order {
    kAscending,
    kDescending
};

struct Statistics {
    std::uint64_t comparisons = 0;
    std::uint64_t swaps = 0;
};

[[nodiscard]] Statistics SelectionSort(int* values, std::size_t size, Order order);
[[nodiscard]] Statistics BubbleSort(int* values, std::size_t size, Order order);
void PrintMenu();
void RunApplication();
}  // namespace sorting

#endif
