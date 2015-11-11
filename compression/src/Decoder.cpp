#include "Decoder.h"
#include <QDebug>
#include "FFT.h"

Decoder::Decoder(QString file)
{
    QAudioFormat format;
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::Float);
    format.setSampleRate(48000);
    format.setSampleSize(16);

    this->d = new QAudioDecoder();
    this->d->setAudioFormat(format);
    this->d->setSourceFilename(file);
}

void Decoder::start()
{
    connect(this->d, SIGNAL(bufferReady()), this, SLOT(readNextBuffer()));
    this->d->start();
}

void Decoder::readNextBuffer()
{
    QAudioBuffer buf = this->d->read();
    FFT fft(buf);
    this->fft.push_back(fft.compute());
    this->ifft.push_back(fft.computeInverse());
    qDebug() << "ok";
}
