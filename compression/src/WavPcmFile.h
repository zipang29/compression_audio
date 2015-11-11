// Il faudra enlever QtCore et QtMultimedia pour ne mettre que les
// entêtes nécessaires
#include <QtCore>
#include <QtMultimedia>
#include <fftw3.h>

class WavPcmFile : public QFile
{
    public:
        WavPcmFile(const QString & name, const QAudioFormat & format);
        bool open();
        void writeData(QVector<fftw_complex *> data);
        void close();  // QFile::close est virtuelle

    private:
        void ecrireEntete();
        bool formatValide();
        QAudioFormat format;
};
