#include "matrix_application.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "matrix.hpp"
#include "matrix_print.hpp"

// Raw arrays and pointer expressions are the subject of lab 7.
// All executed subscript/pointer expressions remain inside their row.
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
namespace {
const int kMaximumDimension = 100;
const int kMaximumPrecision = 12;
const std::size_t kStaticSize = 10;
const std::size_t kSecondRow = 1;
const std::size_t kThirdRow = 2;

[[nodiscard]] bool ReadInteger(int& value) {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::istringstream input(line);
    char extra = '\0';
    return static_cast<bool>(input >> value) && !(input >> extra);
}

[[nodiscard]] bool ReadDimensions(int& rows, int& columns) {
    std::cout << "Число строк и столбцов (1.." << kMaximumDimension << "): ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::istringstream input(line);
    char extra = '\0';
    return static_cast<bool>(input >> rows >> columns) && !(input >> extra) && rows > 0 && columns > 0 && rows <= kMaximumDimension &&
           columns <= kMaximumDimension;
}

[[nodiscard]] bool ReadPrintSettings(int& precision, matrix_print::Format& format) {
    std::cout << "Точность (0.." << kMaximumPrecision << "): ";
    if (!ReadInteger(precision) || precision < 0 || precision > kMaximumPrecision) {
        return false;
    }
    std::cout << "Формат: 0 — фиксированный, 1 — научный: ";
    int choice = 0;
    if (!ReadInteger(choice) || (choice != 0 && choice != 1)) {
        return false;
    }
    format = static_cast<matrix_print::Format>(choice);
    return true;
}

void RunDynamicTask(bool save_to_file) {
    int requested_rows = 0;
    int requested_columns = 0;
    if (!ReadDimensions(requested_rows, requested_columns)) {
        std::cout << "Ошибка: недопустимые размеры.\n";
        return;
    }
    int precision = 0;
    matrix_print::Format format = matrix_print::Format::kFixed;
    if (!ReadPrintSettings(precision, format)) {
        std::cout << "Ошибка: недопустимый формат или точность.\n";
        return;
    }
    const auto rows = static_cast<std::size_t>(requested_rows);
    const auto columns = static_cast<std::size_t>(requested_columns);
    double** twoDimensionalDynamicMatrix = matrix::Allocate(rows, columns);
    if (twoDimensionalDynamicMatrix == nullptr) {
        std::cout << "Ошибка выделения памяти.\n";
        return;
    }
    matrix::Fill(twoDimensionalDynamicMatrix, rows, columns);
    matrix_print::Print(std::cout, twoDimensionalDynamicMatrix, rows, columns, precision, format);
    if (save_to_file) {
        std::ofstream output("matrix_output.txt");
        if (output) {
            matrix_print::Print(output, twoDimensionalDynamicMatrix, rows, columns, precision, format);
            output.close();
            if (output) {
                std::cout << "Сохранено в matrix_output.txt (текущая папка).\n";
            } else {
                std::cout << "Ошибка записи файла.\n";
            }
        } else {
            std::cout << "Не удалось открыть файл.\n";
        }
    }
    matrix::Release(twoDimensionalDynamicMatrix, rows);
}

void FillStatic(double (&values)[kStaticSize][kStaticSize], const double* (&pointers)[kStaticSize]) {
    for (std::size_t row = 0; row < kStaticSize; ++row) {
        pointers[row] = values[row];
        for (std::size_t column = 0; column < kStaticSize; ++column) {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            values[row][column] = static_cast<double>(row * kStaticSize + column);
        }
    }
}

void RunStaticTask() {
    double staticMatrix[kStaticSize][kStaticSize]{};
    const double* row_pointers[kStaticSize]{};
    FillStatic(staticMatrix, row_pointers);
    int precision = 0;
    matrix_print::Format format = matrix_print::Format::kFixed;
    if (!ReadPrintSettings(precision, format)) {
        std::cout << "Ошибка: недопустимый формат или точность.\n";
        return;
    }
    matrix_print::Print(std::cout, row_pointers, kStaticSize, kStaticSize, precision, format);
}

void ExplainPointers() {
    double staticMatrix[kStaticSize][kStaticSize]{};
    const double* B[kStaticSize]{};
    FillStatic(staticMatrix, B);
    std::cout << "Адрес матрицы, первой и третьей строки:\n";
    std::cout << staticMatrix << "  " << staticMatrix[0] << "  " << staticMatrix[kThirdRow] << '\n';
    std::cout << "Три обращения к первому элементу (0):\n";
    std::cout << staticMatrix[0][0] << "  " << **staticMatrix << "  " << *staticMatrix[0] << '\n';
    std::cout << "Первый элемент второй строки (10):\n";
    std::cout << *(*(staticMatrix + kSecondRow)) << "  " << *B[kSecondRow] << '\n';
    std::cout << "Второй элемент первой строки (1):\n";
    std::cout << *(staticMatrix[0] + 1) << "  " << *(*staticMatrix + 1) << '\n';
    // The following expressions from the assignment have undefined behavior:
    // staticMatrix[0][20] and *(staticMatrix[0] + 20).
    // They must not be executed: the first row has only 10 elements.
    std::cout << "staticMatrix[0][20] и *(staticMatrix[0]+20):\n"
                 "выход за границы строки, неопределённое поведение.\n"
                 "Корректный доступ к третьей строке: ";
    std::cout << staticMatrix[kThirdRow][0] << "  " << *staticMatrix[kThirdRow] << '\n';
}
}  // namespace

namespace matrix_app {
void PrintMenu() {
    std::cout << "\nЛабораторная 7. Матрицы\n"
                 "1 — динамическая матрица\n2 — статическая матрица 10x10\n"
                 "3 — объяснение указателей\n4 — матрица и запись в файл\n"
                 "0 — выход\nВыбор: ";
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
            case Task::kDynamic:
                RunDynamicTask(false);
                break;
            case Task::kStatic:
                RunStaticTask();
                break;
            case Task::kPointers:
                ExplainPointers();
                break;
            case Task::kSave:
                RunDynamicTask(true);
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
}  // namespace matrix_app
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
