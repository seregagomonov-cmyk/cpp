#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

namespace matrix {
[[nodiscard]] double** Allocate(std::size_t rows, std::size_t columns);
void Release(double** values, std::size_t rows);
void Fill(double* const* values, std::size_t rows, std::size_t columns);
}  // namespace matrix

#endif
