from FFT import FFT, iFFT

samples_size = 2 ** 16

import cmath

def f(x):
    freq = 3
    return cmath.sin(2 * cmath.pi * 2 * freq * x / samples_size) + 2 * cmath.cos(2 * cmath.pi * freq * x / samples_size)

samples = []
for i in range(samples_size):
    samples.append(f(i))

import time

begin_time = time.clock_gettime(0)
fft  =  FFT(samples)
end_time = time.clock_gettime(0)

ifft = iFFT(fft)

print("index       sample           FFT         inverse FFT")
print("------      ------      --------------  --------------")
for i in range(samples_size):
    print(f"{i}:\t{samples[i].real: .2f} +{samples[i].imag: .2f}j\t\
          {fft[i].real: .2f} +{fft[i].imag: .2f}j\t\
            {ifft[i].real: .2f} +{ifft[i].imag: .2f}j")
    
print(f"Execution time of FFT in python for {samples_size} samples = {(end_time - begin_time) * 1000} ms")