#include "wavpcmfile.h"

WavPcmFile::WavPcmFile(const QString & name, const QAudioFormat & format) : QFile(name)
{
    this->format = format;
}

bool WavPcmFile::formatValide()
{
    // format 8 bits non signé
    // ou format 16 bits (et plus) signé little-endian
    return (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt)
           || (format.sampleSize() > 8 && format.sampleType() == QAudioFormat::SignedInt
               && format.byteOrder() == QAudioFormat::LittleEndian);
}

bool WavPcmFile::open()
{
    if (!formatValide())
    {
        setErrorString("Format d'échantillons incompatible avec le format pcm/wav. "
                       "Formats acceptés: 8 bits signé ou 16 bits non signé en little endian.");
        return false;
    }
    else
    {
        if (!QFile::open(ReadWrite | Truncate))
            return false;
        ecrireEntete();
        return true;
    }
}

void WavPcmFile::ecrireEntete()
{
    // Remplissage des 44 octets d'entête
    QDataStream out(this);
    out.setByteOrder(QDataStream::LittleEndian);

    out.writeRawData("RIFF", 4);
    // Taille du bloc RIFF (= taille fichier - 8 octets) remplie dans close()
    out << quint32(0);
    out.writeRawData("WAVE", 4);

    // Bloc de description du format:
    out.writeRawData("fmt ", 4);
    // Taille du bloc "fmt " (=16 pour du PCM)
    out << quint32(16);
    // Format du fichier (1=PCM)
    out << quint16(1);
    // nombre de canaux
    out << quint16(format.channelCount());
    // fréquence d'échantillonnage
    out << quint32(format.sampleRate());
    // octets par seconde
    out << quint32(format.sampleRate() * format.channelCount() * format.sampleSize() / 8 );
    // octets par bloc d'échantillon
    out << quint16(format.channelCount() * format.sampleSize() / 8);
    // bits par échantillon par canal
    out << quint16(format.sampleSize());

    // Bloc de données
    out.writeRawData("data", 4);
    // Taille des données (= taille fichier final - 44) remplie dans close()
    out << quint32(0);

    // Pour éviter les erreurs
    Q_ASSERT(pos() == 44);
}

void WavPcmFile::writeData(QVector<fftw_complex *> data)
{
    QDataStream out(this);
    out.setByteOrder(QDataStream::LittleEndian);
    for (int i=0; i<data.size(); i++)
    {
        fftw_complex * sample = data.at(i);

        for (int j=0; j<16; j++)
        {
            out << sample[j][0];
            out << sample[j][1];
        }
    }
}

void WavPcmFile::close()
{
    QDataStream out(this);
    out.setByteOrder(QDataStream::LittleEndian);
    quint32 tailleFichier = size();
    // Taille du bloc RIFF
    seek(4);
    out << quint32(tailleFichier-8);
    seek(40);
    out << quint32(tailleFichier-44);

    QFile::close();
}
