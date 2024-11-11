#include "awgn_generator.h"
#include <cmath>

AWGNGenerator::AWGNGenerator(double EbNo, unsigned int seed, double M) : EbNo(EbNo), generator(seed), M(std::log2(M)) {}

std::vector<std::complex<double>> AWGNGenerator::addNoise(const std::vector<std::complex<double>>& signal) {
    std::vector<std::complex<double>> noisySignal = signal;

    // Переводим отношение Eb/No (энергия бита к спектральной плотности шума) в SNR для символа
    // M — количество бит на символ (например, в 8-QAM M=3 16-QAM M =4, так как 3 и 4 бита на символ (берется log2(M)))
    double snrdb = EbNo + 10 * std::log10(M);

    // Генерируем белый гауссовский шум с нулевым средним и рассчитанным стандартным отклонением
    // Преобразуем snrdb в линейную шкалу и делим на 2, чтобы учесть реальную и мнимую компоненты (скалируем)
    std::normal_distribution<double> distribution(0.0, std::sqrt(1 / (2 * std::pow(10, snrdb / 10))));//noisePower));

    for (auto& s : noisySignal) {
        double noiseReal = distribution(generator);
        double noiseImag = distribution(generator);
        s += std::complex<double>(noiseReal, noiseImag);  // Добавляем шум
    }

    return noisySignal;
}
