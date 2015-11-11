#ifndef FFT_H
#define FFT_H

#include <QAudioBuffer>
#include <fftw3.h>

class FFT
{
    public:
        FFT(QAudioBuffer in);
        fftw_complex *compute();
        double * computeInverse();

    private:
        int inputSize;
        int outputSize;

        QAudioBuffer in;
        fftw_complex * outputBuffer;
        double * inputBuffer;
};

#endif
