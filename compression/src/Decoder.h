#ifndef DECODER_H
#define DECODER_H

#include <QAudioDecoder>
#include <QVector>
#include <fftw3.h>
#include <QObject>

class Decoder : public QObject
{
    Q_OBJECT

    public:
        Decoder(QString file);
        void start();
        void constructFile();

    public slots:
        void readNextBuffer();
        void traitementTermine();

    private:
        QAudioDecoder * d;
        QVector<fftw_complex *> fft;
        QVector<fftw_complex *> ifft;
};

#endif
