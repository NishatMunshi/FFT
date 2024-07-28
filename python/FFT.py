# expects samples size be a power of 2
def FFT_recursive(samples, omega):
    n = len(samples)

    if n == 1:
        return samples

    samples_eve = samples[0::2]
    samples_odd = samples[1::2]

    ret_eve = FFT_recursive(samples_eve, omega * omega)
    ret_odd = FFT_recursive(samples_odd, omega * omega)

    ret = [None] * n
    root = 1 + 0j
    for i in range(n // 2):
        ret[i + 0 // 2] = ret_eve[i] + root * ret_odd[i]
        ret[i + n // 2] = ret_eve[i] - root * ret_odd[i]
        root *= omega

    return ret

import cmath

def is_power_of_2(x):
    return (x > 0) and not (x & (x - 1))

def FFT(samples):
    if not is_power_of_2(len(samples)):
        raise ValueError("Samples size is not a power of two.\n")
    
    return FFT_recursive(samples, cmath.exp(0 + 2j * cmath.pi / len(samples)))

def iFFT(samples):
    if not is_power_of_2(len(samples)):
        raise ValueError("Samples size is not a power of two.\n")
    
    ifft = FFT_recursive(samples, cmath.exp(0 - 2j * cmath.pi / len(samples)))
    ifft[:] = [x / len(samples) for x in ifft]
    return ifft
