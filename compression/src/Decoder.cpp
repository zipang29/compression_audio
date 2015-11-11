#include "Decoder.h"
#include <QDebug>
#include <QCoreApplication>
#include "FFT.h"
#include "WavPcmFile.h"

Decoder::Decoder(QString file)
{
    QAudioFormat format;
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    this->d = new QAudioDecoder();
    this->d->setAudioFormat(format);
    this->d->setSourceFilename(file);
}

void Decoder::start()
{
    this->d->start();
    connect(this->d, SIGNAL(bufferReady()), this, SLOT(readNextBuffer()));
    connect(this->d, SIGNAL(finished()), this, SLOT(traitementTermine()));
    qDebug() << "start " << this->d->state();
}

void Decoder::readNextBuffer()
{
    QAudioBuffer buf = this->d->read();
    FFT fft(buf);
    this->fft.push_back(fft.compute());
    this->ifft.push_back(fft.computeInverse());
}

void Decoder::constructFile()
{
    QAudioFormat format;
    // set up the format you want, eg.
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning()<<"default format not supported try to use nearest";
        format = info.nearestFormat(format);
    }

    // Comme on passe le format au constructeur du fichier,
    // on doit l'ouvrir après l'avoir configuré
    WavPcmFile outputFile("test.wav", format);

    if (outputFile.open())
    {
        outputFile.writeData(this->ifft);
        outputFile.close();
    }
    else
    {
        qDebug() << "Enregistrement impossible: " << outputFile.errorString();
    }
}

void Decoder::traitementTermine()
{
    qDebug() << "Traitement du fichier terminé.";
    this->constructFile();
    qDebug() << "Le fichier de sortie à été écrit";
    QCoreApplication::quit();
}
