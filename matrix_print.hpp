#ifndef MATRIX_PRINT_HPP
#define MATRIX_PRINT_HPP

#include <cstddef>
#include <iosfwd>

namespace matrix_print {
enum class Format : int {
    kFixed = 0,
    kScientific = 1
};
void Print(std::ostream& output, const double* const* values, std::size_t rows, std::size_t columns, int precision, Format format);
}  // namespace matrix_print

#endif
