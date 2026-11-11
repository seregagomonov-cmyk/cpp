# Лабораторные работы C++ — Гомонов Сергей

Решения курса iu5git/cpp находятся в отдельных ветках:

| Ветка | Работа | Решение |
|---|---|---|
| `lab_1` | Часы и падежные окончания | [Код и объяснение](../../tree/lab_1) |
| `lab_4` | Сортировки выбором и пузырьком | [Код и объяснение](../../tree/lab_4) |
| `lab_7` | Динамическая и статическая матрицы | [Код и объяснение](../../tree/lab_7) |

Для MacBook используются Apple Clang, CMake, VS Code и LLDB.
Команды после клонирования (пример для лабораторной 4):

```sh
git switch lab_4
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/lab_4
cmake --build build --target clang-format clang-tidy
```

Для целей проверок нужны clang-format и clang-tidy. В подготовленной
локальной копии они доступны в `.tools/bin`; на другом Mac установи
`brew install llvm` и добавь `$(brew --prefix llvm)/bin` в PATH.
Исходные конфиги проверок сохранены, задания выполняются на C++20
со строгими флагами компиляции. Настройки IDE и сборки в Git не хранятся.

Локально проверены все 1440 допустимых показаний времени и 11 ошибочных
вводов; 4800 наборов сортировок, счётчики и пустые массивы;
400 прямоугольных матриц, формулы, оба формата печати и предел 80 символов.
Локальная проверка clang-format и clang-tidy пройдена для каждой ветки.
Статус GitHub Actions появляется только после отправки изменений на сервер.

В README каждой ветки есть примеры запуска и пояснения для защиты.
Ниже сохранены исходные материалы курса.

---

# "Основы Программирования"    1 курс

> Репозиторий для выполнения лабораторных работ в рамках курса "Основы Программирования" кафедры ИУ5.

https://iu5git.github.io/cpp/

 - [План курса](https://iu5git.github.io/cpp/planCourse@.html)

 - Лекции
     - [Лекция 1](https://iu5git.github.io/cpp/meta/lecture-01.html)
     - [доп к лекции proGit](https://iu5git.github.io/cpp/meta/proGit.html)
     - [Лекция 2](https://iu5git.github.io/cpp/meta/lecture-02.html)
     - [Лекция 3](https://iu5git.github.io/cpp/meta/lecture-03.html)
     - [Лекция 4](https://iu5git.github.io/cpp/meta/lecture-04.html)
     - [Лекция 5](https://iu5git.github.io/cpp/meta/lecture-05.html)
 - Лабораторные работы
	 - [Лабораторная работа 0.1](https://iu5git.github.io/cpp/meta/lab-00_1.html)
	 - [Лабораторная работа 0.2](https://iu5git.github.io/cpp/meta/lab-00_2.html)
	 - [Лабораторная работа 0.3](https://iu5git.github.io/cpp/meta/lab-00_3.html)
	 - [Лабораторная работа 0.4](https://iu5git.github.io/cpp/meta/lab-00_4.html)
	 - [Лабораторная работа 1](https://iu5git.github.io/cpp/meta/lab-01.html)
	 - [Лабораторная работа 2](https://iu5git.github.io/cpp/meta/lab-02.html)
	 - [Лабораторная работа 3](https://iu5git.github.io/cpp/meta/lab-03.html)
	 - [Лабораторная работа 4](https://iu5git.github.io/cpp/meta/lab-04.html)
	 - [Лабораторная работа 5](https://iu5git.github.io/cpp/meta/lab-05.html)
	 - [Лабораторная работа 6](https://iu5git.github.io/cpp/meta/lab-06.html)
	 - [Лабораторная работа 7](https://iu5git.github.io/cpp/meta/lab-07.html)
	 - [Лабораторная работа 8](https://iu5git.github.io/cpp/meta/lab-08.html)
	 - [Лабораторная работа 9](https://iu5git.github.io/cpp/meta/lab-09.html)
 - Домашняя работа
	 - [Домашняя работа](https://iu5git.github.io/cpp/meta/homeWork.html)
 - [Style Guide](https://iu5git.github.io/cpp/Style%20Guide.html)
 - [Правила сдачи лабораторных работ](https://iu5git.github.io/cpp/rules.html)


### Команда курса выражает благодарность за помощь в подготовке и обновлении данного курса

## Евдокимову Арсению, выпускнику магистратуры кафедры ИУ5 МГТУ им. Н. Э. Баумана
