#ifndef AWGN_GENERATOR_H
#define AWGN_GENERATOR_H

#include <vector>
#include <complex>
#include <random>

class AWGNGenerator {
public:
    // Конструктор, принимающий SNR и начальное значение для генератора случайных чисел
    AWGNGenerator(double EbNo, unsigned int seed , double M);

    // Метод добавления шума к входному сигналу
    std::vector<std::complex<double>> addNoise(const std::vector<std::complex<double>>& signal);

private:
    double EbNo;  // SNR в дБ
    double M; //какой тип модуляции 16 или 64 и берется логарифм чтобы узнать количество бит
    std::default_random_engine generator;  // Генератор случайных чисел
};

#endif // AWGN_GENERATOR_H
