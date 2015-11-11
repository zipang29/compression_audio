#ifndef FFT_H
#define FFT_H

#include <QAudioBuffer>
#include <fftw3.h>

class FFT
{
    public:
        FFT(QAudioBuffer buff);
        fftw_complex *compute();
        fftw_complex *computeInverse();

    private:
        //int inputSize;
        //int outputSize;

        QAudioBuffer buff;
        //fftw_complex * outputBuffer;
        //double * inputBuffer;

        fftw_complex in[16], out[16], in2[16];
};

#endif
