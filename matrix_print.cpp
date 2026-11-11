#include "matrix_print.hpp"

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

// Rows are passed as pointers by the assignment; all accesses are bounded.
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
namespace {
const std::size_t kLineLimit = 80;
const int kMaximumPrecision = 12;

[[nodiscard]] std::string FormatNumber(double value, int precision, matrix_print::Format format) {
    std::ostringstream output;
    output << std::setprecision(precision);
    if (format == matrix_print::Format::kScientific) {
        output << std::scientific << std::uppercase;
    } else {
        output << std::fixed;
    }
    output << value;
    return output.str();
}
}  // namespace

namespace matrix_print {
void Print(std::ostream& output, const double* const* values, std::size_t rows, std::size_t columns, int precision, Format format) {
    if (values == nullptr || rows == 0 || columns == 0 || precision < 0 || precision > kMaximumPrecision) {
        return;
    }
    std::size_t width = 1;
    for (std::size_t row = 0; row < rows; ++row) {
        if (values[row] == nullptr) {
            return;
        }
        for (std::size_t column = 0; column < columns; ++column) {
            width = std::max(width, FormatNumber(values[row][column], precision, format).size() + 1);
        }
    }
    const std::size_t per_block = std::max(std::size_t{1}, kLineLimit / width);
    for (std::size_t first = 0; first < columns; first += per_block) {
        const std::size_t last = first + std::min(per_block, columns - first);
        output << "Columns " << first + 1 << ".." << last << '\n';
        for (std::size_t row = 0; row < rows; ++row) {
            for (std::size_t column = first; column < last; ++column) {
                const std::string cell = FormatNumber(values[row][column], precision, format);
                // Matrix entries from this exercise fit within 80 columns.
                output << std::string(width - cell.size(), ' ') << cell;
            }
            output << '\n';
        }
        output << '\n';
    }
}
}  // namespace matrix_print
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
