#pragma once

#include <vector>
#include <complex>

std::vector<std::complex<double>>  FFT(std::vector<std::complex<double>> const &_samples);
std::vector<std::complex<double>> iFFT(std::vector<std::complex<double>> const &_samples);

