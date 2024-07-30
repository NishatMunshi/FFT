#include "../include/FFT.hpp"

#include <algorithm>
#include <stdexcept>

static std::vector<std::complex<double>>
FFT(std::vector<std::complex<double>> const& _samples,
    std::complex<double> const _omega) {
    auto const n = _samples.size();

    // base case
    if (n == 1) {
        return _samples;
    }

    // partition into two sets of n/2 vectors
    auto samples_eve = std::vector<std::complex<double>>(n / 2);
    auto samples_odd = std::vector<std::complex<double>>(n / 2);
    for (std::size_t index = 0; index < n / 2; ++index) {
        samples_eve.at(index) = _samples.at(2 * index + 0);
        samples_odd.at(index) = _samples.at(2 * index + 1);
    }

    // find fft of the two halves
    auto const return_eve = FFT(samples_eve, _omega * _omega);
    auto const return_odd = FFT(samples_odd, _omega * _omega);

    // merge the two halves
    std::vector<std::complex<double>> result(n);
    auto root_of_unity = std::complex<double>{ 1, 0 };
    for (std::size_t index = 0; index < n / 2; ++index) {
        result.at(index + 0 / 2) = return_eve.at(index) + root_of_unity * return_odd.at(index);
        result.at(index + n / 2) = return_eve.at(index) - root_of_unity * return_odd.at(index);
        root_of_unity *= _omega;
    }

    return result;
}

static bool is_power_of_2(std::size_t _num) {
    return (_num > 0) and not(_num bitand (_num - 1));
}

std::vector<std::complex<double>> FFT(std::vector<std::complex<double>> const& _samples) {
    if (not is_power_of_2(_samples.size())) {
        throw std::invalid_argument("Input size is not a power of 2\n");
    }
    using namespace std::literals::complex_literals;
    return FFT(_samples, std::exp(2.0j * M_PI / double(_samples.size())));
}

std::vector<std::complex<double>> iFFT(std::vector<std::complex<double>> const& _samples) {
    auto const n = _samples.size();
    if (not is_power_of_2(n)) {
        throw std::invalid_argument("Input size is not a power of 2\n");
    }
    using namespace std::literals::complex_literals;
    auto ifft = FFT(_samples, std::exp(-2.0j * M_PI / double(n)));
    std::for_each(ifft.begin(), ifft.end(), [&](std::complex<double>& _z) { _z /= double(n); });

    return ifft;
}
