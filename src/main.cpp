#include "../include/FFT.hpp"

#include <iomanip>
#include <iostream>

constexpr std::size_t num_samples = (1 << 16);

constexpr double f(double i) {
    return  2 * cos(2 * M_PI * 1 * i / num_samples)
          +     sin(2 * M_PI * 2 * i / num_samples);
}

int main() {
    std::vector<std::complex<double>> samples;
    for (std::size_t i = 0; i < num_samples; ++i) {
        samples.push_back(f(i));
    }

    auto const  fft =  FFT(samples);
    auto const ifft = iFFT(fft);

    std::cout << "\tsamples\t\t" << "FFT\t\t"  << "inverse FFT\n";
    std::cout << "\t-------\t\t" << "---\t\t"  << "-----------\n";

    for (std::size_t i = 0; i < num_samples; ++i) {
        std::cout << i << ":\t" << std::fixed << std::setprecision(2)
                  << samples.at(i) << "\t" << fft.at(i) << "\t" << ifft.at(i) << "\n";
    }

    return 0;
}
