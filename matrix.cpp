#include "matrix.hpp"

#include <new>

// The exercise explicitly requires double** and manual new[]/delete[].
// Every allocated row has columns elements, every index is bounded.
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
namespace matrix {
double** Allocate(std::size_t rows, std::size_t columns) {
    if (rows == 0 || columns == 0) {
        return nullptr;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto* values = new (std::nothrow) double*[rows]{};
    if (values == nullptr) {
        return nullptr;
    }
    for (std::size_t row = 0; row < rows; ++row) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        values[row] = new (std::nothrow) double[columns]{};
        if (values[row] == nullptr) {
            Release(values, row);
            return nullptr;
        }
    }
    return values;
}

void Release(double** values, std::size_t rows) {
    if (values == nullptr) {
        return;
    }
    for (std::size_t row = 0; row < rows; ++row) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete[] values[row];
    }
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete[] values;
}

void Fill(double* const* values, std::size_t rows, std::size_t columns) {
    if (values == nullptr) {
        return;
    }
    const double x = 1.0;
    double inverse_factorial = 1.0;
    for (std::size_t column = 0; column < columns; ++column) {
        inverse_factorial /= static_cast<double>(column + 1);
        const double ratio = x * inverse_factorial;
        double power = 1.0;
        for (std::size_t row = 0; row < rows; ++row) {
            power *= ratio;
            if (values[row] == nullptr) {
                continue;
            }
            if (row == column) {
                values[row][column] = 1.0;
            } else if (row > column && (row + 1) % 2 != 0) {
                values[row][column] = -power;
            } else {
                values[row][column] = power;
            }
        }
    }
}
}  // namespace matrix
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
