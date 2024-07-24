#include "../include/FFT.hpp"

#include <stdexcept>

static bool is_power_of_2(std::size_t _num) {
    return (_num > 0) and not (_num bitand (_num - 1));
}

std::vector<std::complex<double>> FFT(std::vector<std::complex<double>> const &_samples) {
    auto const n = _samples.size();
    if (not is_power_of_2(n)) {
        throw std::invalid_argument("Input size not is a power of 2\n");
    }

    // base case
    if (n == 1) {
        return _samples;
    }

    // partition into two sets of n/2 vectors
    auto samples_even = std::vector<std::complex<double>>(n / 2);
    auto samples_odd = std::vector<std::complex<double>>(n / 2);
    for (size_t index = 0; index < n / 2; ++index) {
        samples_even.at(index) = _samples.at(2 * index);
        samples_odd.at(index) = _samples.at(2 * index + 1);
    }

    // find fft of the two halves
    auto const return_even = FFT(samples_even);
    auto const return_odd = FFT(samples_odd);

    // nth root of unity
    using namespace std::literals::complex_literals;
    std::complex<double> const omega = std::exp(-2i * M_PI / double(n));

    // merge the two halves
    std::vector<std::complex<double>> result(n);
    for (size_t index = 0; index < n / 2; ++index) {
        auto const root_of_unity = std::pow(omega, index);
        result.at(index) = return_even.at(index) + root_of_unity * return_odd.at(index);
        result.at(index + n / 2) = return_even.at(index) - root_of_unity * return_odd.at(index);
    }

    return result;
}

std::vector<std::complex<double>> iFFT(std::vector<std::complex<double>> const &_samples) {
    auto const n = _samples.size();
    if (not is_power_of_2(n)) {
        throw std::invalid_argument("Input size not is a power of 2\n");
    }

    // base case
    if (n == 1) {
        return _samples;
    }

    // partition into two sets of n/2 vectors
    auto samples_even = std::vector<std::complex<double>>(n / 2);
    auto samples_odd = std::vector<std::complex<double>>(n / 2);
    for (size_t index = 0; index < n / 2; ++index) {
        samples_even.at(index) = _samples.at(2 * index);
        samples_odd.at(index) = _samples.at(2 * index + 1);
    }

    // find fft of the two halves
    auto const return_even = FFT(samples_even);
    auto const return_odd = FFT(samples_odd);

    // nth root of unity
    using namespace std::literals::complex_literals;
    std::complex<double> const omega = std::exp(2i * M_PI / double(n));

    // merge the two halves
    std::vector<std::complex<double>> result(n);
    for (size_t index = 0; index < n / 2; ++index) {
        auto const root_of_unity = std::pow(omega, index);
        result.at(index) = return_even.at(index) + root_of_unity * return_odd.at(index) / double(n);
        result.at(index + n / 2) = return_even.at(index) - root_of_unity * return_odd.at(index) / double(n);
    }

    return result;
}
