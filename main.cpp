#include <iostream>

// Анонимное пространство имен для всех констант
namespace {
const int MIN_HOUR = 0;
const int MAX_HOUR = 23;
const int MIN_MINUTE = 0;
const int MAX_MINUTE = 59;

const int MORNING_START = 5;
const int DAY_START = 12;
const int EVENING_START = 18;

const int HOURS_IN_HALF_DAY = 12;

const int MOD_TEN = 10;
const int MOD_HUNDRED = 100;
const int EXCEPTION_TEENS_START = 11;
const int EXCEPTION_TEENS_END = 14;

const int ENDING_SINGLE = 1;
const int ENDING_FEW_START = 2;
const int ENDING_FEW_END = 4;
}  // namespace

int main() {
    int hours, minutes;

    // Ввод и проверка на корректность типов данных
    if (!(std::cin >> hours >> minutes)) {
        std::cout << "введены недопустимые данные\n";
        return 0;
    }

    // Проверка границ времени
    if (hours < MIN_HOUR || hours > MAX_HOUR || minutes < MIN_MINUTE || minutes > MAX_MINUTE) {
        std::cout << "введены недопустимые данные\n";
        return 0;
    }

    // Обработка особых случаев (полдень и полночь)
    if (hours == DAY_START && minutes == MIN_MINUTE) {
        std::cout << "полдень\n";
        return 0;
    }
    if (hours == MIN_HOUR && minutes == MIN_MINUTE) {
        std::cout << "полночь\n";
        return 0;
    }

    // Перевод в 12-часовой формат для вывода
    int display_hour = hours % HOURS_IN_HALF_DAY;
    if (display_hour == MIN_HOUR) {
        display_hour = HOURS_IN_HALF_DAY;
    }

    // Вывод числа часов
    std::cout << display_hour << " ";

    // Склонение слова "час"
    if (display_hour == ENDING_SINGLE) {
        std::cout << "час";
    } else if (display_hour >= ENDING_FEW_START && display_hour <= ENDING_FEW_END) {
        std::cout << "часа";
    } else {
        std::cout << "часов";
    }

    // Вывод минут если они не равны нулю
    if (minutes > MIN_MINUTE) {
        std::cout << " " << minutes << " ";

        int last_digit = minutes % MOD_TEN;
        int last_two = minutes % MOD_HUNDRED;

        // Склонение слова "минута"
        if (last_two >= EXCEPTION_TEENS_START && last_two <= EXCEPTION_TEENS_END) {
            std::cout << "минут";
        } else if (last_digit == ENDING_SINGLE) {
            std::cout << "минута";
        } else if (last_digit >= ENDING_FEW_START && last_digit <= ENDING_FEW_END) {
            std::cout << "минуты";
        } else {
            std::cout << "минут";
        }
    }

    // Определение времени суток
    std::cout << " ";
    if (hours >= MORNING_START && hours < DAY_START) {
        std::cout << "утра";
    } else if ((hours == DAY_START && minutes > MIN_MINUTE) || (hours > DAY_START && hours < EVENING_START)) {
        std::cout << "дня";
    } else if (hours >= EVENING_START && hours <= MAX_HOUR) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }

    // Добавление слова "ровно", если минут 0
    if (minutes == MIN_MINUTE) {
        std::cout << " ровно";
    }

    std::cout << "\n";
    return 0;
}
