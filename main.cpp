#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

#include "number.h"

int main() {
    // Шаг 1: Создание вектора v1 размером от 500 до 1000
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);

    int size = dist(gen) % 501 + 500; // от 500 до 1000
    std::vector<Number> v1;
    for (int i = 0; i < size; ++i) {
        v1.emplace_back(dist(gen));
    }

    // Шаг 2: Создание вектора v2 с последними 200 элементами v1
    int b = std::max(0, size - 200);
    int e = size;
    std::vector<Number> v2(v1.begin() + b, v1.begin() + e);

    // Шаг 3: Формирование списка list1 с первыми n наибольшими элементами
    int n = dist(gen) % 31 + 20; // от 20 до 50
    std::vector<Number> list1 = v1; // Копируем v1
    std::sort(list1.begin(), list1.end(), [](const Number& a, const Number& b) {
        return a.getValue() > b.getValue();
    });
    list1.resize(n); // Оставляем только n наибольших

    // Шаг 4: Формирование списка list2 с последними n наименьшими элементами из v2
    std::vector<Number> list2 = v2; // Копируем v2
    std::sort(list2.begin(), list2.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue();
    });
    list2.resize(n); // Оставляем только n наименьших

    // Шаг 5: Удаление перемещенных элементов из v1 и v2
    for (const auto& item : list1) {
        v1.erase(std::remove(v1.begin(), v1.end(), item), v1.end());
    }
    for (const auto& item : list2) {
        v2.erase(std::remove(v2.begin(), v2.end(), item), v2.end());
    }

    // Шаг 6: Перегруппировка элементов списка list1 по среднему значению
    double mean_value = std::accumulate(list1.begin(), list1.end(), 0.0,
                                         [](double sum, const Number& elem) {
                                             return sum + elem.getValue();
                                         }) / n;

    std::stable_partition(list1.begin(), list1.end(),
                          [mean_value](const Number& elem) {
                              return elem.getValue() > mean_value;
                          });

    // Шаг 7: Удаление нечётных элементов из list2
    list2.erase(std::remove_if(list2.begin(), list2.end(),
                                [](const Number& elem) {
                                    return elem.getValue() % 2 != 0;
                                }), list2.end());

    // Шаг 8: Создание вектора v3 из элементов, которые присутствуют и в v1 и в v2
    std::vector<Number> v3;
    for (const auto& item : v1) {
        if (std::find(v2.begin(), v2.end(), item) != v2.end()) {
            v3.push_back(item);
        }
    }

    // Шаг 9: Формирование списка list3
    size_t min_size = std::min(list1.size(), list2.size());
    
    std::vector<std::pair<Number, Number>> list3;
    for (size_t i = 0; i < min_size; ++i) {
        list3.emplace_back(list1[i], list2[i]);
    }

    // Вывод результатов
    std::cout << "List 3 pairs:\n";
    for (const auto& pair : list3) {
        std::cout << "(" << pair.first.getValue() << ", " << pair.second.getValue() << ")\n";
    }

    return 0;
}
