#include "FFT.h"
#include <QDebug>

FFT::FFT(QAudioBuffer buff)
{
    //this->inputSize = 1024;
    //this->outputSize = (inputSize / 2 + 1);
    this->buff = buff;

    //this->inputBuffer = static_cast<double*>(fftw_malloc(inputSize*sizeof(double)));
    //this->outputBuffer = static_cast<fftw_complex*>(fftw_malloc(outputSize * sizeof(fftw_complex)));

    //peut être à placer après la déclaration de fftw_plan dans compute
    for (int i=0; i<16; i++)
    {
        //inputBuffer[i] = *((float*)in.data());
        in[i][0] = *((unsigned int*)this->buff.data());
        in[i][1] = 0;
    }
    //qDebug() << inputBuffer[0];
}

fftw_complex * FFT::compute()
{
    //fftw_plan fft = fftw_plan_dft_r2c_1d(this->inputSize, this->inputBuffer, this->outputBuffer, FFTW_ESTIMATE);
    fftw_plan fft = fftw_plan_dft_1d(16, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(fft);

    fftw_destroy_plan(fft);

    return out;
}

fftw_complex * FFT::computeInverse()
{
    //fftw_plan ifft = fftw_plan_dft_c2r_1d(this->outputSize, this->outputBuffer, this->inputBuffer, FFTW_ESTIMATE);
    fftw_plan ifft = fftw_plan_dft_1d(16, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(ifft);

    /*for (int i = 0; i < 16; i++)
    {
        in2[i][0] *= 1./16;
        in2[i][1] *= 1./16;
    }*/

    fftw_destroy_plan(ifft);

   // qDebug() << inputBuffer[0];
    return in2;
}
