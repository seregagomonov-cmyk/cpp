#ifndef MATRIX_APPLICATION_HPP
#define MATRIX_APPLICATION_HPP

namespace matrix_app {
enum class Task : int {
    kExit = 0,
    kDynamic = 1,
    kStatic = 2,
    kPointers = 3,
    kSave = 4
};
void PrintMenu();
void RunApplication();
}  // namespace matrix_app

#endif
