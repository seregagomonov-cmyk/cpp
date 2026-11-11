// Lab 4 explicitly studies raw arrays; every subscript is bounded by size.
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
#include "sorting.hpp"

#include <iomanip>
#include <iostream>
#include <new>
#include <random>
#include <sstream>
#include <string>
#include <utility>

namespace {
const std::size_t kStaticSize = 10;
const int kMaximumSize = 10000;
const int kMinimumValue = 0;
const int kMaximumValue = 99;
const int kColumnWidth = 18;

[[nodiscard]] bool ReadInteger(int& value) {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::istringstream input(line);
    char extra = '\0';
    return static_cast<bool>(input >> value) && !(input >> extra);
}

[[nodiscard]] bool OutOfOrder(int left, int right, sorting::Order order) {
    return order == sorting::Order::kAscending ? left > right : left < right;
}

void FillRandom(int* values, std::size_t size) {
    if (values == nullptr) {
        return;
    }
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> distribution(kMinimumValue, kMaximumValue);
    for (std::size_t index = 0; index < size; ++index) {
        values[index] = distribution(engine);
    }
}

void CopyArray(const int* source, int* destination, std::size_t size) {
    if (source == nullptr || destination == nullptr) {
        return;
    }
    for (std::size_t index = 0; index < size; ++index) {
        destination[index] = source[index];
    }
}

void PrintArray(const int* values, std::size_t size) {
    if (values == nullptr) {
        return;
    }
    for (std::size_t index = 0; index < size; ++index) {
        std::cout << values[index] << ' ';
    }
    std::cout << '\n';
}

void PrintStatistics(const sorting::Statistics& selection, const sorting::Statistics& bubble) {
    // ASCII headings keep std::setw alignment independent of UTF-8 encoding.
    std::cout << std::left << std::setw(kColumnWidth) << "Method" << std::right << std::setw(kColumnWidth) << "Comparisons" << std::setw(kColumnWidth)
              << "Swaps" << '\n';
    std::cout << std::left << std::setw(kColumnWidth) << "Selection" << std::right << std::setw(kColumnWidth) << selection.comparisons
              << std::setw(kColumnWidth) << selection.swaps << '\n';
    std::cout << std::left << std::setw(kColumnWidth) << "Bubble" << std::right << std::setw(kColumnWidth) << bubble.comparisons
              << std::setw(kColumnWidth) << bubble.swaps << '\n';
}

void CompareSorts(int* selection, int* bubble, std::size_t size, sorting::Order order, bool print_arrays) {
    const sorting::Statistics first = sorting::SelectionSort(selection, size, order);
    const sorting::Statistics second = sorting::BubbleSort(bubble, size, order);
    PrintStatistics(first, second);
    if (print_arrays) {
        std::cout << "Выбором:   ";
        PrintArray(selection, size);
        std::cout << "Пузырьком: ";
        PrintArray(bubble, size);
    }
}

void RunStaticTask() {
    int selection[kStaticSize]{};
    int bubble[kStaticSize]{};
    FillRandom(selection, kStaticSize);
    CopyArray(selection, bubble, kStaticSize);
    std::cout << "Исходный массив: ";
    PrintArray(selection, kStaticSize);
    std::cout << "1. По возрастанию\n";
    CompareSorts(selection, bubble, kStaticSize, sorting::Order::kAscending, true);
    std::cout << "2. Повторно по возрастанию\n";
    CompareSorts(selection, bubble, kStaticSize, sorting::Order::kAscending, true);
    std::cout << "3. По убыванию\n";
    CompareSorts(selection, bubble, kStaticSize, sorting::Order::kDescending, true);
}

void RunDynamicTask() {
    std::cout << "Размер массива (1.." << kMaximumSize << "): ";
    int requested_size = 0;
    if (!ReadInteger(requested_size) || requested_size <= 0 || requested_size > kMaximumSize) {
        std::cout << "Ошибка: недопустимый размер массива.\n";
        return;
    }
    const auto size = static_cast<std::size_t>(requested_size);
    // Manual new[]/delete[] is an explicit requirement of lab 4.
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    int* selection = new (std::nothrow) int[size];
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    int* bubble = new (std::nothrow) int[size];
    if (selection != nullptr && bubble != nullptr) {
        FillRandom(selection, size);
        CopyArray(selection, bubble, size);
        CompareSorts(selection, bubble, size, sorting::Order::kAscending, false);
    } else {
        std::cout << "Ошибка выделения памяти.\n";
    }
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete[] bubble;
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete[] selection;
}
}  // namespace

namespace sorting {
Statistics SelectionSort(int* values, std::size_t size, Order order) {
    Statistics statistics;
    if (values == nullptr || size < 2) {
        return statistics;
    }
    for (std::size_t first = 0; first < size - 1; ++first) {
        std::size_t best = first;
        for (std::size_t next = first + 1; next < size; ++next) {
            ++statistics.comparisons;
            if (OutOfOrder(values[best], values[next], order)) {
                best = next;
            }
        }
        if (best != first) {
            std::swap(values[first], values[best]);
            ++statistics.swaps;
        }
    }
    return statistics;
}

Statistics BubbleSort(int* values, std::size_t size, Order order) {
    Statistics statistics;
    if (values == nullptr || size < 2) {
        return statistics;
    }
    for (std::size_t end = size; end > 1; --end) {
        bool swapped = false;
        for (std::size_t next = 1; next < end; ++next) {
            ++statistics.comparisons;
            if (OutOfOrder(values[next - 1], values[next], order)) {
                std::swap(values[next - 1], values[next]);
                ++statistics.swaps;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return statistics;
}

void PrintMenu() {
    std::cout << "\nЛабораторная 4. Сортировки\n"
                 "1 — статический массив, три сортировки\n"
                 "2 — динамический массив\n0 — выход\nВыбор: ";
}

void RunApplication() {
    while (true) {
        PrintMenu();
        int choice = 0;
        if (!ReadInteger(choice)) {
            if (std::cin.eof()) {
                return;
            }
            std::cout << "Ошибка: введите целое число.\n";
            continue;
        }
        switch (static_cast<Task>(choice)) {
            case Task::kExit:
                return;
            case Task::kStatic:
                RunStaticTask();
                break;
            case Task::kDynamic:
                RunDynamicTask();
                break;
            default:
                std::cout << "Такого пункта нет.\n";
                continue;
        }
        std::cout << "Продолжить? 1 — да, 0 — нет: ";
        int again = 0;
        while (!ReadInteger(again) || (again != 0 && again != 1)) {
            if (std::cin.eof()) {
                return;
            }
            std::cout << "Введите 1 или 0: ";
        }
        if (again == 0) {
            return;
        }
    }
}
}  // namespace sorting

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
