#include "FFT.h"

FFT::FFT(QAudioBuffer in)
{
    this->inputSize = 1024;
    this->outputSize = (inputSize / 2 + 1);
    this->in = in;

    this->inputBuffer = static_cast<double*>(fftw_malloc(inputSize*sizeof(double)));
    this->outputBuffer = static_cast<fftw_complex*>(fftw_malloc(outputSize * sizeof(fftw_complex)));

    //peut être à placer après la déclaration de fftw_plan dans compute
    for (int i=0; i<1024; i++)
    {
        inputBuffer[i] = *((double*)in.data());
    }
}

fftw_complex * FFT::compute()
{
    fftw_plan fft = fftw_plan_dft_r2c_1d(this->inputSize, this->inputBuffer, this->outputBuffer, FFTW_ESTIMATE);

    fftw_execute(fft);

    return outputBuffer;
}

double * FFT::computeInverse()
{
    fftw_plan ifft = fftw_plan_dft_c2r_1d(this->outputSize, this->outputBuffer, this->inputBuffer, FFTW_ESTIMATE);

    fftw_execute(ifft);

    return this->inputBuffer;
}
