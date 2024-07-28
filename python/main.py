from FFT import FFT, iFFT

samples_size = 2 ** 4

import cmath

def f(x):
    freq = 3
    return cmath.sin(2 * cmath.pi * 2 * freq * x / samples_size) + 2 * cmath.cos(2 * cmath.pi * freq * x / samples_size)

samples = []
for i in range(samples_size):
    samples.append(f(i))

fft  =  FFT(samples)
ifft = iFFT(fft)

print("index       sample           FFT         inverse FFT")
print("------      ------      --------------  --------------")
for i in range(samples_size):
    print(f"{i}:\t{samples[i].real: .2f} +{samples[i].imag: .2f}j\t\
          {fft[i].real: .2f} +{fft[i].imag: .2f}j\t\
            {ifft[i].real: .2f} +{ifft[i].imag: .2f}j")