#include <alsa/asoundlib.h>
#include <fftw3.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <thread>

void doFFT(const std::vector<double>& in, std::vector<std::complex<double>>& out) {//fast fourier transform
    int N = in.size();
    fftw_complex* out_c = reinterpret_cast<fftw_complex*>(out.data());
    fftw_plan p = fftw_plan_dft_r2c_1d(N, const_cast<double*>(in.data()), out_c, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

std::vector<std::complex<double>> fft_wrapper(const std::vector<int32_t>& intInput) {//wrap fft to output frequency domain
    std::vector<double> input(intInput.begin(), intInput.end());
    std::vector<std::complex<double>> output(input.size() / 2 + 1);
    doFFT(input, output);
    return output; // full frequency-domain vector
}

int findDominantFrequency(const std::vector<double>& samples, double sampleRate) {//find dominant frequency
    int N = samples.size();
    std::vector<std::complex<double>> spectrum(N / 2 + 1);
    doFFT(samples, spectrum);
    // Find index of the largest magnitude
    int maxIndex = 0;
    double maxMag = 0.0;
    for (int i = 0; i < spectrum.size(); ++i) {
        double mag = std::norm(spectrum[i]);  // magnitude squared
        if (mag > maxMag) {
            maxMag = mag;
            maxIndex = i;
        }
    }
    return maxIndex;
}
