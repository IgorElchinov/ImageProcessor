/*
*   Разработать класс матрица, который удовлетворяет следующим требованиям:
*   1)Для представления элементов матрицы будем использовать наиболее компактное
*   2)Используем правильное управление ресурсами, памятью:
*       -Распределение
*       -Освобождение
*       -Глубокое копирование
*   3)Добавляем операционную семантику ожидаемую для математического объекта матрица
    (делаем перегрузку оператора) сложение, транспонирование, проверка на равенство, неравенство
*   4)Для представления составных элементов матрицы: столбцы строки создадим легковесные
*   обертки, которые можно будет передавать по значению(аналогия с итераторами и string_view).
*       Не забываем про константность
*   5)Добавляем в матрицу умение быть хорошо воспитанным контейнером:
*       Итераторы, бегины, энды и.т.д
*   6)Научим матрицу быть перемещаемым объектом (НЛО)
*   7)Сделаем матрицу шаблоном, чтобы это была матрица произвольных объектов
*
*   А)Будем тестировать функционал матрицы обычными асертами
*/

// Интерфейс - самое главное

#include <cassert>
#include <iostream>
#include <exception>

#include "matrix.h"

// smoke test
void Test01() {
    std::cout << __func__ << std::endl;

    image_processor::Matrix m;
    image_processor::Matrix m1{};

    std::cout << "passed" << std::endl;
}

void Test02() {
    std::cout << __func__ << std::endl;

    image_processor::Matrix m;
    assert(0 == m.GetRowsCount());
    assert(0 == m.GetColumnsCount());
    assert(nullptr == m.GetDataPointer());

    std::cout << "passed" << std::endl;
}

void PrintMatrix(const image_processor::Matrix& m) {
    m.GetRowsCount();
    m.GetColumnsCount();
}

void Test03() {
    std::cout << __func__ << std::endl;

    image_processor::Matrix m;
    PrintMatrix(m);

    std::cout << "passed" << std::endl;
}

void Test04() {
    std::cout << __func__ << std::endl;

    image_processor::Matrix matrix(3, 4, 42.);
    assert(matrix.GetRowsCount() == 3);
    assert(matrix.GetColumnsCount() == 4);
    assert(matrix.At(2, 1) == 42.);

    bool excpecto_patronum = false;
    try {
        matrix.At(10, 10);
    } catch (std::out_of_range& e) {
        excpecto_patronum = true;
    }
    assert(excpecto_patronum);

    std::cout << "passed" << std::endl;
}

void Print(const image_processor::Matrix::Row& r) {
    for (size_t i = 0; i < r.GetSize(); ++i) {
        std::cout << r[i] << " ";
    }
}

void PrintMatrix2(const image_processor::Matrix& m) {
    for (size_t i = 0; i < m.GetRowsCount(); ++i) {
        for (size_t j = 0; j < m.GetColumnsCount(); ++j) {
            std::cout << m.At(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void PrintMatrix3(const image_processor::Matrix& m) {
    for (size_t i = 0; i < m.GetRowsCount(); ++i) {
        image_processor::Matrix::ConstRow r = m[i];
        for (size_t j = 0; j < m.GetColumnsCount(); ++j) {
            std::cout << r[j] << " ";
        }
        std::cout << std::endl;
    }
}

void Test05() {
    std::cout << __func__ << std::endl;

    image_processor::Matrix matrix(3, 4, 42.);
    assert(matrix.GetRowsCount() == 3);
    assert(matrix.GetColumnsCount() == 4);
    assert(matrix.At(2, 1) == 42.);

    image_processor::Matrix::Row r = matrix[1];
    assert(r[1] == 42.);

    PrintMatrix2(matrix);
    PrintMatrix3(matrix);

    std::cout << "passed" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "test_matrix" << std::endl;

    Test01();
    Test02();
    Test03();
    Test04();
    Test05();

    std::cout << "finished" << std::endl;
    return 0;
}